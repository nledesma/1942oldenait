#include "thread.hpp"

Thread::Thread(){}

Thread::~Thread(){}

bool Thread::iniciar(){
  cout << "ESTOY INICIANDO" << endl;
  return (pthread_create(&id, NULL, helper, this) == 0);
}

void* Thread::esperar(){
  cout << "ESTOY ESPERANDO" << endl;
  pthread_join(id, NULL);
  return NULL;
}

  void Thread::ejecutar() {

  }
void* Thread::helper(void* This){
  cout << "Esto es un helper" << endl;
  cout << This << endl;
  ((Thread*)This)->ejecutar();
  cout << "Se mandó la orden de ejecutar" << endl;
  return NULL;
}
