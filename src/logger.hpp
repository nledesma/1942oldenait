#ifndef LOGGER_H
#define LOGGER_H
#define LOG "log.log"

#include <fstream>
#include <string>
using namespace std;

class Logger {
private:
  static Logger* pInstance;
  Logger(); // Constructor privado.
  Logger(Logger const&){}; // TODO: Por qué hay un constructor por copia?
  Logger& operator=(Logger const&){}; // TODO: Por qué hay que reddefinir esto?
  ofstream arch;
public:
  static Logger * instance();
  void log(string mensaje);
  void cerrar();
};

#endif
