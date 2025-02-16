#include <string>

class Server {
public:
  Server() = delete;
  Server(std::string ip, int port, int nConn);
  ~Server();

  void bindSocket();
  void listenOnSocket();
  
private:
  const std::string serverIp_;
  const int serverPort_;
  const int nListenConn_;

  int socket_;
};
