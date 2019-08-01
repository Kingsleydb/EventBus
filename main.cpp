//Author: Kingsley Bowen

#include <iostream>
#include "EventQueue.h"
using namespace std; 

void cancelEvents(string name, EventQueuePtr queue);
void executeMe(string arg, EventQueuePtr queue, string name);
void dontExecuteMe(string arg, EventQueuePtr queue, string name);

int main()
{
    EventQueue queueInstance;
    FunctPtr eM = executeMe;
    FunctPtr dEM = dontExecuteMe;

    // tests ability to add events with different keys, different callbacks
    queueInstance.add("blue", dEM);
    queueInstance.add("red", eM);
    queueInstance.add("red", eM);
    queueInstance.add("red", eM);

    assert(queueInstance.size() == 4);

    // tests ability for many keys, one callback
    queueInstance.add("black", eM);
    queueInstance.invoke("black", "black just executed");
    assert(queueInstance.size() == 4);

    // tests cancelling functionality 
    queueInstance.invoke("red", "red just executed");
    assert(queueInstance.size() == 1);

    // tests for input not in queue
    queueInstance.invoke("purple", "this should not execute");
    assert(queueInstance.size() == 1);

    return 0; 
}

// Callback function to store in event
void executeMe(string arg, EventQueuePtr address, string name)
{
    cout << "ExecuteMe: " << arg << endl;
    cancelEvents(name, address);
}

// Callback function to store in event
void dontExecuteMe(string arg, EventQueuePtr address, string name)
{
    cout << "dontExecuteMe: " << arg << endl;
    (void) address;
    (void) name;
}

// Purpose: Cancels all of the events in an EventQueue with a given name
// Input: Name of event to be deleted, pointer to EventQueue to delete from
// Return: n/a
void cancelEvents(string name, EventQueuePtr queue)
{   
    int queueSize = queue->size();
    Event eventList[queueSize];

    // copy queue to temporary array
    for (int i = 0; i < queueSize; i++){
        eventList[i] = (*queue)[i];
    }
    // cancel all events with a given key in temporary array
    for (int j = 0; j < queueSize; j++){
        if (eventList[j].key == name){
            Event dummyEvent = {"", nullptr};
            eventList[j] = dummyEvent;
        } 
    }
    queue->clear();
    // refill queue with remaining events
    for (int k = 0; k < queueSize; k++){
        if (eventList[k].key != ""){
            queue->push_back(eventList[k]);
        }
    }
}
