//
//  WorkQueue.h
//
//  Created by Cao, Jian Hua on 10/20/16.
//

#ifndef WorkQueue_H
#define WorkQueue_H

#include <stdio.h>
#include <pthread.h>
#include <list>

using namespace std;

template <typename T> class WorkQueue {
  list<T>   m_queue;
  pthread_mutex_t m_mutex;
  pthread_cond_t  m_condv;

public:

  WorkQueue() {
    pthread_mutex_init(&m_mutex, NULL);
    pthread_cond_init(&m_condv, NULL);
  }

  ~WorkQueue() {
    pthread_mutex_destroy(&m_mutex);
    pthread_cond_destroy(&m_condv);
  }

  void push(T item) {
    pthread_mutex_lock(&m_mutex);
    m_queue.push_back(item);
    pthread_cond_signal(&m_condv);
    pthread_mutex_unlock(&m_mutex);
  }

  T pop() {
    pthread_mutex_lock(&m_mutex);
    while (m_queue.size() == 0) {
      pthread_cond_wait(&m_condv, &m_mutex);
    }

    T item = m_queue.front();
    m_queue.pop_front();
    pthread_mutex_unlock(&m_mutex);
    return item;
  }

  int size() {
    pthread_mutex_lock(&m_mutex);
    int size = m_queue.size();
    pthread_mutex_unlock(&m_mutex);
    return size;
  }

};

#endif /* WorkQueue_H */
