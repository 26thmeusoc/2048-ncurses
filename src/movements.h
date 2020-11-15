/*
 * Author: Dirk Braun
 * Web: http://github.com/26thmeusoc/2048-ncurses
 * 
 * File created:  14.10.2020
 * Last modified: 22.10.2020
 * 
 * Description:
 * Define all needed commands for shifting tiles in playingfield.
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

#include <ncurses.h>

/**
 * Shift playingField to the left.
 * 
 * Moves all values to the left, adding same values next to each other.
 * Score will add values of merged fields.
 * 
 * @param playingField Field where changes will be done
 * @param score Current userscore.
 * @return 1 when move changed something in playingField, otherwise 0
 */
int moveLeft(tile_t **playingField, long long int *score);

/**
 * Shift playingField to the right.
 * 
 * Moves all values to the right, adding same values next to each other.
 * Score will add values of merged fields.
 * 
 * @param playingField Field where changes will be done
 * @param score Current userscore.
 * @return 1 when move changed something in playingField, otherwise 0
 */
int moveRight(tile_t **playingField, long long int *score);

/**
 * Shift playingField up.
 * 
 * Moves all values to the up, adding same values next to each other.
 * Score will add values of merged fields.
 * 
 * @param playingField Field where changes will be done
 * @param score Current userscore.
 * @return 1 when move changed something in playingField, otherwise 0
 */
int moveUp(tile_t **playingField, long long int *score);

/**
 * Shift playingField to the up.
 * 
 * Moves all values to the up, adding same values next to each other.
 * Score will add values of merged fields.
 * 
 * @param playingField Field where changes will be done
 * @param score Current userscore.
 * @return 1 when move changed something in playingField, otherwise 0
 */
int moveDown(tile_t **playingField, long long int *score);
