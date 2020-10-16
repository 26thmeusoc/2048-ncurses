/*
 * 2048 built in C with ncurses.
 * 
 * Author: Dirk Braun (@26thmeusoc)
 * Web: http://github.com/26thmeusoc/2048-ncurses
 * 
 * File created:  14.10.2020
 * Last modified: 14.10.2020
 * 
 * Description:
 * This code is a C reimplementation of Gabriele Cirullis JavaScript
 * implementation of 2048. It uses ncurses as display library to create
 * a UI. It is created to get the highest possible compability across all
 * Operating Systems.
 */

#include <stdlib.h> // For Standards, random
#include <stdio.h> // For Output
#include <time.h>

#include <ncurses.h> // For UI, use -lncurses when compiling

#include "movements.h" // For Tileshifting

#define TILES 4 // Size of Playingfield, will be TILESxTILES

int** playingField;

void refreshScreen() {
    int maxX, maxY;
    getmaxyx(stdscr,maxX,maxY);
    // Display playingfield, don't fill it with numbers now
    int xrow = 0;
    int ycol = 0;
    for (int row = 0; row < TILES; row++) {
        ycol = 0;
        for (int col = 0; col < TILES; col++) {
            mvprintw(xrow,ycol,"[    ]");
            int num = 4;
            int numI = playingField[row][col];
            while (numI > 0) {
                mvprintw(xrow,ycol+num,"%i",numI%10);
                num--;
                numI=numI/10;
                }
            ycol+=maxY/4;
        }
        xrow=xrow+maxX/4;
    }
    refresh();
}

int initializePlayingField() {
    // Generate Rows in this game
    if ((playingField = malloc(TILES*(sizeof(int*)))) == NULL) {
        printf("Could not allocate memory for game! Exiting!");
        return 1;
    }
    
    // Generate Colums for each row
    for (int i = 0; i < TILES; i++) {
        if ((playingField[i] = malloc(TILES*(sizeof(int*)))) == NULL) {
            printf("Could not allocate memory for game! Exiting!");
            return 1;
        }
    }
    // Set each value to 
    for (int r = 0; r < TILES; r++) {
        for (int c = 0; c < TILES; c++) {
            playingField[r][c] = 0;
        }
    }
    
    srand(time(NULL));
    int randX = rand()%TILES;
    int randY = rand()%TILES;
    playingField[randX][randY] = 2;
    while (playingField[randX][randY] > 0) {
        // Make sure we don't generate the second value on the first one 
        randX = rand()%TILES;
        randY = rand()%TILES;
    }
    playingField[randX][randY] = 2;
    
    // Everything went fine! Exit function and return 0.
    return 0;
}

int main(int argc, char **argv) {
    if (initializePlayingField() > 0) {
        return EXIT_FAILURE; // BAIL! BAIL! BAIL!
    }
    initscr();
    refreshScreen();
    getch(); // Wait here, display this screen
    endwin(); // End this, redisplay old screen.
    return EXIT_SUCCESS; // Goodbye!
}
