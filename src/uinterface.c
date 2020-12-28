/*
 * 2048 built in C with ncurses.
 * 
 * Author: Dirk Braun
 * Web: http://github.com/26thmeusoc/2048-ncurses
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
 * 
 * Define functions for displaying the game.
 */

#include "uinterface.h"

screenSizes *lastSizes;

int cmpSize() {
    int newX, newY; // Prepare Variables for current screen Size
    getmaxyx(stdscr,newX,newY); // Get current screen sizes
    if ((lastSizes == NULL)) { // Was this check done before?
        // No. Save sizes for the first time
        lastSizes = (screenSizes*) malloc(sizeof(screenSizes)); // Allocate some space
        lastSizes->maxWidth = newY; // Save values
        lastSizes->maxHeight = newX;
    } else if (lastSizes->maxWidth != newY || lastSizes->maxHeight != newX) { // Check was done before, check whether size of shell has changed
        // New sizes found
        lastSizes->maxWidth = newY; // Save new values 
        lastSizes->maxHeight = newX;
        clear(); // Clear screen
        return 1; // Return result
    } else {
        // No changes in shell size, return result
        return 0;
    } // of else
}

void calculateTileCoordinates(tile_t** playingField) {
    // Search for the mid of screen
    lastSizes->midx = (lastSizes->maxWidth)/2; // Mid of x
    lastSizes->midy = (lastSizes->maxHeight)/2; // Mid of y
    lastSizes->leftCol = (lastSizes->midx)-9; // Position of leftmost column
    lastSizes->upperLine = (lastSizes->midy)-3; // Position of upmost column
    int row = lastSizes->upperLine; // Search for first row
    for (int i = 0; i < 4; i++) { // for every row
        int col = lastSizes->leftCol; // Search for first column
        for (int n = 0; n < 4; n++) { // for every column
            playingField[i][n].uixstart = col; // Write column coordinate
            playingField[i][n].uiystart = row; // Write row coordinate
            col = col+5; // Add 5 to current column coordinate (4 number + |)
        } // of for (n=0)
        row = row+2; // Add 2 to current row coordinate (1 Row + ----)
    } // of for (i=0)
}

void redrawGrid() {
    // Where is the leftmost column located?
    int x = lastSizes->leftCol;
    // Get coordinates of toprow
    int y = lastSizes->upperLine+1; // First line is below first row
    for (int i = 0; i < 3; i++) { // Draw 3 lines
        move(y,x); // Move Cursor to coordinaes
        for (int n = 0; n < 4; n++) { // Draw 4 column separators
            addstr("----"); // Draw Line below cell
            if (n+1 != 4) {
                addstr("+"); // Create a junction of row and column separators
            } // of if (n+1 != 4)
        } // of for (n=0)
        x = lastSizes->leftCol; // get next x-coordinates
        y = y+2; // Calculate next row separator coordinates
    } // of for (i=0)
    x = (lastSizes->leftCol)+4; // Move to the first column for a separator
    y = lastSizes->upperLine; // Move to the firt line
    move(y,x); // Move cursor
    for (int i = 0; i < 4; i++) { // For every row
        for (int n = 0; n < 3; n++) { // For every column
            addstr("|"); // Draw a separator
            x = x+5; // Move to the next separator
            move(y,x); // Move to next separator coordinates
        } // of for (n=0)
        x = (lastSizes->leftCol)+4; // Get to the first column
        y = y+2; // Get to next row
        move(y,x); // Move cursor to next separator coordinates
    } // of for (i=0)
}
void refreshScreen(tile_t **playingField, long long int score) {
    int maxX, maxY; // Save screensize here.
    getmaxyx(stdscr,maxX,maxY); // Get screen dimensions
    int result = cmpSize();
    if (result > 0) {
        calculateTileCoordinates(playingField);
        redrawGrid();
    } // of if (result)
    // Display playingfield, don't fill it with numbers now
    int xrow = 0;
    int ycol = 0;
    int borderx=0;
    int bordery=0;
    for (int row = 0; row < 4; row++) { // For each row...
        for (int col = 0; col < 4; col++) { // ...and each column
            xrow = playingField[row][col].uiystart;
            ycol = playingField[row][col].uixstart;
            // Write each value backwards
            int num = 3;
            int numI = playingField[row][col].value; // Select field
            mvprintw(xrow,ycol,"    ");
            while (numI > 0) { // As long as not all numbers have been printed
                // Display the current number
                mvprintw(xrow,ycol+num,"%i",numI%10);
                num--; // Get one character to the left
                numI=numI/10; // Div value by 10 (shift this number)
            } // of while (numI > 0)
        } // of for (col=0)
    } // of for (row=0)
    mvprintw(maxX-2,0,"Score: %i",score); // Display Scorerow at the end of the screen
    refresh(); // Redraw screen
}
