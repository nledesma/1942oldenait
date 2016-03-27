#ifndef MENSAJE_H
#define MENSAJE_H
#include <string>

#define T_STRING 0
#define T_INT 1
#define T_DOUBLE 2
#define T_CHAR 3
#define LONG_INFO_MENSAJE 9
// Utilizamos 32 bits para evitar incompatibilidades.
#define INT_SIZE 4
#define DOUBLE_SIZE 8

typedef struct infoMensaje {
	int id;
	int tipo;
	int longitud;
};

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
		/* Genera la siguiente estructura de bytes para codificar un mensaje
		** - 1 byte para el tipo.
		** - 4 bytes para la longitud.
		** - 4 bytes para el id.
		** - longitud bytes para el contenido.
		*/
		virtual const	char * codificar() = 0;
		static infoMensaje decodificarInfo(char * pInfoMensaje);

};
#endif // MENSAJE_H
