#ifndef COMMON_HPP
#define COMMON_HPP

#include <vector>
#include <string>

// Definición del tamaño del tablero
#define ROWS 6
#define COLS 7

// Enumeración para representar las celdas del tabler
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
      // Métodos para realizar movimientos, verificar victorias y comprobar si el tablero está lleno
      bool makeMove(int col, Cell player);
      bool checkWin(Cell player);
      bool isFull();
      // Método para obtener el estado actual del tablero como un vector de cadenas
      std::vector<std::string> getBoard() const;

private:
      std::vector<std::vector<Cell>> board; // Matriz que representa el tablero
      // Método auxiliar para verificar si hay 4 en línea en una dirección específica
      bool checkDirection(int row, int col, int dRow, int dCol, Cell player);
};

#endif