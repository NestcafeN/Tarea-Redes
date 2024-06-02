#include "common.hpp"
#include <sstream>
#include <iomanip>

// Constructor: Inicializa el tablero con celdas vacías
Game::Game() : board(ROWS, std::vector<Cell>(COLS, EMPTY)) {}

// Método para realizar un movimiento en una columna para un jugador específico
bool Game::makeMove(int col, Cell player)
{
      if (col < 0 || col >= COLS || board[0][col] != EMPTY)
      {
            return false; // Movimiento inválido
      }
      for (int row = ROWS - 1; row >= 0; --row)
      {
            if (board[row][col] == EMPTY)
            {
                  board[row][col] = player; // Realiza el movimiento en la celda vacía más baja de la columna
                  return true;
            }
      }
      return false;
}

// Método para verificar si un jugador ha ganado
bool Game::checkWin(Cell player)
{
      for (int row = 0; row < ROWS; ++row)
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
      }
      return false;
}

// Método para verificar si el tablero está lleno (empate)
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

// Método para obtener el estado actual del tablero como un vector de cadenas
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

// Método auxiliar para verificar si hay 4 en línea en una dirección específica
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