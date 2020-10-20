/*
 * 2048 built in C with ncurses.
 * 
 * Author: Dirk Braun
 * Web: http://github.com/26thmeusoc/2048-ncurses
 * 
 * File created:  14.10.2020
 * Last modified: 20.10.2020
 * 
 * Description:
 * This code is a C reimplementation of Gabriele Cirullis JavaScript
 * implementation of 2048. It uses ncurses as display library to create
 * a UI. It is created to get the highest possible compability across all
 * Operating Systems.
 */

#include <stdlib.h> // For Standards, random
#include <stdio.h> // For Output
#include <time.h> // For time()

#include <ncurses.h> // For UI, use -lncurses when compiling

#include "movements.h" // For Tileshifting

int TILES = 4; // Size of Playingfield, will be TILESxTILES

int** playingField; // Save the current playing field in here
long long int score = 0; // Save the current player score in here

/**
 * Check whether a move is still possible
 * 
 * Checks whether a move is still possible. This can happen when at 
 * least one empty field is left or two fields with the same value
 * are next to each other.
 * 
 * @param playingField Currently used field
 * @return 1 when a move is still possible, otherwise 0
 */
int movePossible(int **playingField) {
    // 1. Is there at least one empty field left?
    for (int r = 0; r < 4; r++) { // Check each row
        for (int c = 0; c < 4; c++) { // Check each column
            if (playingField[r][c] == 0) { // Is row/column an empty field?
                return 1; // Yes! Quit this function already, return 1
            }
        }
    }
    
    // 2. Can two neighbouring fields get combined?
    for (int r = 0; r < 3; r++) { // Check each row
        for (int c = 0; c < 3; c++) { // Check each column
            if (playingField[r][c] == playingField[r][c+1] || playingField[r][c] == playingField[r+1][c]) { // Can field to the right or below get combined?
                return 1; // Yes! Quit this function, return 1
            }
        }
    }
    
    // Both functions didn't come up with a possible move. Return 0
    return 0;
}

/**
 * Select a single field and add a value to it.
 * 
 * Searches the playing field for an empty field and adds a new
 * value to it.
 *
 * @param playingField
 */
void fillEmptyField(int **playingField) {
    /* Instead of simply randomly searching for empty fields until
     * one is found (can take a very long time!), generate a list
     * of empty fields and choose one of them.
     */
    int counter = 0; // Count how many empty fields have been found
    
    /* Generate two lists, remember which row and column combination,
     * sizes have to be number of all available fields.
     */
    int* row = malloc(16*sizeof(int));
    int* cell = malloc(16*sizeof(int));
    for (int r = 0; r < 4; r++) { // For every row
        for (int c = 0; c < 4; c++) { // For every column
            if (playingField[r][c] == 0) { // Is this field empty?
                row[counter] = r; // Yes, remember row...
                cell[counter] = c; // ...and column coordinate
                counter++; // Increase counter
            }
        }
    }
    
    int field = rand() % counter; // Select one random field
    
    // With a chance of 5:2 ...
    if ((rand()%7) < 5) {
        // ... set value of this field with 2
        playingField[row[field]][cell[field]] = 2;
    } else { // ... set value to 4
        playingField[row[field]][cell[field]] = 4;
    }
    free(row); // Free both lists, so we don't leak memory
    free(cell);
}

/**
 * Redraw fields on screen.
 * 
 * Redraw the complete playingfield on screen.
 */
void refreshScreen() {
    int maxX, maxY; // Save screensize here.
    getmaxyx(stdscr,maxX,maxY); // Get screen dimensions
    
    // Display playingfield, don't fill it with numbers now
    int xrow = 0;
    int ycol = 0;
    int borderx=0;
    int bordery=0;
    for (int row = 0; row < TILES; row++) { // For each row...
        ycol = 0;
        for (int col = 0; col < TILES; col++) { // ...and each column
            mvprintw(xrow,ycol,"[    ]"); // Draw a small box
            getyx(stdscr,bordery,borderx);
            // Write each value backwards
            int num = 4;
            int numI = playingField[row][col]; // Select field
            while (numI > 0) { // As long as not all numbers have been printed
                // Display the current number
                mvprintw(xrow,ycol+num,"%i",numI%10);
                num--; // Get one character to the left
                numI=numI/10; // Div value by 10 (shift this number)
            }
            ycol=borderx; // Go to the next cell 
        }
        xrow++; // Go to the next row
    }
    mvprintw(maxX-2,0,"Score: %i",score); // Display Scorerow at the end of the screen
    refresh(); // Redraw screen
}

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
    if ((playingField = malloc(TILES*(sizeof(int*)))) == NULL) {
        // Something went wrong. Show error message
        printf("Could not allocate memory for game! Exiting!");
        // Exit this function with an Error-Code
        return 1;
    }
    
    // Generate Colums for each row
    for (int i = 0; i < TILES; i++) {
        if ((playingField[i] = malloc(TILES*(sizeof(int*)))) == NULL) {
            // Something went wrong. Show error message
            printf("Could not allocate memory for game! Exiting!");
            // Exit sthis function with an Error-Code
            return 1;
        }
    }
    // Set each field value to zero
    for (int r = 0; r < TILES; r++) {
        for (int c = 0; c < TILES; c++) {
            playingField[r][c] = 0;
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
    playingField[randX][randY] = 2;
    // Repeat this search, as long as the selected field is not empty
    while (playingField[randX][randY] > 0) {
        // Make sure we don't generate the second value on the first one 
        randX = rand()%TILES; // Select a new random row
        randY = rand()%TILES; // Select a new random column
    }
    playingField[randX][randY] = 2; // Set this new fields value to 2.
    
    // Everything went fine! Exit function and return 0.
    return 0;
}

int main(int argc, char **argv) {
    if (initializePlayingField() > 0) { // Can we allocate enough memory?
        return EXIT_FAILURE; // BAIL! BAIL! BAIL!
    }
    WINDOW *main = initscr(); // Initialize ncurses
    curs_set(0); // Hide cursor
    refreshScreen(); // Redraw Screen
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
            refreshScreen();
            break;
            default:
            break;
        }
        
        // Was the last move useful (some change in playingField)
        if (result > 0) { // Yes, add a new value to playingField
            fillEmptyField(playingField);
            refreshScreen(); // Redraw screen
        }
    }
    refreshScreen();
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
