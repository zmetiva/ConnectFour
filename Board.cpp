#include "Board.h"

Board::Board()
{
    //The window we'll be rendering to
    this->window = NULL;

    //The surface contained by the window
    this->screenSurface = NULL;

    this->boardImage = NULL;
    this->yellowImage = NULL;
    this->redImage = NULL;

    winnerOneImage = NULL;
    winnerTwoImage = NULL;

    winnerRect.x = SCREEN_WIDTH/2 - 200;
    winnerRect.y = SCREEN_HEIGHT/2 - 100;
    winnerRect.w = 400;
    winnerRect.h = 200;



	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
	}
	else
	{
		//Create window
		window = SDL_CreateWindow( "Connect Four", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( window == NULL )
		{
			printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
		}
		else
		{
			//Get window surface
			this->screenSurface = SDL_GetWindowSurface( window );

			//Fill the surface white
			SDL_FillRect( this->screenSurface, NULL, SDL_MapRGB( screenSurface->format, 0x00, 0x00, 0xFF ) );

            //Load splash image
            this->boardImage = SDL_LoadBMP( "imgs/board.bmp" );

            if( this->boardImage == NULL ) {
                    printf( "Unable to load image %s! SDL Error: %s\n", "imgs/board.bmp", SDL_GetError() );
            }

            this->yellowImage = SDL_LoadBMP( "imgs/yellow.bmp" );

            if( this->yellowImage == NULL ) {
                    printf( "Unable to load image %s! SDL Error: %s\n", "imgs/yellow.bmp", SDL_GetError() );
            }

            this->redImage = SDL_LoadBMP( "imgs/red.bmp" );

            if( this->redImage == NULL ) {
                    printf( "Unable to load image %s! SDL Error: %s\n", "imgs/red.bmp", SDL_GetError() );
            }

            this->winnerOneImage = SDL_LoadBMP( "imgs/won.bmp" );

            if( this->winnerOneImage == NULL ) {
                    printf( "Unable to load image %s! SDL Error: %s\n", "imgs/won.bmp", SDL_GetError() );
            }

            this->winnerTwoImage = SDL_LoadBMP( "imgs/lost.bmp" );

            if( this->winnerTwoImage == NULL ) {
                    printf( "Unable to load image %s! SDL Error: %s\n", "imgs/lost.bmp", SDL_GetError() );
            }

            resetBoard();
		}
	}
}

Board::~Board()
{
    //Destroy window
	SDL_DestroyWindow( window );

	//Quit SDL subsystems
	SDL_Quit();
}

int Board::placeDiskAt(int btn, int player, bool actualPlay) {
    if (boardTrack[btn] >= 0 && boardTrack[btn] < BOARD_COLS) {

        stretchRect.x = (64 * btn + 30 * btn) + 14;
        stretchRect.y = (64 *boardTrack[btn] + 30*boardTrack[btn]) + 6;
        stretchRect.w = 64;
        stretchRect.h = 64;

        SDL_Surface* disk = NULL;

        switch (player) {
            case 0: disk = redImage; break;
            case 1: disk = yellowImage; break;
        }

        if (actualPlay == true) {

            SDL_BlitSurface(disk, NULL, screenSurface, &stretchRect);
            SDL_UpdateWindowSurface( window );
        }

        //printf("X: %i\tY:%i\n", btn + 1, boardTrack[btn] + 1);

        boardMap[boardTrack[btn]][btn] = player;

        boardTrack[btn] -= 1;

        return 1;
    }

    return 0;

}

void Board::setTrackValue(int index, int value) {
    boardTrack[index] = value;
}

int Board::getTrackValue(int index) {
    return boardTrack[index]+1;
}

void Board::setMapValue(int row, int col, int value) {
    boardMap[row][col] = value;
}

int Board::getMapValue(int row, int col) {
    if (row < BOARD_ROWS && row >= 0 && col < BOARD_COLS && col >= 0)
        return boardMap[row][col];

    else return -1;
}

void Board::displayWinner(int player) {

    if (player == 1) {
        SDL_BlitSurface(winnerOneImage, NULL, screenSurface, &winnerRect);
    }

    else {
        SDL_BlitSurface(winnerTwoImage, NULL, screenSurface, &winnerRect);
    }

    SDL_Delay(2000);


    SDL_UpdateWindowSurface(window);

}

void Board::resetBoard() {
    for (int i = 0; i < BOARD_COLS; i++) {
        boardTrack[i] = 5;

        for (int j = 0; j < BOARD_ROWS; j++) {
            boardMap[j][i] = -1;
        }
    }

    SDL_BlitSurface(boardImage, NULL, screenSurface, NULL);

    //Update the surface
    SDL_UpdateWindowSurface( window );

}
