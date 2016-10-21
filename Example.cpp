//
//  Example.cpp
//
//  Created by Cao, Jian Hua on 10/20/16.
//

#include "WorkQueue.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string>
#include <pthread.h>


class WorkItem
{
    string m_message;
    int    m_number;
 
  public:
    WorkItem(const char* message, int number) 
          : m_message(message), m_number(number) {}
    ~WorkItem() {}
 
    const char* getMessage() { return m_message.c_str(); }
    int getNumber() { return m_number; }
};


WorkQueue<WorkItem *> *queue;

void * threadFunc(void *arg) {
    while(1) {
        WorkItem *item = queue->pop();
        printf("Get item %s : %d \n", item->getMessage(), item->getNumber());
    }
}


int main(int argc, char** argv)
{
    // Create the queue and consumer (worker) threads
    queue = new WorkQueue<WorkItem *>();
    
    pthread_t tid;
    pthread_create(&tid, NULL, threadFunc, NULL);

    sleep(1);

    WorkItem* item = NULL;
    
    item = new WorkItem("abc", 123);
    queue->push(item);

    sleep(1);

    item = new WorkItem("def", 456);
    queue->push(item);
 
    sleep(5);
}