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
 * 
 * How this works:
 * 
 * All functions are implemented like BubbleSort:
 * 1. Compare all cells (direction is given with shifting direction).
 *    [ 4 ] -?-> [ 0 ]
 * 2. If a switch has to be made, do it!
 *    [ 0 ]      [ 4 ]
 * 3. Compare all fields again as long as switches were made
 */

#include "movements.h"

int moveLeft(int** playingField, long long int *score) {
    int moved = 1; // Remember whether there was a move (for loops)
    int maxX, maxY; // Remember screendimensions
    int result = 0; // Was there a useful move done?
    // First of all, move all tiles to the left, replace 0-fields with value next to them
    while (moved > 0) { // As long as there was a move last time
        moved=0; // Reset moved-variable, so we can check again, whether there was something done in this loop
        for (int row = 0; row < 4; row++) { // For every row
            for (int col = 0; col < 3; col++) { // in each column
                if ((playingField[row][col] == 0) && (playingField[row][col+1] > 0)) { // Is the current field a 0 and has a field with value > 0 to the right?
                    // Yes! Switch those fields
                    playingField[row][col] = playingField[row][col+1];
                    playingField[row][col+1] = 0;
                    moved = 1; // Remember, there was a loop iteration in this move
                    result = 1; // There was at least one useful move done (moved a 0 field to the right) in this call, remember it for later
                }
            }
        }
    }
    
    // Now check if there can be any merges made!
    for (int row = 0; row < 4; row++) { // For each row
        for (int col = 0; col < 3; col++) { // in each column
            // Are this cell and the cell to the right are the same value AND both are not 0?
            // Second check is imporant, so we don't make useless merges
            if ((playingField[row][col] == playingField[row][col+1]) && (playingField[row][col] > 0)) {
                *score += playingField[row][col]*2; // Add to score
                playingField[row][col] = playingField[row][col]*2; // Merge two cells
                playingField[row][col+1] = 0; // Reset value of second cell
                result = 1; // There was at least one useful move done (merging two cells) in this call, remember it for later
            }
        }
    }
    
    /*
     * In case there were cells merged in the step before, we need
     * to remove newly created cells with value=0 
     */
    if (result > 0) { // Was there anything useful done up until here? If not, we can just skip this step
        moved=1; // Set this to 1 so we get into the loop
        while (moved > 0) { // As long as there was a move last time
            moved = 0; // Reset to 0, check again whether there was done something useful
            for (int row = 0; row < 4; row++) { // For every row
                for (int col = 0; col < 3; col++) { // in each column
                    if ((playingField[row][col] == 0) && (playingField[row][col+1] > 0)) { // Is there a cell with value > 0 to the right?
                        // Yes, move it to the left now
                        playingField[row][col] = playingField[row][col+1];
                        playingField[row][col+1] = 0;
                        moved = 1; // There was at least one useful move done (moved a 0 field to the right) in this call, remember it for later
                    }
                }
            }
        }
    }
    
    return result;
}

int moveRight(int **playingField, long long int *score) {
    int moved = 1; // Remember whether there was a move (for loops)
    int result = 0; // Was there a useful move done?
    // First of all, move all tiles to the left, replace 0-fields with value next to them
    while (moved > 0) { // As long as there was a move last time
        moved=0;// Reset moved-variable, so we can check again, whether there was something done in this loop
        for (int row = 0; row < 4; row++) { // For every row
            for (int col = 3; col > 0; col--) { // in each column
                if ((playingField[row][col] == 0) && (playingField[row][col-1] > 0)) { // Is the current field a 0 and has a field with value > 0 to the right?
                    // Yes! Switch those fields
                    playingField[row][col] = playingField[row][col-1];
                    playingField[row][col-1] = 0; // Reset value of second cell
                    moved = 1; // Remember, there was a loop iteration in this move
                    result = 1; // There was at least one useful move done (moved a 0 field to the left) in this call, remember it for later
                }
            }
        }
    }
    
    // Now check if there can be any merges made!
    for (int row = 0; row < 4; row++) { // For each row
        for (int col = 3; col > 0; col--) { // in each column
            if ((playingField[row][col] == playingField[row][col-1]) && (playingField[row][col] > 0)) { // Are this cell and the cell to the left are the same value AND both are not 0?
            // Second check is imporant, so we don't make useless merges
                *score += playingField[row][col]*2; // Add to score
                playingField[row][col] = playingField[row][col]*2; // Merge two cells
                playingField[row][col-1] = 0; // Reset value of second cell
                result = 1; // There was at least one useful move done (merging two cells) in this call, remember it for later
            }
        }
    }
    
    /*
     * In case there were cells merged in the step before, we need
     * to remove newly created cells with value=0 
     */
    if (result > 0) {
        moved=1;
        // Remove 0s again
        while (moved > 0) { // As long as there was a move last time
            moved = 0;
            for (int row = 0; row < 4; row++) { // For every row
                for (int col = 3; col > 0; col--) { // in each column
                    if ((playingField[row][col] == 0) && (playingField[row][col-1] > 0)) { // Is the current field a 0 and has a field with value > 0 to the left?
                        // Yes, move it to the right now
                        playingField[row][col] = playingField[row][col-1];
                        playingField[row][col-1] = 0;
                        moved = 1; // There was at least one useful move done (moved a 0 field to the right) in this call, remember it for later
                    }
                }
            }
        }
    }
    
    return result;
}

