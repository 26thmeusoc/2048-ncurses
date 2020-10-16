int moveLeft(int** playingField) {
    int moved = 1;
    while (moved > 0) {
        moved = 0;
        for (int row = 0; row < 4; row++){
            for(int col = 0; col < 3; col++) {
                if (playingField[row][col] == playingField[row][col+1] && playingField[row][col] != 0) {
                    playingField[row][col] = playingField[row][col]*2;
                    moved = 1;
                }
                if ((playingField[row][col] == 0) && (playingField[row][col+1] > 0)) {
                    playingField[row][col] = playingField[row][col+1];
                    playingField[row][col+1]=0;
                    moved = 1;
                }
            }
        }
    }
    return 0;
}

int moveRight() {
    int moved = 1;
    while (moved > 0) {
        moved = 0;
        for (int row = 0; row < 4; row++){
            for(int col = 3; col > 0; col--) {
                if (playingField[row][col] == playingField[row][col-1] && playingField[row][col] != 0) {
                    playingField[row][col] = playingField[row][col]*2;
                    moved = 1;
                }
                if ((playingField[row][col] == 0) && (playingField[row][col-1] > 0)) {
                    playingField[row][col] = playingField[row][col-1];
                    playingField[row][col]=0;
                    moved = 1;
                }
            }
        }
    }
    return 0;
}

int moveUp() {
    return 1;
}

int moveDown() {
    return 1;
}
