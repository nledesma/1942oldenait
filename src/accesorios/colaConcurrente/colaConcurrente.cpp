#include "colaConcurrente.hpp"

template <class T>
T ColaConcurrente<T>::pop(){
    // Espero a que la cola tenga elementos.
    pthread_mutex_lock(&mutexDesencolar);
    while (cola.empty()) {
        pthread_cond_wait(&condDesencolar, &mutexDesencolar);
    }
    pthread_mutex_unlock(&mutexDesencolar);

    // Hago efectivamente el pop.
    pthread_mutex_lock(&mutexCola);
    T el = cola.front();
    cola.pop();
    pthread_mutex_unlock(&mutexCola);

    return el;
}

template <class T>
void ColaConcurrente<T>::push(T el){
    pthread_mutex_lock(&mutexDesencolar);
    pthread_mutex_lock(&mutexCola);
    // Agrego el elemento.
    cola.push(el);
    // Mando una señal para que se pueda desencolar.
    pthread_cond_signal(&condDesencolar);

    pthread_mutex_unlock(&mutexCola);
    pthread_mutex_unlock(&mutexDesencolar);
}

template <class T>
bool ColaConcurrente<T>::vacia(){
    return cola.empty();
}

template<class T>
void ColaConcurrente<T>::avisar(){
    // Encolamos algo ficticio para que pueda destrabarse desencolando (!).
    // Por ahí hay un mejor método.
    T t;
    push(t);
}


template <class T>
ColaConcurrente<T>::ColaConcurrente(){}
template <class T>
ColaConcurrente<T>::~ColaConcurrente<T>(){}

/* Explicito cuáles tipos pueden instanciarse */
template class ColaConcurrente<std::pair<int, Mensaje*> >;
template class ColaConcurrente<Mensaje*>;
