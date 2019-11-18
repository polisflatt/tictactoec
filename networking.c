#ifndef NETWORKING_C
#define NETWORKING_C

#include <unistd.h> 
#include <stdio.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string.h> 
#include <netdb.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <errno.h>

#include "game.c"
#include "color.h"
#include "misc.c"


extern int errno;
#define PORT 6216

/* TACTOE PROTOCOL, No bloated JSON! */
/* USERNAME */ /* of your opponent */
/* DIMENSION */ /* Of the board */
/* X-CORD/Y-CORD*/ /* To place */
/* @ message */

/* Seriously? That's all! */

/* Translates the aforementioned protocol into useful, numerical coordinates */

/* void* networking_error_code(int code)
{
    switch (code)
    {
        case I_WENT_INPLACE:
            printf(MSG_WENT_INPLACE);
            break;
        
        case I
    }
}
*/


void commands(int fd, char* _command) /* The wonderful thing about sockets is that they are files, not bloated structs */
{
    char operation = _command[0];
    char* command = _command; /* Move address up one */

    switch (operation)
    {
        case '@':
            send(fd, command, sizeof(command), 0);
            break;
    }
}

void* wait_function()
{
    char chars[] = {
        '|', '/', '-', '\\'
    };

    while (1)
    {
        for (int i = 0; i < sizeof(chars); i++)
        {
            printf(".");
            printf("%c", chars[i]);
            fflush(stdout);
            sleep(1);
            printf("\b");
        }
    }
}

int* coordinates(char buffer[])
{
    int* coordinates = (int*) malloc(sizeof(int) * 2);
    char* token = strtok(buffer, COORDINATE_DELIMITER);

    
    coordinates[0] = atoi(token);
    token = strtok(NULL, COORDINATE_DELIMITER);
    coordinates[1] = atoi(token);

    return coordinates;

}


/* Beware of bloat below */
/* I tried, as much as I could, to condense the functions */
/* However they operate differently to a degree where I cannot. I am sorry. */


