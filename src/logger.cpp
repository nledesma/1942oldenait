#include "logger.hpp"

pthread_mutex_t Logger::mutexCrear = PTHREAD_MUTEX_INITIALIZER;
// Declaramos la única instancia.
Logger* Logger::pInstance = NULL;

Logger* Logger::instance(){
  pthread_mutex_lock(&mutexCrear);
  if(pInstance == NULL){
    pInstance = new Logger();
  }
  pthread_mutex_unlock(&mutexCrear);
  return pInstance;
}

Logger::Logger(){
  arch.open(LOG);
}

void Logger::cerrar(){
  arch.close();
}

void Logger::log(string str){
  time_t rawtime;
  tm * timeinfo;
  char buffer [80];
  time(&rawtime);
  timeinfo = localtime(&rawtime);
  strftime(buffer, 80, "[%Y/%m/%d - %H:%M:%S]:", timeinfo);

  pthread_mutex_lock(&mutexLog);
  arch << buffer << " " << str << endl;
  pthread_mutex_unlock(&mutexLog);
}
