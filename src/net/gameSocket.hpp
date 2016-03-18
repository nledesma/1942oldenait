class GameSocket {
protected:
  int socketFd;
  struct sockaddr_in addr_info;

public:
  GameSocket();
};
