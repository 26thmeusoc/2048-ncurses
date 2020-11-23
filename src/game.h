#include <stdlib.h>

/*
 * Author: Dirk Braun
 * Web: http://github.com/26thmeusoc/2048-ncurses
 * 
 * File created:  22.10.2020
 * Last modified: 22.10.2020
 * 
 * Description:
 * All functions needed for game internals.
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

#include "tile.h"


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
int movePossible(tile_t **playingField);

/**
 * Select a single field and add a value to it.
 * 
 * Searches the playing field for an empty field and adds a new
 * value to it.
 *
 * @param playingField
 */
void fillEmptyField(tile_t **playingField);
