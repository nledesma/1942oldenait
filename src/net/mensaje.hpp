#ifndef MENSAJE_H
#define MENSAJE_H
#include <string>

using namespace std;
class Mensaje{
	private:
		int id;
		int tipo;
		void * valor;
	public:

// Ver si lo decodifica el parser...
		Mensaje(int unId, string unValor, int unTipo);
		~Mensaje();
		void setId(int unId);
		int getId();
		void setValor(void* unValor);
		void* getValor();
		int getTipo();
		void setTipo(int unTipo);
		string strTipo();

};
#endif // MENSAJE_H
