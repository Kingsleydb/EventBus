#include <iostream>
#include <vector>
#include "EventQueue.h"
using namespace std;

EventQueue::EventQueue()
{
    vector<Event> queue;
}

// Purpose: adds an event to the event queue
// Input: string to identify event and a function pointer
// Return Value: N/a
void EventQueue::add(string name, FunctPtr callback)
{
    Event queueEntry = {name, callback};
    queue.push_back(queueEntry);
}

// Purpose: identifies first event in Event queue with specified key and calls 
// associated callback function with arg as its parameter. It also removes all 
// events with the same key from the queue.
// Input: String to identify event, string arg as parameter to callback
// Return Value: N/a
void EventQueue::invoke(string name, string arg)
{
    int queueSize = queue.size();
    for (int i = 0; i < queueSize; i++){
        if (!queue.empty()){
            Event event = queue[i];
            // find event in queue
            if (name == event.key){
                event.callback(arg, &queue, name);
                return;
            }
        }
    }
}

int EventQueue::size()
{
    return queue.size();
}