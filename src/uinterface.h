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

#include <ncurses.h>
#include <stdlib.h>

typedef struct _screenSizes {
    int maxWidth;
    int maxHeight;
} screenSizes;


int cmpSize();

/**
 * Redraw fields on screen.
 * 
 * Redraw the complete playingfield on screen.
 */
void refreshScreen(int** playingField, long long int score);
