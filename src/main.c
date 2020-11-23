/*
 * 2048 built in C with ncurses.
 * 
 * Author: Dirk Braun
 * Web: http://github.com/26thmeusoc/2048-ncurses
 * 
 * File created:  14.10.2020
 * Last modified: 22.10.2020
 * 
 * Description:
 * This code is a C reimplementation of Gabriele Cirullis JavaScript
 * implementation of 2048. It uses ncurses as display library to create
 * a UI. It is created to get the highest possible compability across all
 * Operating Systems.
 * 
 *  This file is part of 2048-ncurses.
 *
 * 2048-ncurses is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * 2048-ncurses is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with 2048-ncurses.  If not, see  <https://www.gnu.org/licenses/>.
 */

#include <stdlib.h> // For Standards, random
#include <stdio.h> // For Output
#include <time.h> // For time()

#include <ncurses.h> // For UI, use -lncurses when compiling

#ifndef DEFGAME
#include "game.h" // For game internals
#define DEFGAME 1
#endif

#include "movements.h" // For Tileshifting
#include "uinterface.h" //

int TILES = 4; // Size of Playingfield, will be TILESxTILES
tile_t** playingField; // Save the current playing field in here
long long int score = 0; // Save the current player score in here
int generateColorPairs() {
    return 0;
}

/**
 * Generate a playing Field.
 * 
 * Generate a two dimensional pointerlist which will be
 * used as a playingField
 * 
 * @return Return 0 when a playing field was successfully generated, otherwise 1
 */
int initializePlayingField() {
    // Generate Rows in this game
    if ((playingField = malloc(TILES*(sizeof(tile_t)))) == NULL) {
        // Something went wrong. Show error message
        printf("Could not allocate memory for game! Exiting!");
        // Exit this function with an Error-Code
        return 1;
    }
    
    // Generate Colums for each row
    for (int i = 0; i < TILES; i++) {
        if ((playingField[i] = malloc(TILES*(sizeof(tile_t)))) == NULL) {
            // Something went wrong. Show error message
            printf("Could not allocate memory for game! Exiting!");
            // Exit sthis function with an Error-Code
            return 1;
        }
    }
    // Set each field value to zero
    for (int r = 0; r < TILES; r++) {
        for (int c = 0; c < TILES; c++) {
            playingField[r][c].value = 0;
        }
    }
    
    // Seed randomnumber generator
    srand(time(NULL));
    // Select a random row
    int randX = rand()%TILES;
    // Select a randow column
    int randY = rand()%TILES;
    
    // Set this field value to two.
    // Playingfield is empty, so no extra check is needed
    playingField[randX][randY].value = 2;
    // Repeat this search, as long as the selected field is not empty
    while (playingField[randX][randY].value > 0) {
        // Make sure we don't generate the second value on the first one 
        randX = rand()%TILES; // Select a new random row
        randY = rand()%TILES; // Select a new random column
    }
    playingField[randX][randY].value = 2; // Set this new fields value to 2.
    
    // Everything went fine! Exit function and return 0.
    return 0;
}

int main(int argc, char **argv) {
    if (initializePlayingField() > 0) { // Can we allocate enough memory?
        return EXIT_FAILURE; // BAIL! BAIL! BAIL!
    }
    WINDOW *main = initscr(); // Initialize ncurses
    curs_set(0); // Hide cursor
    refreshScreen(playingField,score); // Redraw Screen
    int ch = ' '; // Remember last pressed key
    noecho(); // Don't show last pressed key on screen
    keypad(main,TRUE); // Allow scan for Arrowkeys
    int result; // Remember whether the move was useful
    int movePoss = 1; // Remember whether move is still possible
    // Repeat game as long as 'q' wasn't pressed and there is still a move possible
    while((ch = getch()) != 'q' && movePossible(playingField)){
        result = 0;
        
        // Which key was pressed?
        switch (ch) {
            
            // For now, only allow arrowkeys
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
            case KEY_F(9):
            clear();
            mvprintw(3,2,"2048-ncurses");
            mvprintw(4,2,"A reimplementation of 2048 by:");
            mvprintw(5,6,"Gabriele Cirulli et al.");
            mvprintw(6,6,"http://gabrielecirulli.github.io/2048/");
            mvprintw(8,2,"Code:");
            mvprintw(9,6,"Dirk Braun");
            mvprintw(10,6,"https://github.com/26thmeusoc/2048-ncurses/");
            mvprintw(12,2,"Published under GNU Public License v3");
            getch();
            clear();
            refreshScreen(playingField,score);
            break;
            default:
            break;
        }
        
        // Was the last move useful (some change in playingField)
        if (result > 0) { // Yes, add a new value to playingField
            fillEmptyField(playingField);
            refreshScreen(playingField,score); // Redraw screen
        }
    }
    refreshScreen(playingField,score);
    // Get the current screendimensions
    int maxX, maxY;
    getmaxyx(stdscr,maxX,maxY);
    
    // Display Game Over Screen
    mvprintw(((maxX)/2+4),maxY/2,"Game Over");
    // Display current score
    mvprintw(((maxX)/2+5),maxY/2,"Score was: %i",score);
    // Instruct user how to quit the application
    mvprintw(((maxX)/2+7),maxY/2,"Press 'q' to quit.");
    while (getch() != 'q'); // Only quit when user presses 'q'
    endwin(); // End this, redisplay old screen.
    return EXIT_SUCCESS; // Goodbye!
}
