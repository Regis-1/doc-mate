#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string>
#include <iostream>
#include <thread>

const int SERVER_PORT = 8089;
const int NUM_OF_CONNECTIONS = 5;
const std::string INTERFACE_IP = "127.0.0.1";

void handleClient(int clientSocket) {
  std::string response =
    "HTTP/1.1 200 OK\r\n"
    "Content-Type: text/html\r\n"
    "Content-Length: 13\r\n"
    "\r\n"
    "Hello, world!";

  write(clientSocket, response.c_str(), response.size());

  close(clientSocket);
}

int main()
{
  int serverSocket = 0;
  int clientSocket = 0;
  serverSocket = socket(AF_INET, SOCK_STREAM, 0);

  struct sockaddr_in serverAddr;
  serverAddr.sin_family = AF_INET;
  serverAddr.sin_addr.s_addr = inet_addr(INTERFACE_IP.c_str());
  serverAddr.sin_port = htons(SERVER_PORT);

  bind(serverSocket, (struct sockaddr*)&serverAddr , sizeof(serverAddr));
  listen(serverSocket, NUM_OF_CONNECTIONS);

  while(true) {
    std::cout << "\n\nHi, I'm running server. Some client hit me..\n";
    clientSocket = accept(serverSocket, (struct sockaddr*)NULL, NULL);
    std::thread(handleClient, clientSocket).detach();
  }

  close(serverSocket);
  return 0;
}
