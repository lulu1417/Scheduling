#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<numeric>

using namespace std;
int find_start(int arrive, int pre_start, int pre_burst)
{
	if(pre_start+pre_burst>arrive)
		return pre_start+pre_burst;
	else
		return arrive;

}

int find_waiting(int arrive, int pre_start, int pre_burst)
{
	if(pre_start+pre_burst>arrive)
		return pre_start+pre_burst-arrive;
	else
		return 0;

}

int main()
{
	fstream file;
	//vector<int> priority;
	//vector<int> burst;
	//vector<int> arrive;
	vector<int> wait;
	vector<int> turn;


	string processid;
	int priority;
	int burst;
	int arrive;
	int i=0;

	int pre_start =0;
	int pre_burst=0;
	int max_waiting=0;
	int start;
	int turnaround;
	double average_wait;
	double average_turn;



	file.open("test2.txt",ios::in);
	if(!file)
	{
		cout<<"Error! Can not open the file"<<endl;
	}
	else
	{
        cout << "ID  "<<" Priority"<< "  Burst"<<"  Arrive "<<"  Start"<< "  Waiting" << "  Turnaround\n";
		while(file>>processid>>priority>>burst>>arrive)
		{
		    i++;

			start = find_start(arrive,pre_start, pre_burst);
			wait.push_back(find_waiting(arrive,pre_start, pre_burst));
			turnaround = start+burst-arrive;
			turn.push_back(turnaround);
			pre_start=start;
			pre_burst=burst;
			if(wait.back()>max_waiting)
				max_waiting=wait.back();
			cout<<processid<<"\t"<<priority<<"\t"<<burst<<"\t"<<arrive<<"\t"<<start<<"\t"<<wait.back()<<"\t"<<turnaround<<endl;
		}

	}

	double sum_wait = accumulate(wait.begin(),wait.end(),0);
	average_wait = sum_wait/wait.size();

	double sum_turn = accumulate(turn.begin(),turn.end(),0);
	average_turn = sum_turn/turn.size();

	cout<<"average turnaround time: "<<average_turn<<endl;
	cout<<"Max waiting time: "<<max_waiting<<endl;
	cout<<"average waiting time: "<<average_wait<<endl;
}