int moveUp(int ** playingField, long long int *score) {
    int result = 0; // Was there a useful move done?
    int moved = 1; // Remember whether there was a move (for loops)
    // First of all, move all tiles to the left, replace 0-fields with value next to them
    while (moved > 0) { // As long as there was a move last time
        moved=0;
        for (int row = 0; row < 3; row++) { // For every row
            for (int col = 0; col < 4; col++) { // in each column
                if ((playingField[row][col] == 0) && (playingField[row+1][col] > 0)) { // Is the current field a 0 and has a field with value > 0 above?
                    // Yes! Switch those fields
                    playingField[row][col] = playingField[row+1][col];
                    playingField[row+1][col] = 0; // Reset value of second cell
                    moved = 1; // Remember, there was a loop iteration in this move
                    result = 1; // There was at least one useful move done (moved a 0 field down) in this call, remember it for later
                }
            }
        }
    }
    
    // Now check if there can be any merges made!
    for (int row = 0; row < 3; row++) { // For each row
        for (int col = 0; col < 4; col++) { // in each column
            // Are this cell and the cell above are the same value AND both are not 0?
            // Second check is imporant, so we don't make useless merges
            if ((playingField[row+1][col] == playingField[row][col]) && (playingField[row][col] > 0)) {
                *score += playingField[row][col]*2; // Add to score
                playingField[row][col] = playingField[row][col]*2; // Merge two cells
                playingField[row+1][col] = 0; // Reset value of second cell
                result = 1; // There was at least one useful move done (merging two cells) in this call, remember it for later
            }
        }
    }
    
    /*
     * In case there were cells merged in the step before, we need
     * to remove newly created cells with value=0 
     */
    if (result > 0) {
        moved=1;
        // Remove 0s again
        while (moved > 0) { // As long as there was a move last time
            moved = 0;
            for (int row = 0; row < 3; row++) { // For every row
                for (int col = 0; col < 4; col++) { // in each column
                    if ((playingField[row][col] == 0) && (playingField[row+1][col] > 0)) { // Is the current field a 0 and has a field with value > 0 below?
                        // Yes, move it down now
                        playingField[row][col] = playingField[row+1][col];
                        playingField[row+1][col] = 0;
                        moved = 1; // There was at least one useful move done (moved a 0 field to the right) in this call, remember it for later
                    }
                }
            }
        }
    }
    
    return result;
}

int moveDown(int **playingField, long long int *score) {
    int result = 0; // Was there a useful move done?
    int moved = 1; // Remember whether there was a move (for loops)
    // First of all, move all tiles to the left, replace 0-fields with value next to them
    while (moved > 0) { // As long as there was a move last time
        moved=0;
        for (int row = 3; row > 0; row--) { // For every row
            for (int col = 0; col < 4; col++) { // in each column
                if ((playingField[row][col] == 0) && (playingField[row-1][col] > 0)) { // Is the current field a 0 and has a field with value > 0 below?
                    // Yes! Switch those fields
                    playingField[row][col] = playingField[row-1][col];
                    playingField[row-1][col] = 0; // Reset value of second cell
                    moved = 1; // Remember, there was a loop iteration in this move
                    result = 1; // There was at least one useful move done (moved a 0 field to the up) in this call, remember it for later
                }
            }
        }
    }
    
    // Now check if there can be any merges made!
    for (int row = 3; row > 0; row--) {  // For each row
        for (int col = 0; col < 4; col++) { // in each column
            if ((playingField[row][col] == playingField[row-1][col]) && (playingField[row][col] > 0)) { // Are this cell and the cell below are the same value AND both are not 0?
            // Second check is imporant, so we don't make useless merges
                *score += playingField[row][col]*2; // Add to score
                playingField[row][col] = playingField[row-1][col]*2;
                // Merge two cells
                playingField[row-1][col] = 0; // Reset value of second cell
                result = 1; // There was at least one useful move done (merging two cells) in this call, remember it for later
            }
        }
    }
    
    /*
     * In case there were cells merged in the step before, we need
     * to remove newly created cells with value=0 
     */
    if (result > 0) { // Do this only, if there was a movement before!
        moved=1;
        // Remove 0s again
        while (moved > 0) { // As long as there was a move last time
            moved = 0;
            for (int row = 3; row > 0; row--) { // For every row
                for (int col = 0; col < 4; col++) { // in each column
                    if ((playingField[row][col] == 0) && (playingField[row-1][col] > 0)) { // Is the current field a 0 and has a field with value > 0 above?
                        // Yes, move it up now
                        playingField[row][col] = playingField[row-1][col];
                        playingField[row-1][col] = 0;
                        moved = 1; // There was at least one useful move done (moved a 0 field to the right) in this call, remember it for later
                    }
                }
            }
        }
    }
    
    return result;
}
