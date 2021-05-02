#include "headers/Game.h"
#include "headers/LaunchGame.h"
#include "headers/Replay.h"
#include "headers/Sound.h"


const char* WINDOW_TITLE = "Minesweeper";
const int WINDOW_WIDTH = 600;
const int WINDOW_HEIGHT = 900;

int main(int argc, char* argv[])
{

    Game* game = new Game(); //create new game

    //initialize game
    game->Init(WINDOW_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT);

    LaunchGame* launch = new LaunchGame();    //create launch
    Sound* audio = new Sound();   //initialize sound
    Replay* rePlay = new Replay();   //for replaying


    do
    {
        Sound::play(Sound::openingMusic);
        launch->Start();

        if (Game::isRunning)
        {
            Mix_PauseMusic();
            game->createBoard();
            game->printBoard();
        }
        while (Game::isRunning)
        {
            game->handleEvents();
            game->render();
        }

        rePlay->endScreen(WINDOW_WIDTH, WINDOW_HEIGHT);

        game->shutDown();
    } while (Replay::replay);

    delete launch;
    delete game;
    delete audio;
    delete rePlay;

    return 0;
}
