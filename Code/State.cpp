#include"State.h"
#include<iostream>
using namespace std;

    void State::set(int n_inputs)
    {
        //The size of the array will be equal to number of input symbols
        transitedState = new int[n_inputs];
        cout<<"State: q";
        cin>>state_no;
        cout<<"\nFinal or non-final state(f/n): ";
        cin>>status;

//Initially ,at 0th equivalence there are two partition, one of non-final states and other of final states
        if(status=='n' || status=='N')
        group_no=0; 
        else if(status=='f' || status=='F')
        group_no=1;

        cout<<"\nEnter the transition states for the following inputs: \n";
        for(int i=0;i<n_inputs;i++)
        {
            cout<<"Input "<<i<<": q";
            cin>>transitedState[i];
            cout<<"\n";
        }

    }


//Command to compile the code : g++ Minimization.cpp State.cpp