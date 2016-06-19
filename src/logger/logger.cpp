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

void Logger::resetInstance() {
  delete pInstance;
  pInstance = NULL;
}

Logger::Logger(){
  arch.open(LOG);
}

void Logger::cerrar(){
  arch.close();
}

void Logger::log(int tipoLog, string str, int numError){
  time_t rawtime;
  tm * timeinfo;
  char buffer [80];
  time(&rawtime);
  timeinfo = localtime(&rawtime);
  strftime(buffer, 80, "[%Y/%m/%d - %H:%M:%S]:", timeinfo);
  pthread_mutex_lock(&mutexLog);
  if(tipoLog == LOG_INFO){
    arch << "[INFO]: " << buffer << " " << str << endl;
  }else if(tipoLog == LOG_ERROR){
    arch << "[ERROR]: " << buffer << str << " " << "Error:" << numError << endl;
  }else if(tipoLog == LOG_WARN){
    arch << "[WARNING]:" << buffer << str << endl;
  }
  pthread_mutex_unlock(&mutexLog);

}

void Logger::logInfo(string str){
  log(LOG_INFO, str, 0);
}

void Logger::logError(int numError, string str){
  log(LOG_ERROR, str, numError);
}

void Logger::logWarning(string str){
  log(LOG_WARN, str, 0);
}
