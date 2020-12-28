/*
 * 2048 built in C with ncurses.
 * 
 * Author: Dirk Braun
 * Web: http://github.com/26thmeusoc/2048-ncurses
 * 
 * File created:  16.11.2020
 * Last modified: 23.11.2020
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
 */

#include "tile.h"

int addTileItem(tileListItem_t **list, tile_t* newTile) {
    // Create a new List item
    tileListItem_t *buffer = malloc(sizeof(tileListItem_t));
    if (buffer == NULL) { // New item created?
        // No! Could not allocate enough memory!
        return 0;
    } // of if (buffer)
    buffer->nextTile = *list; // Next pointer of new item points to head of list
    *list = buffer; // Move Headpointer of list to new pointer
    buffer->fieldTile = newTile; // Set value of new Listhead
    return 1; // Everything went okay
}

void freeList(tileListItem_t *list) {
    tileListItem_t *listItem = list; // Point to first item in list
    while (listItem != NULL) { // As long, as there are still fields ...
        tileListItem_t *buffer = listItem->nextTile; // Remember next item
        free(listItem); // Free first Item in List
        listItem = buffer; // Move pointer to next item in lists
    } // of while (listItem != NULL)
}

tile_t* getElementAtPosition(tileListItem_t *list, unsigned int pos) {
    while (list != NULL && pos > 0) { // As long as there are items and pos is still not reached
        list = list->nextTile; // Go to next item in list
        pos--; // Decrease pos
    } // of while (list != NULL)
    // @TODO Fix access to NULL Field
    return list->fieldTile; // Return content of current pointer
}

unsigned int getListSize(tileListItem_t *list) {
    // Start counting
    unsigned int counter = 0;
    while (list != NULL) { // As long as there are still items in this list
        list = list->nextTile; // Go to next item
        counter++; // Increase counter
    } // of while (list != NULL)
    return counter; // Return result
}
