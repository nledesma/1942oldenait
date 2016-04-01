#ifndef LOGGER_H
#define LOGGER_H
#define LOG "log.log"

#include <pthread.h>
#include <ctime>
#include <fstream>
#include <string>

using namespace std;

class Logger {
private:
  static Logger* pInstance;
  Logger(); // Constructor privado.
  // Constructor por copia. Esto es para que una eventual clase hija no pueda definirlo.
  Logger(Logger const&);
  // Redefinimos esto para no poder obtener la instancia y hacer "=".
  Logger& operator=(Logger const&);
  ofstream arch;
  static pthread_mutex_t mutexCrear;
  pthread_mutex_t mutexLog = PTHREAD_MUTEX_INITIALIZER;
public:
  static Logger * instance();
  void log(string mensaje);
  void cerrar();
};

#endif
