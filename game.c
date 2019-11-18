#ifndef GAME_H
#define GAME_H

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "color.h"
#include "misc.c"

/* Definitions */
#define X 'X'
#define O 'O'
#define SPACE '0'

/* Graphically display the board */
/* For the argument of the board, I chose a retarded way because C was being a faggot */


void display_board(int board[][dimension_x])
{
    printf(ANSI_COLOR_GREEN "[Y]\n" ANSI_COLOR_RESET);
    for (int i = 0; i < dimension_y; i++)
    {
        /* Display the Y coordinates */
        printf(ANSI_COLOR_GREEN "[%d]" ANSI_COLOR_RESET, i);

        for (int j = 0; j < dimension_y; j++)
        {
            /* Display the letter */
            printf("[%c]", board[i][j]);
        }

        printf("\n");
    }
    /* Display the X coordinates */
    printf(ANSI_COLOR_GREEN "[X]" ANSI_COLOR_RESET);
    for (int i = 0; i < dimension_x; i++)
    {
        printf(ANSI_COLOR_GREEN "[%d]" ANSI_COLOR_RESET, i);
    }
}

/* Algorithim for checking who won */
int array_won_check(char search, int board[][dimension_x])
{
    int _won = 0;
    /* Across */
    for (int i = 0; i < dimension_y; i++)
    {  
        int won = 0;
        
        for (int j = 0; j < dimension_x; j++)
        {
            if (board[i][j] != search)
            {
                won = 0;
            }
            else if (board[i][j] == search)
            {
                if (j == (dimension_x - 1) && won == 1) /* Counting from zero and then from one is confusing. */
                {
                    printf("ACROSS\n");
                    return 1; 
                }
                else
                {
                    won = 1;
                }
            }
        }

        /*                 -------------
        * is [] [] [] [] = |[] [] [] []|
        *                  -------------  
        *                  [] [] [] []  
        *                  [] [] [] []
        * 
        * Essentially what we are doing
        */

       //return won;
    }

    /* Straight down */
    for (int i = 0; i < dimension_x; i++)
    {
        /*
        * --------->
        * |[x]| [] []
        * |[x]| [] []
        * |[x]| [] []
        * --------->
        * 
        */
        int won = 0;

        for (int j = 0; j < dimension_y; j++)
        {
            won = 1;

            if (board[j][i] != search)
            {
                won = 0;
                break; 
            }
        }

        if (won)
        {
            printf("DOWN\n");
            return won;
        }
    }

    for (int i = 0; i < dimension_y; i++)
    {
        if (board[i][i] != search)
        {
            _won = 0;
            break; 
        }
        else if (board[i][i] == search)
        {
            _won = 1;
        }
        
        if (i == (dimension_y - 1) && board[i][i] == search && _won == 1)
        {
            printf("DIAGONAL\n");
            return 1;
        }
    }

    int _y = 0;
    for (int i = (dimension_x - 1); i >= 0; i--)
    {
        if (board[i][_y] != search)
        {
            _won = 0;
            _y++;
            break;
        }
        else if (board[i][_y] == search)
        { 
            _won = 1;
        }

        if (i == 0 && board[i][_y] == search &&_won == 1) /* At the end of the diagonal */
        { /* Actual some mathematics and logical thinking for coding a simple game like tic-tac-toe */
            printf("reverse diagonal\n");
            return 1;
        }

        _y++;
        
    }

    return 0;
}


/* Find out who won, say it, and return if someone won */
int who_won(int board[][dimension_x])
{
    /* OOO */

    char player[2] = {O, X};
    int won = 0;
    int result[2] = {0, 0};

    /* REALLY REDUNDANT CODE, BUT C WAS BEING, AS USUAL, RETARDED */
    for (int i = 0; i < 2; i++)
    {
        if (array_won_check(player[i], board))
        {
            //printf("%s won the game.\n", player[i]);
            return 1;

        }
    }

    /* No one won */
    return 0;
}

/* Place a letter on the board on the coordinates given */
/* Simple, compared to the other god forsaken functions */
int place(int board[][dimension_x], int player, int coordinate_x, int coordinate_y)
{
    board[coordinate_y][coordinate_x] = player;
}

/* Prevent overlapping of letters */
int letter_exists(int board[][dimension_x], int coordinate_x, int coordinate_y)
{
    return (board[coordinate_y][coordinate_x]) != SPACE;
}


/* Clear the screen (universally?) Nice attempt, but the colours are not universal. */
void clear()
{
    system("cls");
    system("clear");
}

#endif