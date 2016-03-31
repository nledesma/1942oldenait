#include "src/logger.hpp"
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
  Logger::instance()->log(ss.str());
}

int main() {
  pthread_t ids[30];

  for (long int i = 0; i < 30; i++){
    pthread_create(&ids[i], NULL, f, (void*)i);
  }

  Logger * logger = Logger::instance();
  logger->log("Esto es el main.");

  for (int i = 0; i < 30; i++){
    pthread_join(ids[i], NULL);
  }

  logger->cerrar();
  return 0;
}
