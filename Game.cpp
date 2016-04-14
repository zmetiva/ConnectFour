#include "Game.h"

Game::Game()
{
    gameBoard = new Board();
    newGame();

    hasQuit = false;
}

Game::~Game()
{
    delete gameBoard;
}


void Game::handleEvents() {


    while( SDL_PollEvent( &e ) != 0 ) {


        if( e.type == SDL_QUIT ) {
            hasQuit = true;
        }
        else if( e.type == SDL_KEYDOWN ) {

            switch( e.key.keysym.sym ) {
                case SDLK_ESCAPE:
                    hasQuit = true;
                    break;
                case SDLK_RETURN:
                    this->newGame();
                    break;

                case SDLK_1:
                    nextTurn(0);
                    break;

                case SDLK_2:
                    nextTurn(1);
                    break;

                case SDLK_3:
                    nextTurn(2);
                    break;

                case SDLK_4:
                    nextTurn(3);
                    break;

                case SDLK_5:
                    nextTurn(4);
                    break;

                case SDLK_6:
                    nextTurn(5);
                    break;

                case SDLK_7:
                    nextTurn(6);
                    break;
            }
        }
    }
}

void Game::nextTurn(int col) {
    turnNum+=gameBoard->placeDiskAt(col, turnNum%2, true);
    gameOver = checkWinner(col);
    if (!gameOver && turnNum%2 == 1) monteCarloPlay();
    displayWinner();
}

bool Game::isOver() {
    return gameOver;
}

bool Game::isClosed() {
    return hasQuit;
}

void Game::setGameOver(bool value) {
    gameOver = value;
}

bool Game::checkWinner(int index) {

    if (checkHorizontial(index)) {
        return true;
    }
    else if (checkVertical(index)) {
        return true;
    }
    else if (checkDiagonal(index)) {
        return true;
    }

    return false;
}

bool Game::checkVertical(int col) {
    int counter = 0;

    int row = gameBoard->getTrackValue(col);

    int mapValue = gameBoard->getMapValue(row, col);
    int tempMapValue = mapValue;

    while (tempMapValue == (turnNum - 1)%2) {
        //printf("%i,%i\n", row, col);
        counter++;
        tempMapValue = gameBoard->getMapValue(++row, col);
    }


    if(counter >= 4) {
        return true;
    }

    return false;


}

bool Game::checkHorizontial(int col) {
    int counter = 0;

    int row = gameBoard->getTrackValue(col);

    int tempCol = col;

    int mapValue = gameBoard->getMapValue(row, col);
    int tempMapValue = mapValue;

    //printf("%i\n", mapValue);

    while (tempMapValue == (turnNum - 1)%2) {
        counter++;
        //printf("%i,%i\n", row, tempCol);

        tempMapValue = gameBoard->getMapValue(row, --tempCol);

    }
    tempCol = col;
    tempMapValue = gameBoard->getMapValue(row, ++tempCol);


    while (tempMapValue == (turnNum - 1)%2) {
        //printf("%i,%i\n", row, tempCol);
        tempMapValue = gameBoard->getMapValue(row, ++tempCol);
        counter++;
    }

    if(counter >= 4) {
        return true;
    }

    return false;


}

bool Game::checkDiagonal(int col) {
    int counter = 0;

    int row = gameBoard->getTrackValue(col);

    int tempCol = col;
    int tempRow = row;

    int mapValue = gameBoard->getMapValue(row, col);
    int tempMapValue = mapValue;

    while (tempMapValue == (turnNum - 1)%2) {
        //printf("%i,%i\n", tempRow, tempCol);
        counter++;
        tempMapValue = gameBoard->getMapValue(--tempRow, --tempCol);
        //printf("Diag #1: %i\n", counter);
    }

    tempRow = row;
    tempCol = col;

    tempMapValue = gameBoard->getMapValue(++tempRow, ++tempCol);

    while (tempMapValue == (turnNum - 1)%2) {
       // printf("%i,%i\n", row, tempCol);
        counter++;
        tempMapValue = gameBoard->getMapValue(++tempRow, ++tempCol);
        //printf("Diag #1: %i\n", counter);
    }

    if(counter >= 4) {
        return true;
    }

    counter = 0;
    tempMapValue = mapValue;
    tempCol = col;
    tempRow = row;

    //printf("Diag #2: %i\n", counter);

    while (tempMapValue == (turnNum - 1)%2) {
        //printf("%i,%i\n", row, tempCol);
        counter++;
        tempMapValue = gameBoard->getMapValue(--tempRow, ++tempCol);
        //printf("Diag #2: %i\n", counter);
    }
    tempRow = row;
    tempCol = col;
    tempMapValue = gameBoard->getMapValue(++tempRow, --tempCol);

    //printf("HERE");

    while (tempMapValue == (turnNum - 1)%2) {
        //printf("%i,%i\n", row, tempCol);
        counter++;
        tempMapValue = gameBoard->getMapValue(++tempRow, --tempCol);
        //printf("Diag #2: %i\n", counter);
    }

    if(counter >= 4) {
        return true;
    }

    return false;

}

