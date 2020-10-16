/*
 * Author: Dirk Braun
 * Web: http://github.com/26thmeusoc/2048-ncurses
 * 
 * File created:  14.10.2020
 * Last modified: 16.10.2020
 * 
 * Description:
 * Define all needed commands for shifting tiles in playingfield.
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
int moveLeft(int **playingField, long long int *score);

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
int moveRight(int **playingField, long long int *score);

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
int moveUp(int **playingField, long long int *score);

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
int moveDown(int **playingField, long long int *score);
