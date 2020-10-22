# include "game.h"

int movePossible(int **playingField) {
    // 1. Is there at least one empty field left?
    for (int r = 0; r < 4; r++) { // Check each row
        for (int c = 0; c < 4; c++) { // Check each column
            if (playingField[r][c] == 0) { // Is row/column an empty field?
                return 1; // Yes! Quit this function already, return 1
            }
        }
    }
    
    // 2. Can two neighbouring fields get combined?
    for (int r = 0; r < 3; r++) { // Check each row
        for (int c = 0; c < 3; c++) { // Check each column
            if (playingField[r][c] == playingField[r][c+1] || playingField[r][c] == playingField[r+1][c]) { // Can field to the right or below get combined?
                return 1; // Yes! Quit this function, return 1
            }
        }
    }
    
    // Both functions didn't come up with a possible move. Return 0
    return 0;
}

void fillEmptyField(int **playingField) {
    /* Instead of simply randomly searching for empty fields until
     * one is found (can take a very long time!), generate a list
     * of empty fields and choose one of them.
     */
    int counter = 0; // Count how many empty fields have been found
    
    /* Generate two lists, remember which row and column combination,
     * sizes have to be number of all available fields.
     */
    int* row = malloc(16*sizeof(int));
    int* cell = malloc(16*sizeof(int));
    for (int r = 0; r < 4; r++) { // For every row
        for (int c = 0; c < 4; c++) { // For every column
            if (playingField[r][c] == 0) { // Is this field empty?
                row[counter] = r; // Yes, remember row...
                cell[counter] = c; // ...and column coordinate
                counter++; // Increase counter
            }
        }
    }
    
    int field = rand() % counter; // Select one random field
    
    // With a chance of 5:2 ...
    if ((rand()%7) < 5) {
        // ... set value of this field with 2
        playingField[row[field]][cell[field]] = 2;
    } else { // ... set value to 4
        playingField[row[field]][cell[field]] = 4;
    }
    free(row); // Free both lists, so we don't leak memory
    free(cell);
}
