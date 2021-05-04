#include "headers/Board.h"
#include "headers/Game.h"

#include <vector>
#include <cstdlib>
#include <ctime>


Board::Board() {}

Board::~Board()
{
    for (int i = 0; i < Game::heightOfGame; i++)
    {
        delete this->board[i];
    }

    delete this->board;
}

void Board::setValue(int value)
{
    this->board = new int*[Game::heightOfGame]; //set number of rows for board

    for (int i = 0; i < Game::heightOfGame; i++)
    {
        this->board[i] = new int[Game::widthOfGame]; //set number of columns

        for (int j = 0; j < Game::widthOfGame; j++)
        {
            this->board[i][j] = value; //set all board to value
        }
    }
}


void Board::random() // place mines in random positions
{
    srand(time(nullptr));

    std::vector<int> unSelected; //not selected squares

    int numberOfCells = Game::widthOfGame * Game::heightOfGame;
    int bombX, bombY;

    for (int i = 0; i < numberOfCells; i++)
    {
        unSelected.push_back(i);
    }

    for (int i = 0; i < Game::numberOfMines; i++)
    {
        int pos = rand() % unSelected.size();

        bombX = unSelected[pos] % Game::widthOfGame;
        bombY = unSelected[pos] / Game::widthOfGame;

        this->board[bombY][bombX] = mine;

        this->increaseAround(bombX, bombY);//increase numbers around bomb

        unSelected.erase(unSelected.begin() + pos); //delete selected squares
    }
}

int Board::getValue(const int& x, const int& y) const
{
    return this->board[y][x];
}

void Board::updateValue(const int& x, const int& y, const int& value)
{
    this->board[y][x] = value;
}

void Board::increaseAround(const int& x, const int& y)
{
    for (int i = -1; i <= 1; i++)
    {
        for (int j = -1; j <= 1; j++)
        {
            if (i != 0 || j != 0)
            {
                //make sure cell is within board
                if (x + j >= 0 && x + j < Game::widthOfGame && y + i >= 0 && y + i < Game::heightOfGame)
                {
                    if (this->board[y + i][x + j] != mine)
                    {
                        this->board[y + i][x + j]++;
                    }
                }
            }
        }
    }
}