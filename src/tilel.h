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

#include <stdbool.h>

#include "game.h"


typedef struct _tileListItem {
    tile_t* fieldTile;
    tileListItem_t* nextTile;
} tileListItem_t;

int addTileItem(tileListItem_t **list, tile_t* newTile);

void freeList(tileListItem_t *list);
