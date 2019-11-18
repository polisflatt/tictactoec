#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "game.c"
#include "color.h"
#include "networking.c"
#include "misc.c"

/* Main function  */
int main(int argc, char** argv)
{  
    /* Multiplayer and other options */
    /* Also primitive and cheap way to handle arguments, however */
    /* this program is not overly complex so it is okay in some regards, I could guess. */
    if (argc > 1)
    {
        if (!strcmp(argv[1], "--host"))
        {
            if (!argv[2] || !argv[3])
            {
                printf("Insufficient arguments. You must provide the port you wish to host on, as well as your username.\n"); 
                exit(EXIT_FAILURE);
            }
            
            int _port = atoi(argv[2]);
            host_game(_port, argv[3]);
            return 0;
        }
        else if (!(strcmp(argv[1], "--join")))
        {
            if (!argv[2] || !argv[3])
            {
                printf("Insufficient arguments. You must provide either the address or port you want to join. (Both are imperative) You must also provide a username.\n");
                exit(EXIT_FAILURE);
            }

            char* address = argv[2];
            int _port = atoi(argv[3]);
            join_game(address, _port, argv[4]);
            return 0;
        }
        else if (!(strcmp(argv[1], "--help")))
        {
            help();
            return 0;
        }
        else if (!(strcmp(argv[1], "--array-test")))
        {
            char _array[5][5] = {
                {'x', 'o', 'o', 'o', 'o'},
                {'o', 'x', 'o', 'o', 'o'},
                {'o', 'o', 'x', 'o', 'o'},
                {'o', 'o', 'o', 'o', 'o'},
                {'o', 'o', 'o', 'o', 'o'},
            };

            printf("%d", array_won_check('x', _array));
            exit(0);
        }
        else
        {
            printf("You have provided an invalid argument. Doing nothing; exiting, too...\n");
            exit(EXIT_FAILURE);
        }
        

    }
    
    
    /* Single player */
    /* Setup the board */
    int board[dimension_x][dimension_y];
    
    /* FILL BOARD */
    for (int i = 0; i < dimension_y; i++)
    {
        for (int j = 0; j < dimension_x; j++)
        {
            board[i][j] = SPACE;
        }
    }

    /* Welcome Message */
    printf(ANSI_COLOR_GREEN "Tic-Tac-Toe: Version 1.0 . In the C programming language. Only a proof of concept\n" ANSI_COLOR_RESET);

    /* Making a loop so we can ask the question again if neither yes or no is entered! */
    /* Not doing such is an example of very primitive code! */
    while (1)
    {  
        printf("Do you wish to continue?: (y/n): ");
        char continue_input = getchar();
        if (continue_input == 'n')
        {
            printf("\nGoodbye, then!\n"); exit(EXIT_SUCCESS);
            break; /* Redundant, but it adds to the readability of the code */
        }
        else if (continue_input == 'y')
        {
            printf("\nOkay, continuing!\n");
            break;
        }
        else
        {
            printf("\nYou didn't enter yes or no. Going back and asking the question again, are you retarded?\n");
            continue;
        }

    }

    /* Starting Game */


    /* Turns */
    for (int i = 0; i < 100; i++) /* We give one-hundred turns, because no tic-tac-toe game would continue past that -- or get even close */
    {
        char turn = 'N';
        clear();

        /* Display the board; check if someone has one and conclude the game! */
        display_board(board);
        
        if (who_won(board))
        {
            printf("\nGame complete!\n");
            exit(0);
        }

        /* O always begins first -- and when i is even */
        if (i % 2 == 0) /* O's turn */
        {
            turn = O;
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

            printf("X coordinate: ");
            int x;
            scanf("%d", &x);
            
            if (letter_exists(board, x, y))
            {
                printf("A letter already exists at those coordinates\n");
                continue;
            }

            /* Place the letter on the board */
            place(board, turn, x, y);
            break;
        }
    }



    return EXIT_SUCCESS; /* Returns 0; is simply a wrapper for legibility purposes. */
}