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
 * Define al functions regarding Tiles and Tilelists here to avoid recursive includes.
 */
 
#include <stdlib.h>
#include <stdbool.h>

// Define a single tile in our playing Field.
typedef struct _tile {
    int value; // Displayed Value on screen
    int colorCode; // Used color code
    unsigned int uixstart;
    unsigned int uiystart;
} tile_t;

// Define an item in a linked list of tiles
typedef struct _tileListItem {
    tile_t* fieldTile; // Content of this list item
    struct _tileListItem* nextTile; // Pointer to the next item in this list
} tileListItem_t;

/* List functions.
 * Implemented in: tilel.c
 */

/**
 * Add a new item to a list, move start of list to this new item
 * 
 * @param list Current start of list
 * @param newTile New Item to be added
 * @return 1 if adding was successful, else 0
 */
int addTileItem(tileListItem_t **list, tile_t* newTile);

/**
 * Delete all items in this list
 * @param list First item of List
 */
void freeList(tileListItem_t *list);

/**
 * Search for element pos in list and return the content
 * 
 * @param list First item of List
 * @param pos Position to be searched
 * @return Value at pos
 */
tile_t* getElementAtPosition(tileListItem_t *list, unsigned int pos);

/**
 * Count number of items in list
 * 
 * @param list First item of List
 * @return Number of items in List
 */
unsigned int getListSize(tileListItem_t *list);
