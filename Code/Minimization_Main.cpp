#include"State.h"
#include<bits/stdc++.h>
using namespace std;

int n_states; //n_states denotes total number of states
int tgroups;  //tgroups denotes total number of partitions formed
int n_inputs; //n_inputs denotes total number of input symbols

//Function to minimize the DFA
int Minimize(State s[])
{
    int g_reached[n_states];//This array stores(for each state) the group_no of the sate reached when a particular input is given
    for(int I=0;I<n_states-2;I++) //Max (n_states-2) iterations are required to minimize the DFA
    {
        for(int j=0;j<n_inputs;j++) //j=0 means input symbol is '0' , j=1 means input symbol is '1' and so on
        {
            //Initialising g_reached when input symbol is j
            for(int i=0;i<n_states;i++)
            {
            int temp=s[i].transitedState[j];
            g_reached[i]=s[temp].group_no;
            }

            for(int i=0;i<n_states-1;i++)
            {
                int group_record[n_states];//This will maintain the record of the states that form new partion in this iteration 
                memset(group_record,-1,sizeof(group_record));
                
                for(int k=i+1;k<n_states;k++)
                {
                    if(s[i].group_no==s[k].group_no && g_reached[i]!=g_reached[k])
                    {
                        int f =-1;
                        for(int l=0;l<n_states;l++)//checking whether s[k] can fall in some other already existing partion or it will form a new partition
                        {
                            if(g_reached[k]==group_record[l])
                            {
                                f=l;
                                break;
                            }
                        }

                        if(f==-1)//s[k] forms a new partition
                        {
                            s[k].group_no=tgroups;
                            tgroups++;
                            group_record[k]=g_reached[k];
                        }
                        else//s[k] will fall in some other partition(excluding s[i])
                        {
                            s[k].group_no=s[f].group_no;
                        }
                    }
                }
            }
        }
        
    int equivalence =I;
    for(int i=0;i<n_states;i++)
    {
        if(s[i].group_no!=g_reached[i])
        {
            equivalence=-1;
            break;
        }
    }

    if(equivalence!=-1)
    {
        return equivalence;
    }

    }
}

//Function to represent the states belonging to a particular partition by a single state
void represent(State s[])
{
    for(int i=0;i<n_states-1;i++)
    {
        if(s[i].state_no!=-1)
        {
            for(int j=i+1;j<n_states;j++)
            {
                //If state s[i] and s[j] belong to the same group then s[j] is represented by s[i] 
                if(s[i].group_no ==s[j].group_no)
                {
                    for(int k=0;k<n_states;k++)
                    {
                        for(int l=0;l<n_inputs;l++)
                        {
                            if(s[k].transitedState[l]==s[j].state_no)
                            s[k].transitedState[l]=i;
                        }
                    }

                    s[j].state_no=-1; //Marking the state_no of this state by -1 denotes that this state is represebted by some other state
                    
                    if(s[j].status=='F' || s[j].status=='f')
                    s[i].status='F';
                }
            }
        }

        
    }
}

//get table for minimized DFA
void getOutput(State s[])
{
    cout<<"\n\n\n********************************************************\n";
    cout<<"********************************************************\n";
    cout<<"States |           Input\n";
    cout<<"       |";
    for(int i=0;i<n_inputs;i++)
    {
        cout<<"     "<<i;
    }
    cout<<"\n";
    for(int i=0;i<n_states;i++)
    {
        if(s[i].state_no==-1) //if this state is represented by some other state then no need to include it in the table
        continue;
        cout<<"\n   q"<<s[i].state_no<<" |";
        for(int j=0;j<n_inputs;j++)
        {
            cout<<"     q"<<s[i].transitedState[j];
        }
        if(s[i].state_no==0)   
        cout<<"     Initial state";
        if((s[i].status=='f'  ||   s[i].status=='F')&&(s[i].state_no==0))   
        cout<<" and Final state";
        else if(s[i].status=='f'  ||   s[i].status=='F')
        cout<<"     Final state";
    }
}

//get the minimum equivalnece partition
void GetEquivalencePartition(State s[])
{
    cout<<"******************Minimum Equivalence Partition*****************\n";
    for(int i=0;i<tgroups;i++)
    {
        cout<<"{ ";
        for(int j=0;j<n_states;j++)
        {
            if(s[j].group_no==i)
            cout<<"q"<<s[j].state_no<<" ";
        }
        cout<<"}\n";
    }
}

int main()
{
    cout<<"********************************************************\n";
    cout<<"Enter number of states: ";
    cin>>n_states;
    cout<<"Enter number of input symbols: ";
    cin>>n_inputs;
    State s[n_states];
    for(int i=0;i<n_states;i++)
    {
        s[i].set(n_inputs);
    }
    tgroups=2; //Initially there are two partitions, final and non-final states
    int equivalence=Minimize(s);
    GetEquivalencePartition(s);
    represent(s);
    getOutput(s);

    return 0;
}

//Compilation command: g++ Minimization_Main.cpp State.cpp
