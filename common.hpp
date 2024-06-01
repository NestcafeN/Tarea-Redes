#ifndef COMMON_HPP
#define COMMON_HPP

#include <vector>
#include <string>

#define ROWS 6
#define COLS 7

enum Cell
{
      EMPTY,
      PLAYER1,
      PLAYER2
};

class Game
{
public:
      Game();
      bool makeMove(int col, Cell player);
      bool checkWin(Cell player);
      bool isFull();
      std::vector<std::string> getBoard() const;

private:
      std::vector<std::vector<Cell>> board;
      bool checkDirection(int row, int col, int dRow, int dCol, Cell player);
};

#endif