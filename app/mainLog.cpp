#include "../src/logger/logger.hpp"
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <pthread.h>
#include <sstream>

using namespace std;

void* f(void* arg){
  long int nro = (long int) arg;
  stringstream ss;
  ss << "Esto es un mensaje del thread " << nro;
  Logger::instance()->logInfo(ss.str());
}

int main() {
  pthread_t ids[30];

  for (long int i = 0; i < 30; i++){
    pthread_create(&ids[i], NULL, f, (void*)i);
  }

  Logger * logger = Logger::instance();
  logger->logInfo("Esto es el main.");

  for (int i = 0; i < 30; i++){
    pthread_join(ids[i], NULL);
  }

  logger->logError(111,"Se ha producido un horrible error");
  logger->cerrar();
  return 0;
}
