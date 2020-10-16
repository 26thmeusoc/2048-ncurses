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

int TILES = 4; // Size of Playingfield, will be TILESxTILES

int** playingField;
long long int score = 0;

int movePossible(int **playingField) {
    // 1. Is there at least one empty field left?
    for (int r = 0; r < 4; r++) {
        for (int c = 0; c < 4; c++) {
            if (playingField[r][c] == 0) {
                return 1; // Jep! Quit this function already.
            }
        }
    }
    
    // 2. Can two neighbouring fields get combined?
    for (int r = 0; r < 3; r++) {
        for (int c = 0; c < 3; c++) {
            if (playingField[r][c] == playingField[r][c+1] || playingField[r][c] == playingField[r+1][c]) {
                return 1; // Jep! Quit this function already.
            }
        }
    }
    
    return 0;
}

void fillEmptyField(int **playingField) {
    // Instead of simply searching for empty fields until one is found (can take a very long time!), generate a list of empty fields and choose one of them.
    int counter = 0;
    int* row = malloc(16*sizeof(int));
    int* cell = malloc(16*sizeof(int));
    for (int r = 0; r < 4; r++) {
        for (int c = 0; c < 4; c++) {
            if (playingField[r][c] == 0) {
                row[counter] = r;
                cell[counter] = c;
                counter++;
            }
        }
    }
    
    int field = rand() % counter;
    
    playingField[row[field]][cell[field]] = 2;
    free(row);
    free(cell);
}

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
        xrow++;
    }
    mvprintw(maxX-1,0,"Score: %i",score);
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
    WINDOW *main = initscr();
    refreshScreen();
    int ch = ' ';
    noecho();
    keypad(main,TRUE);
    int result;
    int movePoss = 1;
    while((ch = getch()) != 'q' && movePossible(playingField)){
        result = 0;
        switch (ch) {
            case KEY_UP:
            result = moveUp(playingField,&score);
            break;
            case KEY_DOWN:
            result = moveDown(playingField,&score);
            break;
            case KEY_LEFT:
            result = moveLeft(playingField,&score);
            break;
            case KEY_RIGHT:
            result = moveRight(playingField,&score);
            break;
            default:
            break;
        }
        
        if (result > 0) {
            fillEmptyField(playingField);
            refreshScreen();
        }
    }
    int maxX, maxY;
    getmaxyx(stdscr,maxX,maxY);
    mvprintw(((maxX)/2+4),maxY/2,"Game Over");
    mvprintw(((maxX)/2+5),maxY/2,"Score was: %i",score);
    mvprintw(((maxX)/2+7),maxY/2,"Press 'q' to quit.",score);
    while (getch() != 'q');
    endwin(); // End this, redisplay old screen.
    return EXIT_SUCCESS; // Goodbye!
}
