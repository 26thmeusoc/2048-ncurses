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

#ifndef DEFGAME
#include "game.h" // For game internals
#define DEFGAME
#endif

#ifndef DEFTILE
#include "tile.h"
#define DEFTILE
#endif

typedef struct _screenSizes {
    int maxWidth;
    int maxHeight;
    int midx;
    int midy;
    int leftCol;
    int upperLine;
} screenSizes;

/**
 * Recalculate position of tiles on screen.
 * 
 * Fill coordinates in playingField tiles with their on screen
 * coordinates. This allows easier jumping to when redrawing the screen.
 * 
 * @pre lastSizes set to current Values
 */
void calculateTileCoordinates(tile_t** playingField);

/**
 * Redraw grid of playingField.
 * 
 * Draws grid on playing field.
 * 
 * @pre lastSizes set to current Values
 */
void redrawGrid();

/**
 * Compare current screenSize with size of last move.
 * 
 * @return 1 if size of screen has changed, otherwise 0.
 */
int cmpSize();

/**
 * Redraw fields on screen.
 * 
 * Redraw the complete playingfield on screen.
 * 
 * @param playingField Currently played Field
 * @param score Current Score
 */
void refreshScreen(tile_t** playingField, long long int score);
