#include <iostream>
#include <string>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include "common.hpp"
#include <iomanip>
#include <vector>
#include <sstream>

// Función para imprimir el tablero de juego en la consola
void print_board(const std::vector<std::string> &board)
{
      std::cout << "\nTABLERO\n";
      for (size_t i = 0; i < board.size(); ++i)
      {
            std::cout << (i + 1) << "";
            for (char c : board[i])
            {
                  std::cout << std::setw(2) << c;
            }
            std::cout << std::endl;
      }
      std::cout << "  -------------\n";
      std::cout << "  1 2 3 4 5 6 7\n"; // Columnas numeradas
}

// Función para procesar los datos del tablero recibidos y mostrarlos en la consola
void processBoard(const std::string &data)
{
      std::istringstream stream(data);
      std::string line;
      std::vector<std::string> board;
      while (std::getline(stream, line))
      {
            if (line == "---")
                  break;
            board.push_back(line);
      }
      print_board(board);
}

int main(int argc, char *argv[])
{ // Verifica que los argumentos sean correctos
      if (argc != 3)
      {
            std::cerr << "Usage: " << argv[0] << " <server_ip> <port>" << std::endl;
            return 1;
      }
      // Crea el socket del cliente
      int clientSocket = socket(AF_INET, SOCK_STREAM, 0);
      if (clientSocket == -1)
      {
            std::cerr << "No se pudo crear el socket" << std::endl;
            return 1;
      }

      std::string serverIp = argv[1];
      int port = std::stoi(argv[2]);
      sockaddr_in serverAddr;
      serverAddr.sin_family = AF_INET;
      serverAddr.sin_port = htons(port);

      // Convierte la dirección IP y la asigna a la estructura de direcciones
      if (inet_pton(AF_INET, serverIp.c_str(), &serverAddr.sin_addr) <= 0)
      {
            std::cerr << "Direccion IP erronea" << std::endl;
            close(clientSocket);
            return 1;
      }
      // Conecta al servidor
      if (connect(clientSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0)
      {
            std::cerr << "Conexion al servidor fallida" << std::endl;
            close(clientSocket);
            return 1;
      }

      char buffer[2048];
      // Recibe y muestra el mensaje de inicio
      recv(clientSocket, buffer, sizeof(buffer), 0);
      std::cout << buffer << std::endl;

      while (true)
      {
            // Limpia el buffer y recibe datos del servidor
            memset(buffer, 0, sizeof(buffer));
            recv(clientSocket, buffer, sizeof(buffer), 0);
            std::string receivedData(buffer);
            // Procesa y muestra el tablero si los datos contienen el marcador de fin de tablero
            if (receivedData.find("---") != std::string::npos)
            {
                  processBoard(receivedData);
            }
            else
            {
                  std::cout << receivedData;
            }
            // Si el mensaje recibido indica que alguien ha ganado o que hubo un empate, termina el juego
            if (receivedData.find("Gana") != std::string::npos || receivedData.find("Empate") != std::string::npos)
            {
                  break;
            }
            // Si es el turno del cliente, pide la columna donde quiere jugar
            if (receivedData.find("Tu turno") != std::string::npos)
            {
                  std::cout << "Introduce la columna en la que quieres Jugar:  ";
                  int col;
                  std::cin >> col;
                  col--;
                  std::string colStr = std::to_string(col);
                  send(clientSocket, colStr.c_str(), colStr.size(), 0);
            }
      }
      // Cierra el socket del cliente
      close(clientSocket);
      return 0;
}