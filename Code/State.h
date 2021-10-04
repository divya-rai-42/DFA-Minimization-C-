#ifndef STATE_MIN
#define STATE_MIN
using namespace std;

    class State
    {
     public:
     int state_no; //State number of the paricular state
     int group_no; //Group(partition) to which the state belongs
     int* transitedState; //This pointer will point to an array which stores the state_no of the states reached on each input symbol
     char status; //Final or non-final state
     void set(int); //function to set details of a state
    };

#endif