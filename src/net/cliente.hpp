#include "gameSocket.cpp"
using namespace std;

class Cliente: public GameSocket{
private:
    string ip;
    int port;
    list <Mensaje*> listaMensajes;

public:
	Cliente(string ip, int port):GameSocket();


  void inicializar(string serverAddress ,int port);
  void agregarMensaje(Mensaje* pMensaje);
  void setAddress(string serverAddress, int port);
  int conectar();
  string recibir(int longitudMensaje);
  string getIP();
  int getPort();
  list <Mensaje*>& getMensajes();

};