/* Host game function */
void host_game(const int port, const char* username)
{
    /* Initalize board */
    /* Also a good way to cheat! */
    /* But why...? */

    int board[dimension_y][dimension_x];
    for (int i = 0; i < dimension_y; i++)
    {
        for (int j = 0; j < dimension_x; j++)
        {
            board[i][j] = SPACE;
        }
    }
    
    printf("Hosting...\n");
    /* Networking shit I half-wrote myself */

    int server_fd, new_socket, valread; 
    struct sockaddr_in address; 
    int opt = 1; 
    int addrlen = sizeof(address); 
    char buffer[1024];
       
    // Creating socket file descriptor
    printf("Creating sockets...\n");

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) 
    { 
        fprintf(stderr, "Socket creation failed: %s\n", strerror(errno)); 
        exit(EXIT_FAILURE); 
    } 
       
    address.sin_family = AF_INET; 
    address.sin_addr.s_addr = INADDR_ANY; 
    address.sin_port = htons(port); 
       
    /* Bind! */ 
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) != 0)
    {
        fprintf(stderr, "Error with binding to port %d: %s\n", port, strerror(errno));
        exit(EXIT_FAILURE);
    }
    
    
    pthread_t wait_thread;
    /* Nice little wait animation */
    printf("Server listening..."); 
    pthread_create(&wait_thread, NULL, wait_function, NULL);

    if ((listen(server_fd, 5)) != 0) { 
        printf("Listen failed: %s\n", strerror(errno)); 
        exit(EXIT_FAILURE); 
    } 
    
    /* Connection accepted */
    new_socket = accept(server_fd, (struct sockaddr *) &address,  (socklen_t*) &addrlen);
    pthread_cancel(wait_thread);
    
    char ip[256];
    int length = sizeof(address);
    getpeername(server_fd, (struct sockaddr*) &address, &length);
    struct sockaddr_in *s = (struct sockaddr_in *) &address;
    inet_ntop(AF_INET, &s->sin_addr, ip, sizeof ip);

    printf("\nConnection accepted from %s!\n", ip);
    printf("You are O! - because you are host.\n");

    send(new_socket, username, sizeof(username), 0);
    char rival_username[256];

    /* Wait */
    printf("Obtaining username...");
    pthread_create(&wait_thread, NULL, wait_function, NULL);

    while (!recv(new_socket, rival_username, sizeof buffer, 0))
    {
        //printf("Obtaining username...");
    }
    pthread_cancel(wait_thread);
    printf("\nYou are matched with %s\n", rival_username);

    for (int i = 0; i < 100; i++) /* We give one-hundred turns, because no tic-tac-toe game would continue past that -- or get even close */
    {
        char turn = 'N';

        /* Display the board; check if someone has one and conclude the game! */

        if (i > 1)
        {
            clear();
        }

        display_board(board);
        if (who_won(board))
        {
            printf("\nGame complete!\n");
            exit(0);
        }

        /* Whoever is hosting is always O -- and is always first! */
        /* O always begins first -- and when i is even */
        if (i % 2 == 0) /* O's turn */
        {
            turn = O;
        }
        else /* X's turn */
        {
            while (1)
            {
                turn = X;
                char buffer[256];
                printf("\nWait...");
                pthread_t wait_thread;
                pthread_create(&wait_thread, NULL, wait_function, NULL);


                while (!recv(new_socket, buffer, sizeof(buffer), 0))
                {
                    if (errno != 0)
                    {
                        fprintf(stderr, "Error: %s\n", strerror(errno));
                        exit(1);
                    }
                }
                pthread_cancel(wait_thread);

                if (buffer[0] == '@')
                {
                    printf("\nMESSAGE FROM %s: %s\n", rival_username, buffer + 1);
                    continue;
                }

                int* coords = coordinates(buffer);

                if (letter_exists(board, coords[0], coords[1]))
                {
                    send(new_socket, (char*) WENT_INPLACE, sizeof(WENT_INPLACE), 0);
                    printf("Opponent went in place of another letter. Most likely cheating...\n");
                    exit(EXIT_FAILURE);
                }

                place(board, turn, coords[0], coords[1]);
                break;
            }
            continue;
        }
        
        /* O's turn - again */
        /* Really wish I could use gotos, but I want the code to be readable */
        while (1)
        {
            /* Instructions */
            printf(ANSI_COLOR_RED "(PASSING NON-INT OR OUT OF RANGE WILL SEG FAULT!)\n" ANSI_COLOR_RESET "Mark the coordinates you want to place your sign on\n");
            printf("%c's turn!\n", turn);
            
            /* Coordinates */
            printf("Y coordinate: ");
            int y;
            scanf("%d", &y);

            /* Commands menu */
            if (y == -1)
            {
                printf("Command: ");
                char* command = (char*) malloc(256 * sizeof(char));
                scanf("%s\n", command);
                
                if (command != NULL) 
                {
                    commands(new_socket, command);
                }

                y = 0;
                continue;
            }

            printf("X coordinate: ");
            int x;
            scanf("%d", &x);

            char buffer[256];

            if (letter_exists(board, x, y))
            {
                printf("A letter already exists at those coordinates\n");
                continue;
            }

            sprintf(buffer, "%d%s%d", x, COORDINATE_DELIMITER, y);

            /* Send the coordinates to the client */
            send(new_socket, buffer, sizeof(buffer), 0);

            /* Place the letter on the board - on client side!*/
            place(board, turn, x, y);
            break;
        }
    }

}

