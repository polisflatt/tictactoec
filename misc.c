#ifndef MISC_C
#define MISC_C

#include <stdio.h>
#include <stdlib.h>

/* Don't mess with this if you don't know what you're doing */
#define COORDINATE_DELIMITER "/"

/* It should be known that the dimensions must be that of a square, in order for tic-tac-toe to work */
/* It is due to the fact that diameters are not measurable on non-squares */

/* It may be considered redundant, but the variation is here for readability reasons */
#define dimension_x 2
#define dimension_y 2

/* Error codes */

/* I used char arrays because I don't want to convert ints to char arrays later on */
char* INVALID_MOVE    =   "1000";
char* WENT_TWICE      =   "1001";
char* WENT_INPLACE    =   "1002";
char* CHEATED         =   "1003";
char* LAG             =   "2000";

/* Okay, I really need integer versions, for switches */
const int I_INVALID_MOVE  =   1000;
const int I_WENT_TWICE      =   1001;
const int I_WENT_INPLACE    =   1002;
const int I_CHEATED         =   1003;
const int I_LAG             =   2000;

char* MSG_INVALID_MOVE      =   "The opponent made an invalid move which violates the rules of the game. Unspecific\n";
char* MSG_WENT_TWICE        =   "The opponent went twice, which is illegal.\n";
char* MSG_WENT_INPLACE      =   "The opponent went in place of another letter, which is illegal.\n";
char* MSG_LAG               =   "The opponent had lag to the degree of unplayability (which, for this type of game, is almost an impossibility).\n";
char* MSG_CHEATED           =   "The opponent, for an unknown reason, has been detected cheating.\n";

/* Do you want cheat protection? */
int cheat_protection = 1;

/* Theoretically, one could make an online tic-tac-toe game with more than a 3 x 3 grid. */
/* However, the winning moves must be defined */





void help()
{
    printf("tictactoec - Tic-tac-toe written in C, with some multiplayer features! Proof of concept\n");
    printf("Usage: tictactoec [modes]\n");
    printf("Modes:\n");
    printf("[blank]: Loads up the standard mode, with a two player interface. No computer.\n");
    printf("--host [port]: hosts a game with a specified port. This means, obviously, you can play over the internet. You must port forward, however.\n");
    printf("--join [address] [port]: joins a host. When joining a host, you are always X.\n");
    printf("--help: prints/displays this menu\n");
}

#endif