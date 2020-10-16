/*
 * Author: Dirk Braun
 * Web: http://github.com/26thmeusoc/2048-ncurses
 * 
 * File created:  14.10.2020
 * Last modified: 15.10.2020
 * 
 * Description:
 * Define all needed commands for shifting tiles in playingfield.
 */

#include <ncurses.h>

int moveLeft(int **playingField, long long int *score);

int moveRight(int **playingField, long long int *score);

int moveUp(int **playingField, long long int *score);

int moveDown(int **playingField, long long int *score);
