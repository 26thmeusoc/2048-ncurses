/*
 * 2048 built in C with ncurses.
 * 
 * Author: Dirk Braun
 * Web: http://github.com/26thmeusoc/2048-ncurses
 * 
 * File created:  14.10.2020
 * Last modified: 22.10.2020
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

# include "game.h"

// Define a Data-Construct here. Every x has a corresponding y,
// so remember both.
// Afterwards create a new datatype out of it, so it easier to use.
typedef struct _gameCoords {
    unsigned int xCoord;
    unsigned int yCoord;
} gameCoords_t;


typedef struct _game {
    unsigned int moves;
    unsigned int score;
} game_t;

int movePossible(tile_t **playingField) {
    // 1. Is there at least one empty field left?
    for (int r = 0; r < 4; r++) { // Check each row
        for (int c = 0; c < 4; c++) { // Check each column
            if (playingField[r][c].value == 0) { // Is row/column an empty field?
                return 1; // Yes! Quit this function already, return 1
            }
        }
    }
    
    // 2. Can two neighbouring fields get combined?
    for (int r = 0; r < 3; r++) { // Check each row
        for (int c = 0; c < 3; c++) { // Check each column
            if (playingField[r][c].value == playingField[r][c+1].value || playingField[r][c].value == playingField[r+1][c].value) { // Can field to the right or below get combined?
                return 1; // Yes! Quit this function, return 1
            }
        }
    }
    
    // Both functions didn't come up with a possible move. Return 0
    return 0;
}

void fillEmptyField(tile_t **playingField) {
    /* Instead of simply randomly searching for empty fields until
     * one is found (can take a very long time!), generate a list
     * of empty fields and choose one of them.
     */
    int counter = 0; // Count how many empty fields have been found
    
    /* Generate two lists, remember which row and column combination,
     * sizes have to be number of all available fields.
     */
    tileListItem_t* listStart= NULL;
    gameCoords_t* position = malloc(16*sizeof(gameCoords_t));
    //int* cell = malloc(16*sizeof(gameCoords));
    for (int r = 0; r < 4; r++) { // For every row
        for (int c = 0; c < 4; c++) { // For every column
            if (playingField[r][c].value == 0) { // Is this field empty?
                /*position[counter].xCoord = r; // Yes, remember row...
                position[counter].yCoord = c; // ...and column coordinate*/
                addTileItem(&listStart,&playingField[r][c]);
                counter++; // Increase counter
            }
        }
    }
    
    int field = rand() % counter; // Select one random field
    
    // With a chance of 5:2 ...
    if ((rand()%7) < 5) {
        // ... set value of this field with 2
        playingField[position[field].xCoord][position[field].yCoord].value = 2;
    } else { // ... set value to 4
        playingField[position[field].xCoord][position[field].yCoord].value = 4;
    }
    free(position); // Free list, so we don't leak memory with every move
}
