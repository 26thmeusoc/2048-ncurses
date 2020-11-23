/*
 * 2048 built in C with ncurses.
 * 
 * Author: Dirk Braun
 * Web: http://github.com/26thmeusoc/2048-ncurses
 * 
 * File created:  16.11.2020
 * Last modified: 21.11.2020
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
    tileListItem_t *buffer = malloc(sizeof(tileListItem_t));
    if (buffer == NULL) {
        // Could not allocate enough memory!
        return false;
    }
    buffer->nextTile = *list;
    *list = buffer;
    buffer->fieldTile = newTile;
    return true;
}

void freeList(tileListItem_t *list) {
    tileListItem_t *listItem = list;
    while (listItem != NULL) {
        tileListItem_t *buffer = listItem->nextTile;
        free(listItem);
        listItem = buffer;
    }
}

tile_t* getElementAtPosition(tileListItem_t *list, unsigned int pos) {
    int counter = 0;
    while (list != NULL && pos < counter) {
        list = list->nextTile;
        counter++;
    }
    return list->fieldTile;
}
