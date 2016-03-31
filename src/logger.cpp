#include "logger.hpp"
#include <cstdio>
#include <ctime>

// Declaramos la única instancia.
Logger* Logger::pInstance = NULL;

Logger* Logger::instance(){
  if(pInstance == NULL){
    pInstance = new Logger();
  }
  return pInstance;
}

Logger::Logger(){
  arch.open(LOG);
}

void Logger::cerrar(){
  arch.close();
}

void Logger::log(string str){
  //TODO AGREGAR MUTEX
  time_t rawtime;
  tm * timeinfo;
  char buffer [80];
  time(&rawtime);
  timeinfo = localtime(&rawtime);

  strftime(buffer, 80, "[%Y/%m/%d - %H:%M:%S]:", timeinfo);
  arch << buffer << " " << str << endl;
}
