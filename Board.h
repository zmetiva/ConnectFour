#ifndef BOARD_H
#define BOARD_H

#include <SDL.h>
#include <stdio.h>

const int SCREEN_WIDTH = 658;
const int SCREEN_HEIGHT = 595;

const int BOARD_ROWS = 6;
const int BOARD_COLS = 7;


class Board
{
    public:
        Board();
        virtual ~Board();

        int placeDiskAt(int btn, int player, bool actualPlay);

        void setMapValue(int row, int col, int value);
        int getMapValue(int row, int col);

        void setTrackValue(int index, int value);
        int getTrackValue(int index);

        void displayWinner(int player);

        void resetBoard();

    protected:
    private:
        //The window we'll be rendering to
        SDL_Window* window;

        //The surface contained by the window
        SDL_Surface* screenSurface;

        SDL_Surface* boardImage;

        SDL_Surface* yellowImage;
        SDL_Surface* redImage;
        SDL_Rect stretchRect;

        SDL_Surface* winnerOneImage;
        SDL_Surface* winnerTwoImage;
        SDL_Rect winnerRect;

        int boardTrack[BOARD_COLS];
        int boardMap[BOARD_ROWS][BOARD_COLS];
};

#endif // BOARD_H
