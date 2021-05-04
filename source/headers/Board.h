#ifndef MINESWEEPER_BOARD_H
#define MINESWEEPER_BOARD_H

class Board
{
public:
    Board();
    ~Board();
    void setValue(int value);
    void random();
    int getValue(const int& x, const int& y) const;
    void updateValue(const int& x, const int& y, const int& value);

private:
    int** board;
    void increaseAround(const int& x, const int& y);
};

#endif //MINESWEEPER_BOARD_H
