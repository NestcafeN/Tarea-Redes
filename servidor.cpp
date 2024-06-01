#include <iostream>
#include <thread>
#include <vector>
#include <string>
#include <sstream>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include "common.hpp"

void handleClient(int clientSocket);

int main(int argc, char *argv[])
{
      if (argc != 2)
      {
            std::cerr << "Usage: " << argv[0] << " <port>" << std::endl;
            return 1;
      }

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

      if (bind(serverSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0)
      {
            std::cerr << "Bind failed" << std::endl;
            close(serverSocket);
            return 1;
      }

      listen(serverSocket, 3);
      std::cout << "Esperando conexiones ..." << std::endl;

      while (true)
      {
            int clientSocket = accept(serverSocket, nullptr, nullptr);
            if (clientSocket >= 0)
            {
                  std::thread clientThread(handleClient, clientSocket);
                  clientThread.detach();
            }
      }

      close(serverSocket);
      return 0;
}

void handleClient(int clientSocket)
{
      Game game;
      bool gameRunning = true;
      Cell currentPlayer = (rand() % 2 == 0) ? PLAYER1 : PLAYER2;
      char buffer[1024];

      std::string startMsg = (currentPlayer == PLAYER1) ? "Cliente comienza\n" : "Servidor comienza\n";
      send(clientSocket, startMsg.c_str(), startMsg.size(), 0);

      while (gameRunning)
      {
            std::vector<std::string> board = game.getBoard();
            std::ostringstream boardStream;
            boardStream << "TABLERO\n";
            for (const auto &line : board)
            {
                  boardStream << line << "\n";
            }
            boardStream << "---\n";
            std::string boardStr = boardStream.str();
            send(clientSocket, boardStr.c_str(), boardStr.size(), 0);

            if (currentPlayer == PLAYER1)
            {
                  recv(clientSocket, buffer, sizeof(buffer), 0);
                  int col = std::stoi(buffer);
                  game.makeMove(col, PLAYER1);
                  if (game.checkWin(PLAYER1))
                  {
                        std::string winMsg = "Gana el Cliente\n";
                        send(clientSocket, winMsg.c_str(), winMsg.size(), 0);
                        gameRunning = false;
                  }
            }
            else
            {
                  int col = rand() % COLS;
                  while (!game.makeMove(col, PLAYER2))
                  {
                        col = rand() % COLS;
                  }
                  std::string moveMsg = "Servidor juega columna " + std::to_string(col) + "\n";
                  send(clientSocket, moveMsg.c_str(), moveMsg.size(), 0);
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

            currentPlayer = (currentPlayer == PLAYER1) ? PLAYER2 : PLAYER1;
      }

      close(clientSocket);
}