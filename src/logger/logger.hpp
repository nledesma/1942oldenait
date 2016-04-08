#ifndef LOGGER_H
#define LOGGER_H
#define LOG "log.log"

#include <pthread.h>
#include <ctime>
#include <fstream>
#include <string>

#define LOG_INFO 1
#define LOG_ERROR 2
#define LOG_WARN 3
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
  void log(int tipoLog, string str, int error);
  void logInfo(string mensaje);
  void logError(int numError, string error);
  void logWarning(string str);
  void cerrar();
};

#endif