void Game::displayWinner() {
    if (gameOver)
        gameBoard->displayWinner(turnNum%2);
}

void Game::monteCarloPlay() {

    int counter = 0;
    int hit = 0;

    int popularPlay = 0;
    int columnPlayed = 0;

    int falseTurnNum = turnNum;
    bool falseGameOver = false;
    bool catGame = false;

    int backupMap[BOARD_ROWS][BOARD_COLS];
    int backupTrack[BOARD_COLS] = {5};

    int columnList[BOARD_COLS] = {1};
    int columnHits[BOARD_COLS] = {1};

    for (int i = 0; i < BOARD_COLS; i++) {
        backupTrack[i] = gameBoard->getTrackValue(i)-1;
        columnHits[i] = 1;
        columnList[i] = 1;
    }

    for (int i = 0; i < BOARD_ROWS; i++) {
        for (int j = 0; j < BOARD_COLS; j++) {
            backupMap[i][j] = gameBoard->getMapValue(i,j);
        }
    }

    srand (time(NULL));

    while (counter < MONTE_CARLO_SMART) {
        //printf("%i\n",i);

        columnPlayed = rand() % 7;
        popularPlay = columnPlayed;
        columnList[popularPlay] += 1;


        while(!falseGameOver) {

            hit = gameBoard->placeDiskAt(columnPlayed, turnNum%2, false);

            while (hit == 0) {
                columnPlayed = rand() % 7;
                if (turnNum == falseTurnNum) {
                    popularPlay = columnPlayed;
                    columnList[popularPlay] += 1;
                }

                hit = gameBoard->placeDiskAt(columnPlayed, turnNum%2, false);

            }

            turnNum+=1;

            falseGameOver = checkWinner(columnPlayed);

            columnPlayed = rand() % 7;

            if (turnNum == 42) {
                falseGameOver = true;
                columnList[popularPlay] -= 1;
                catGame = true;
                //turnNum = turnNum;
            }
        }

        if (turnNum%2 == 0 && !catGame) {
            //printf("I WON IT: %i:\n", turnNum);
            columnHits[popularPlay] += 1;
            //printf("%i: %i/%i\n", popularPlay, columnHits[popularPlay], columnList[popularPlay]);
        }

        for (int i = 0; i < BOARD_COLS; i++) {
            gameBoard->setTrackValue(i, backupTrack[i]);
            //printf("%i", backupTrack[i]);

        }

        for (int i = 0; i < BOARD_ROWS; i++) {

            for (int j = 0; j < BOARD_COLS; j++) {
                gameBoard->setMapValue(i,j,backupMap[i][j]);
            }
        }


        falseGameOver = false;
        catGame = false;
        turnNum = falseTurnNum;
        counter++;
    }

    double maxi = (double(columnHits[0])/double(columnList[0]));

    int play = 0;


    for (int i = 1; i < BOARD_COLS; i++) {
        if ((double(columnHits[i])/double(columnList[i])) > maxi) {
            maxi = (double(columnHits[i])/double(columnList[i]));
            play = i;
        }
    }

    printf("I AM PLAYING COLUMN %i WITH AN %2.f%% (%i/%i) CHANCE TO BEAT YOU!\n",play,maxi*100, columnHits[play], columnList[play]);

    turnNum+=gameBoard->placeDiskAt(play, turnNum%2, true);
    gameOver = checkWinner(play);
}

void Game::newGame() {

    gameBoard->resetBoard();
    gameOver = false;
    turnNum = 0;
}

