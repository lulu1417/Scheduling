#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<numeric>
#define MAX 100000
using namespace std;
struct Process{
string pid;
int priority;
int burst;
int arrive;
bool executed;
};
int start=0, turnaround, waiting,executed = 0;
vector<int> wait; vector<int> turn; vector<int> ready;
void execute(Process proc){
    int finish;
    if(start - proc.arrive < 0 || start == 0){
        waiting = 0;
        finish = proc.arrive + proc.burst;
    }
    else{
        waiting = start - proc.arrive;
        finish = start + proc.burst;
    }
    wait.push_back(waiting);
    if(start + proc.burst - proc.arrive <=0 )
        turnaround = proc.burst;
    else
        turnaround = start + proc.burst - proc.arrive;
    turn.push_back(turnaround);
        cout<<proc.pid<<"\t"<<proc.priority<<"\t"<<proc.burst<<"\t"<<proc.arrive<<"\t"<<start<<"\t"<<finish<<"\t"<<waiting<<"\t  "<<turnaround<<"\t  "<<
    executed+1<<endl;
}
void SJF(Process proc[], int n){
    int minimum;
    while(executed<n){
        int j = executed;
        if(proc[j].arrive > start){
            execute(proc[j]);
            proc[j].executed = 1;
            start = proc[j].arrive + proc[j].burst;
        }
        else{
            minimum = MAX;
            while(proc[j].arrive <= start && j<n){ //check all the processes in the ready queue and find the shortest one
                    cout<<"j = "<<j<<endl;
                if(proc[j].burst<minimum && !proc[j].executed){
                    swap(proc[j], proc[0]);
                    minimum = proc[0].burst;
                }
                j++;
            }
            //execute the shortest one
            if(!proc[0].executed){ //this line is to prevent duplicate execution when no processes being swapped
                execute(proc[0]);
                proc[0].executed = 1;
                start = start + proc[0].burst;
            }
        }
        executed++;
    }
}
void calculate_wait_and_turnaround(){
    double average_wait, average_turn;
    double sum_wait = accumulate(wait.begin(),wait.end(),0);
	average_wait = sum_wait/wait.size();
	double sum_turn = accumulate(turn.begin(),turn.end(),0);
	average_turn = sum_turn/turn.size();
    int max_waiting = wait.back();
	cout<<"Max waiting time: "<<max_waiting<<endl;
	cout<<"average waiting time: "<<average_wait<<endl;
    cout<<"average turnaround time: "<<average_turn<<endl;
}
int main(){
    fstream file;
    string processid; int priority, burst, arrive;
    Process proc[10000]; int n = 0;
    file.open("test.txt",ios::in);
	if(!file){
		cout<<"Error! Can not open the file"<<endl;
	}
	else{
        cout << "ID  "<<" Priority"<< "  Burst"<<"  Arrive "<<"  Start"<<"  Finish"<< "  Waiting" << "  Turnaround"<< " Completed" <<endl;
        while(file>>processid>>priority>>burst>>arrive){
            proc[n] = {processid, priority, burst, arrive, 0};
            n++;
        }
	}
	SJF(proc, n);
    calculate_wait_and_turnaround();
	return 0;
}

