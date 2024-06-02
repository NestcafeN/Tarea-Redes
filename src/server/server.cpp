#include <iostream>
#include <thread>
#include <vector>
#include <string>
#include <sstream>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include "common.hpp"

// Funci贸n para manejar las conexiones de los clientes
void handleClient(int clientSocket, std::string clientID);

int main(int argc, char *argv[])
{ // Verifica que los argumentos sean correctos
      if (argc != 2)
      {
            std::cerr << "Usage: " << argv[0] << " <port>" << std::endl;
            return 1;
      }

      // Crea el socket del servidor
      int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
      if (serverSocket == -1)
      {
            std::cerr << "Could not create socket" << std::endl;
            return 1;
      }

      int port = std::stoi(argv[1]);
      sockaddr_in serverAddr;
      serverAddr.sin_family = AF_INET;
      serverAddr.sin_addr.s_addr = INADDR_ANY;
      serverAddr.sin_port = htons(port);

      // Asigna la direcci贸n al socket del servidor
      if (bind(serverSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0)
      {
            std::cerr << "Bind failed" << std::endl;
            close(serverSocket);
            return 1;
      }
      // Pone el servidor a la escucha de conexiones entrantes
      listen(serverSocket, 10);
      std::cout << "Esperando conexiones ..." << std::endl;

      while (true)
      {
            sockaddr_in clientAddr;
            socklen_t clientAddrLen = sizeof(clientAddr);
            int clientSocket = accept(serverSocket, (struct sockaddr *)&clientAddr, &clientAddrLen);
            if (clientSocket >= 0)
            {
                  // Genera un ID para el cliente basado en su IP y puerto
                  std::string clientID = std::string(inet_ntoa(clientAddr.sin_addr)) + ":" + std::to_string(ntohs(clientAddr.sin_port));
                  std::cout << "Juego nuevo[" << clientID << "]" << std::endl;
                  std::thread clientThread(handleClient, clientSocket, clientID);
                  clientThread.detach();
            }
      }

      close(serverSocket);
      return 0;
}

// Funci贸n para manejar la comunicaci贸n con el cliente
void handleClient(int clientSocket, std::string clientID)
{
      Game game;
      bool gameRunning = true;
      Cell currentPlayer = (rand() % 2 == 0) ? PLAYER1 : PLAYER2;
      char buffer[1024];

      std::string startMsg = (currentPlayer == PLAYER1) ? "inicia juego el cliente" : "inicia juego el servidor";
      std::cout << "Juego [" << clientID << "]: " << startMsg << "." << std::endl;
      std::string clientStartMsg = (currentPlayer == PLAYER1) ? "Tu turno\n" : "";
      send(clientSocket, clientStartMsg.c_str(), clientStartMsg.size(), 0);

      while (gameRunning) // Enviar el tablero al cliente
      {
            std::vector<std::string> board = game.getBoard();
            std::ostringstream boardStream;
            for (const auto &line : board)
            {
                  boardStream << line << "\n";
            }
            boardStream << "---\n";
            std::string boardStr = boardStream.str();
            send(clientSocket, boardStr.c_str(), boardStr.size(), 0);

            if (currentPlayer == PLAYER1)
            {
                  // Enviar mensaje al cliente indicando que es su turno
                  send(clientSocket, "Tu turno\n", 9, 0);
                  recv(clientSocket, buffer, sizeof(buffer), 0);
                  int col = std::stoi(buffer);
                  game.makeMove(col, PLAYER1);
                  std::cout << "Juego [" << clientID << "]: cliente juega columna " << col + 1 << "." << std::endl;
                  if (game.checkWin(PLAYER1))
                  {
                        std::string winMsg = "Gana el Cliente\n";
                        send(clientSocket, winMsg.c_str(), winMsg.size(), 0);
                        gameRunning = false;
                  }
            }
            else
            {
                  // Genera la jugada del servidor
                  int col = rand() % COLS;
                  while (!game.makeMove(col, PLAYER2))
                  {
                        col = rand() % COLS;
                  }
                  std::cout << "Juego [" << clientID << "]: servidor juega columna " << col + 1 << "." << std::endl;
                  if (game.checkWin(PLAYER2))
                  {
                        std::string winMsg = "Gana el Servidor\n";
                        send(clientSocket, winMsg.c_str(), winMsg.size(), 0);
                        gameRunning = false;
                  }
            }

            if (game.isFull())
            {
                  std::string drawMsg = "Empate\n";
                  send(clientSocket, drawMsg.c_str(), drawMsg.size(), 0);
                  gameRunning = false;
            }
            // Cambiar el turno al siguiente jugador
            currentPlayer = (currentPlayer == PLAYER1) ? PLAYER2 : PLAYER1;
      }
      // Cierra el socket del cliente
      close(clientSocket);
      std::cout << "Juego [" << clientID << "]: fin del juego." << std::endl;
}