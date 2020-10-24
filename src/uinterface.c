/*
 * 2048 built in C with ncurses.
 * 
 * Author: Dirk Braun
 * Web: http://github.com/26thmeusoc/2048-ncurses
 * 
 * File created:  23.10.2020
 * Last modified: 23.10.2020
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
    int newX, newY;
    getmaxyx(stdscr,newX,newY);
    if ((lastSizes == NULL)) {
        lastSizes = (screenSizes*) malloc(sizeof(screenSizes));
        lastSizes->maxWidth = newY;
        lastSizes->maxHeight = newX;
    } else if (lastSizes->maxWidth != newY || lastSizes->maxHeight != newX) {
        lastSizes->maxWidth = newY;
        lastSizes->maxHeight = newX;
        return 1;
    } else {
        return 0;
    }
}

void refreshScreen(int **playingField, long long int score) {
    int maxX, maxY; // Save screensize here.
    getmaxyx(stdscr,maxX,maxY); // Get screen dimensions
    int result = cmpSize();
    mvprintw(lastSizes->maxHeight-1,0,"Size is: x: %i, y: %i",lastSizes->maxWidth,lastSizes->maxHeight);
    // Display playingfield, don't fill it with numbers now
    int xrow = 0;
    int ycol = 0;
    int borderx=0;
    int bordery=0;
    for (int row = 0; row < 4; row++) { // For each row...
        ycol = 0;
        for (int col = 0; col < 4; col++) { // ...and each column
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
