#ifndef MENSAJE_H
#define MENSAJE_H
#include <string>

#define T_STRING 0
#define T_INT 1
#define T_DOUBLE 2
#define T_CHAR 3

using namespace std;
class Mensaje{
	protected:
		int id;
		int tipo;
		char * intToBytes(int n);
		void pushearInt(string &str, int n);
		void pushearDouble(string &str, int n);

	public:

// Ver si lo decodifica el parser...
		Mensaje();
		~Mensaje();
		void setId(int unId);
		int getId();
		void setValor(void* unValor);
		void* getValor();
		int getTipo();
		void setTipo(int unTipo);
		virtual string strTipo() = 0;
		virtual string strValor() = 0;
		virtual const	char * codificar() = 0;

};
#endif // MENSAJE_H
