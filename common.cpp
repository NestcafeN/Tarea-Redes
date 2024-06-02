#include "common.hpp"
#include <sstream>
#include <iomanip>

Game::Game() : board(ROWS, std::vector<Cell>(COLS, EMPTY)) {}

bool Game::makeMove(int col, Cell player)
{
      if (col < 0 || col >= COLS || board[0][col] != EMPTY)
      {
            return false;
      }
      for (int row = ROWS - 1; row >= 0; --row)
      {
            if (board[row][col] == EMPTY)
            {
                  board[row][col] = player;
                  return true;
            }
      }
      return false;
}

bool Game::checkWin(Cell player) for (int row = 0; row < ROWS; ++row)
{
      for (int col = 0; col < COLS; ++col)
      {
            if (board[row][col] == player &&
                (checkDirection(row, col, 1, 0, player) ||
                 checkDirection(row, col, 0, 1, player) ||
                 checkDirection(row, col, 1, 1, player) ||
                 checkDirection(row, col, 1, -1, player)))
            {
                  return true;
            }
      }
      return false;
}

bool Game::isFull()
{
      for (int col = 0; col < COLS; ++col)
      {
            if (board[0][col] == EMPTY)
            {
                  return false;
            }
      }
      return true;
}

std::vector<std::string> Game::getBoard() const
{
      std::vector<std::string> boardStr(ROWS, std::string(COLS, ' '));
      for (int row = 0; row < ROWS; ++row)
      {
            for (int col = 0; col < COLS; ++col)
            {
                  if (board[row][col] == PLAYER1)
                  {
                        boardStr[row][col] = 'C';
                  }
                  else if (board[row][col] == PLAYER2)
                  {
                        boardStr[row][col] = 'S';
                  }
            }
      }
      return boardStr;
}

bool Game::checkDirection(int row, int col, int dRow, int dCol, Cell player)
{
      int count = 0;
      for (int i = 0; i < 4; ++i)
      {
            int r = row + i * dRow;
            int c = col + i * dCol;
            if (r < 0 || r >= ROWS || c < 0 || c >= COLS || board[r][c] != player)
            {
                  return false;
            }
            count++;
      }
      return count == 4;
}