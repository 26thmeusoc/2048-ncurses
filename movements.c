int moveLeft(int** playingField) {
    int moved = 1;
    // First of all, move all tiles to the left, replace 0-fields with value next to them
    while (moved > 0) { // As long as there was a move last time
        moved=0;
        for (int row = 0; row < 4; row++) { // For every row
            for (int col = 0; col < 3; col++) { // in each column
                if ((playingField[row][col] == 0) && (playingField[row][col+1] > 0)) {
                    playingField[row][col] = playingField[row][col+1];
                    playingField[row][col+1] = 0;
                    moved = 1;
                }
            }
        }
    }
    
    // Now check if there can be any combinations made!
    for (int row = 0; row < 4; row++) {
        for (int col = 0; col < 3; col++) {
            if (playingField[row][col] == playingField[row][col+1]) {
                playingField[row][col] = playingField[row][col]*2;
                playingField[row][col+1] = 0;
            }
        }
    }
    
    // Remove 0s again
    while (moved > 0) { // As long as there was a move last time
        moved = 0;
        for (int row = 0; row < 4; row++) { // For every row
            for (int col = 0; col < 3; col++) { // in each column
                if ((playingField[row][col] == 0) && (playingField[row][col+1] > 0)) {
                    playingField[row][col] = playingField[row][col+1];
                    playingField[row][col+1] = 0;
                    moved = 1;
                }
            }
        }
    }
    
    return 0;
}

int moveRight(int **playingField) {
    int moved = 1;
    // First of all, move all tiles to the left, replace 0-fields with value next to them
    while (moved > 0) { // As long as there was a move last time
        moved=0;
        for (int row = 0; row < 4; row++) { // For every row
            for (int col = 3; col > 0; col--) { // in each column
                if ((playingField[row][col] == 0) && (playingField[row][col-1] > 0)) {
                    playingField[row][col] = playingField[row][col-1];
                    playingField[row][col-1] = 0;
                    moved = 1;
                }
            }
        }
    }
    
    // Now check if there can be any combinations made!
    for (int row = 0; row < 4; row++) {
        for (int col = 3; col > 0; col--) {
            if (playingField[row][col] == playingField[row][col-1]) {
                playingField[row][col] = playingField[row][col]*2;
                playingField[row][col-1] = 0;
            }
        }
    }
    
    // Remove 0s again
    while (moved > 0) { // As long as there was a move last time
        moved = 0;
        for (int row = 0; row < 4; row++) { // For every row
            for (int col = 3; col > 0; col--) { // in each column
                if ((playingField[row][col] == 0) && (playingField[row][col-1] > 0)) {
                    playingField[row][col] = playingField[row][col-1];
                    playingField[row][col-1] = 0;
                    moved = 1;
                }
            }
        }
    }
    
    return 0;
}

int moveUp(int ** playingField) {
    int moved = 1;
    // First of all, move all tiles to the left, replace 0-fields with value next to them
    while (moved > 0) { // As long as there was a move last time
        moved=0;
        for (int row = 0; row < 3; row++) { // For every row
            for (int col = 0; col < 4; col++) { // in each column
                if ((playingField[row][col] == 0) && (playingField[row+1][col] > 0)) {
                    playingField[row][col] = playingField[row+1][col];
                    playingField[row+1][col] = 0;
                    moved = 1;
                }
            }
        }
    }
    
    // Now check if there can be any combinations made!
    for (int row = 0; row < 3; row++) {
        for (int col = 0; col < 4; col++) {
            if (playingField[row+1][col] == playingField[row][col]) {
                playingField[row][col] = playingField[row][col]*2;
                playingField[row+1][col] = 0;
            }
        }
    }
    
    // Remove 0s again
    while (moved > 0) { // As long as there was a move last time
        moved = 0;
        for (int row = 0; row < 3; row++) { // For every row
            for (int col = 0; col < 4; col++) { // in each column
                if ((playingField[row][col] == 0) && (playingField[row+1][col] > 0)) {
                    playingField[row][col] = playingField[row+1][col];
                    playingField[row+1][col] = 0;
                    moved = 1;
                }
            }
        }
    }
    
    return 0;
}

int moveDown(int **playingField) {
    int moved = 1;
    // First of all, move all tiles to the left, replace 0-fields with value next to them
    while (moved > 0) { // As long as there was a move last time
        moved=0;
        for (int row = 3; row > 0; row--) { // For every row
            for (int col = 0; col < 4; col++) { // in each column
                if ((playingField[row][col] == 0) && (playingField[row-1][col] > 0)) {
                    playingField[row][col] = playingField[row-1][col];
                    playingField[row-1][col] = 0;
                    moved = 1;
                }
            }
        }
    }
    
    // Now check if there can be any combinations made!
    for (int row = 3; row > 0; row--) {
        for (int col = 0; col < 4; col++) {
            if (playingField[row][col] == playingField[row-1][col]) {
                playingField[row][col] = playingField[row-1][col]*2;
                playingField[row-1][col] = 0;
            }
        }
    }
    
    // Remove 0s again
    while (moved > 0) { // As long as there was a move last time
        moved = 0;
        for (int row = 3; row > 0; row--) { // For every row
            for (int col = 0; col < 4; col++) { // in each column
                if ((playingField[row][col] == 0) && (playingField[row-1][col] > 0)) {
                    playingField[row][col] = playingField[row-1][col];
                    playingField[row-1][col] = 0;
                    moved = 1;
                }
            }
        }
    }
    
    return 0;
}
