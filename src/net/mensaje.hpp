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
		string strTipo();

};
#endif // MENSAJE_H