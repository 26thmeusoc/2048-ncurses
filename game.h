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
 */

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
int movePossible(int **playingField);

/**
 * Select a single field and add a value to it.
 * 
 * Searches the playing field for an empty field and adds a new
 * value to it.
 *
 * @param playingField
 */
void fillEmptyField(int **playingField);
