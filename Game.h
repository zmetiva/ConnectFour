#ifndef GAME_H
#define GAME_H

#include <stdlib.h>
#include <time.h>

#include "Board.h"

const int MONTE_CARLO_SMART = 100000;

class Game
{
    public:
        Game();
        virtual ~Game();

        bool isOver();
        void setGameOver(bool value);

        bool isClosed();

        void handleEvents();

        void displayWinner();

    protected:
    private:
        Board* gameBoard;

        bool gameOver;
        int turnNum;

        bool hasQuit;

        SDL_Event e;

        bool checkWinner(int btn);
        bool checkHorizontial(int row);
        bool checkVertical(int row);
        bool checkDiagonal(int row);

        void nextTurn(int col);

        void monteCarloPlay();

        void newGame();

};

#endif // GAME_H