/* Join a host */
int join_game(const char* ip_address, const int port, const char* username)
{
    int board[dimension_y][dimension_x];
    for (int i = 0; i < dimension_y; i++)
    {
        for (int j = 0; j < dimension_x; j++)
        {
            board[i][j] = SPACE;
        }
    }

    int sockfd, connfd; 
    struct sockaddr_in servaddr, cli; 

    sockfd = socket(AF_INET, SOCK_STREAM, 0); 
    
    printf("Socket successfully created..\n");
    
    bzero(&servaddr, sizeof(servaddr)); 
  
    /* Set up networking shit */
    servaddr.sin_family = AF_INET; 
    servaddr.sin_addr.s_addr = inet_addr(ip_address); 
    servaddr.sin_port = htons(port); 
  
    // connect the client socket to server socket 
    if (connect(sockfd, (struct sockaddr*) &servaddr, sizeof(servaddr)) != 0) { 
        printf("Connection to the host %s:%d failed: %s\n", ip_address, port, strerror(errno)); 
        exit(0); 
    } 
    
    printf("\nConnection success! You are X because you are not a host. Hosts go first. Please wait!\n");

    char rival_username[256];

    pthread_t wait_thread;
    printf("Obtaining username...");
    pthread_create(&wait_thread, NULL, wait_function, NULL);
    
    while (!recv(sockfd, rival_username, sizeof(rival_username), 0))
    {

    }
    pthread_cancel(wait_thread);
    printf("\nYou are matched with %s\n", rival_username);

    send(sockfd, username, sizeof(username), 0);

    for (int i = 0; i < 100; i++) /* We give one-hundred turns, because no tic-tac-toe game would continue past that -- or get even close */
    {
        char turn = 'N'; /* o goes first */

        if (i > 1)
        {
            clear();
        }

        /* Display the board; check if someone has won and conclude the game! */
        display_board(board);
        if (who_won(board))
        {
            printf("\nGame complete!\n");
            exit(0);
        }

        /* O always begins first -- and when i is even */
        if (i % 2 == 0) /* O's turn */
        {
            while (1)
            {
                //printf("Wait...\n");
                turn = O;
                char buffer[256];

                printf("\nWait...");
                pthread_t wait_thread;
                pthread_create(&wait_thread, NULL, wait_function, NULL);

                int j = 0;
                while (!recv(sockfd, buffer, sizeof(buffer), 0))
                {
                    if (errno != 0)
                    {
                        fprintf(stderr, "Error: %s\n", strerror(errno));
                        exit(1);
                    }
                }
                pthread_cancel(wait_thread);

                if (buffer[0] == '@')
                {
                    printf("\nMESSAGE FROM %s: %s\n", rival_username, buffer + 1);
                    continue;
                }

                int* coords = coordinates(buffer);

                if (letter_exists(board, coords[0], coords[1]))
                {
                    send(sockfd, (char*) WENT_INPLACE, sizeof(WENT_INPLACE), 0);
                    printf("Opponent went in place of another letter. Most likely cheating...\n");
                    exit(EXIT_FAILURE);
                }

                place(board, turn, coords[0], coords[1]); 
                clear();
                break;
            }
            continue;
        }
        else /* X's turn */
        {
            turn = X;

        
        }
        
        while (1)
        {
            /* Instructions */
            printf(ANSI_COLOR_RED "(PASSING NON-INT OR OUT OF RANGE WILL SEG FAULT!)\n" ANSI_COLOR_RESET "Mark the coordinates you want to place your sign on\n");
            printf("%c's turn!\n", turn);
            
            /* Coordinates */
            printf("Y coordinate: ");
            int y;
            scanf("%d", &y);

            if (y == -1)
            {
                printf("Command: ");
                char command[256];
                scanf("%[^\n]%*c", command);
                
                if (command != "") 
                {
                    commands(sockfd, command);
                }

                y = 0;
                continue;
            }

            printf("X coordinate: ");
            int x;
            scanf("%d", &x);

            char buffer[256];

            sprintf(buffer, "%d%s%d", x, COORDINATE_DELIMITER, y);
            
            if (letter_exists(board, x, y))
            {
                printf("A letter already exists at those coordinates\n");
                continue;
            }

            send(sockfd, buffer, sizeof(buffer), 0);

        

            /* Place the letter on the board */
            place(board, turn, x, y);
            break;
        }
    }




    close(sockfd); 
}

#endif