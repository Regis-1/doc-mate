#include "server.h"
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sstream>
#include <thread>
#include <unistd.h>
#include <iostream>
#include <errno.h>

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

Server::Server(std::string ip, int port, int nConn)
  : serverIp_(ip), serverPort_(port), nListenConn_(nConn)
{}

Server::~Server() {
  close(socket_);
}

void Server::bindSocket() {
  socket_ = socket(AF_INET, SOCK_STREAM, 0);
  if (socket_ < 0) {
    std::cerr << "ERROR: Could not create server socket.\n";
  }
  int optval = 1;
  setsockopt(socket_, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval));

  struct sockaddr_in serverAddr;
  serverAddr.sin_family = AF_INET;
  serverAddr.sin_addr.s_addr = inet_addr(serverIp_.c_str());
  serverAddr.sin_port = htons(serverPort_);

  int rc = bind(socket_, (struct sockaddr*)&serverAddr , sizeof(serverAddr));
  if (rc < 0) {
    std::cerr << "ERROR: Could not bind the socket. Error code: " << rc << "\n";
  }
}

void Server::listenOnSocket() {
  int rc = listen(socket_, nListenConn_);
  if (rc < 0) {
    std::cerr << "ERROR: Error while starting listening on binded socket."
	      << " Error code: " << rc << "\n";
  }

  int clientSocket;
  while(true) {
    std::cout << "\nHi, I'm running server. Some client hit me..\n";
    clientSocket = accept(socket_, (struct sockaddr*)NULL, NULL);
    if (clientSocket < 0) {
      std::cerr << "ERROR: Error while accept(). Error: "
	     << errno << "\n";
      return;
    }
    std::thread(handleClient, clientSocket).detach();
  }
}
