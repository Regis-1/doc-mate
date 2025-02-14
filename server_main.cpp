#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string>
#include <iostream>
#include <thread>
#include <sstream>

const int SERVER_PORT = 8089;
const int NUM_OF_CONNECTIONS = 5;
const std::string INTERFACE_IP = "127.0.0.1";

const std::string resHeadersOk = "HTTP/1.1 200 OK\r\n"
  "Content-Type: application/octet-stream\r\n"
  "Access-Control-Allow-Origin: *\r\n";
const std::string resTestBody = R"(../openGl2_0/test13.txt|../openGL3_1/TextureHandler.txt|../README.txt)";

const std::string formatHttpRes(const std::string &body) {
  std::ostringstream oss;
  oss << resHeadersOk << "Content-Length: " << body.size() << "\r\n\r\n" << body;

  return oss.str();
}

void handleClient(int clientSocket) {
  std::string response {formatHttpRes(resTestBody)};
  write(clientSocket, response.c_str(), response.size());

  close(clientSocket);
}

int main()
{
  int serverSocket = socket(AF_INET, SOCK_STREAM, 0);

  struct sockaddr_in serverAddr;
  serverAddr.sin_family = AF_INET;
  serverAddr.sin_addr.s_addr = inet_addr(INTERFACE_IP.c_str());
  serverAddr.sin_port = htons(SERVER_PORT);

  bind(serverSocket, (struct sockaddr*)&serverAddr , sizeof(serverAddr));
  listen(serverSocket, NUM_OF_CONNECTIONS);

  int clientSocket;
  while(true) {
    std::cout << "\nHi, I'm running server. Some client hit me..\n";
    clientSocket = accept(serverSocket, (struct sockaddr*)NULL, NULL);
    std::thread(handleClient, clientSocket).detach();
  }

  close(serverSocket);
  return 0;
}
