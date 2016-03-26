#include <iostream>

using namespace std;

int main(){
  MENU:
  int opcion;
  cout << "Bienvenido, Elija la opcion que desee:" << endl;
  cout << "1. Conectar" << endl;
  cout << "2. Desconectar" << endl;
  cout << "3. Salir" << endl;
  cout << "4. Enviar mensaje <id>" << endl;
  cout << "5. Ciclar " << endl;
  cin >> opcion;
  switch (opcion) {
    case 1:
      //Aca se debe establecer la conexion con el servidor.
      break;
    case 2:
      //Se cierra la conexion con el servidorParser
      break;
    case 3:
    //Se sale del programa
      break;
    case 4:
    //Por cada uno de los mensajes que hay en el archivo de configuracion, es decir deberia
    //existir un for que envie cada mensaje ...
      break;
    case 5:
      int tiempo;
      //Envia mensajes en forma iterativa durante una cantiadad determinada de milisegundos.
      cout << "Ingrese el tiempo (ms): " << endl;
      cin >> tiempo;
      break;
    default: cout<< "Opcion invalida. Pulse ENTER para continuar y volver a elegir" << endl;
    goto MENU;
  }


  return 0;

}
