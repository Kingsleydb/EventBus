#include <iostream>
#include <vector>
using namespace std;

struct Event; // forward declarations to break circularity
typedef vector<Event>* EventQueuePtr;
typedef void(*FunctPtr)(string, EventQueuePtr, string name);

typedef struct Event 
{
    string key;
    FunctPtr callback;
} Event;

// Event Queue interface
class EventQueue
{
    public: 
        EventQueue();
        void add(string name, FunctPtr callback);
        void invoke(string name, string arg);
        int size();
    private:
        vector<Event> queue;
};
