#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<numeric>
#define MAX 1000000
using namespace std;
struct Process{
string pid;
int priority;
int burst;
int remainder;
int arrive;
bool finished;
};
int start=0, turnaround, waiting, finish=0, max_waiting=0, cs=0;
int i = 0;  string pre_proc = "";
vector<int> wait; vector<int> turn;
void Proc_finish(Process proc){
    finish++;
    if(start - proc.burst - proc.arrive < 0){
        waiting = 0;
    }
    else{
        waiting = start - proc.burst - proc.arrive;
    }
    wait.push_back(waiting);
    if(waiting > max_waiting)
        max_waiting = waiting;
    turnaround = start - proc.arrive;
    turn.push_back(turnaround);
        cout<<proc.pid<<"\t"<<proc.priority<<"\t"<<proc.burst<<"\t"<<proc.arrive<<"\t"<<start<<"\t"<<waiting<<"\t  "<<turnaround<<endl;
}
void execute(Process proc){
    int times=0;
    start++;
    //cout<<proc.pid<<"\t"<<proc.priority<<"\t"<<proc.burst<<"\t"<<proc.arrive<<"\t"<<start<<"\t"<<waiting<<"\t  "<<turnaround<<endl;
    if(proc.remainder==0){
        Proc_finish(proc);
    }
}
void SRTF(Process proc[], int n){
    int minimum, m, pre=0;
    while(finish<n){
            int found = 0;
            minimum = MAX;
            for(i=0;proc[i].arrive <= start && i<n;i++){ //find the shortest remainder in ready queue
                if(proc[i].burst < minimum && !proc[i].finished){
                    minimum = proc[i].remainder;
                    m = i;
                    found = 1;
                }

            }
        if(pre!=m) //if there is a context switch
            cs++;
        pre = m;
        if(found == 1){ //this line is to check if ready queue is empty
            execute(proc[m]); proc[m].remainder--;
            if(proc[m].remainder==0){
                Proc_finish(proc[m]);
                proc[m].finished = 1;
            }
        }

        else{   //queue is empty
            start = proc[finish].arrive;
        }
    }
    cout<<"Context switch = "<<cs<<endl;
}
void calculate_wait_and_turnaround(){
    double average_wait, average_turn;
    double sum_wait = accumulate(wait.begin(),wait.end(),0);
	average_wait = sum_wait/wait.size();
	double sum_turn = accumulate(turn.begin(),turn.end(),0);
	average_turn = sum_turn/turn.size();
    cout<<"average turnaround time: "<<average_turn<<endl;
	cout<<"Max waiting time: "<<max_waiting<<endl;
	cout<<"average waiting time: "<<average_wait<<endl;
}
int main(){
    fstream file;
    string processid; int priority, burst, arrive;
    Process proc[10000]; int n = 0;
    file.open("data_2.txt",ios::in);
	if(!file){
		cout<<"Error! Can not open the file"<<endl;
	}
	else{
        cout << "ID  "<<" Priority"<< "  Burst"<<"  Arrive "<<"  Finish"<< "  Waiting" << "  Turnaround"<<endl;
        while(file>>processid>>priority>>burst>>arrive){
            proc[n] = {processid, priority, burst, burst, arrive, 0};
            n++;
        }
	}
	SRTF(proc, n);
    calculate_wait_and_turnaround();

	return 0;
}

