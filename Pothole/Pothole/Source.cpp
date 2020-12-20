#include <iostream>
#include <queue>
using namespace std;

//global variable for the graph to set max for number of chambers in the cave, sight to the next room, and knowledge of previous room
int Graph[201][201];
int Sightline[201];
int PreviousRoom[201];
//global variable for chamber level number
int n;

//network flow algorithm
double NetworkFlow(int s, int t)
{
	int flow = 0;
	while(true)
	{
		//set to largest possible number for a type int
		int path = 2147483647;

		//queue of cave as it starts at room 1 then the next highest room is 2, 3, 4, ..., x
		queue<int> cave;
		memset(Sightline, 0, sizeof Sightline);
		memset(PreviousRoom, -1, sizeof PreviousRoom);

		//start finding cave flow for speleologist including setting previous room
		Sightline[s] = true;
		cave.push(s);
		PreviousRoom[s] = s;
		while(!cave.empty())
		{
			//take current room off of queue
			int currentRoom = cave.front();
			cave.pop();
			for (int i = 1; i <= n; i++) 
			{
				//checks if previous room doesnt exist and current room does exist
				if(PreviousRoom[i] == -1 and Graph[currentRoom][i] > 0)
				{
					//find next lowest room and set previous room to current room
					path = min(path, Graph[currentRoom][i]);
					PreviousRoom[i] = currentRoom;
					if(i != t)
					{
						cave.push(i);
					}else {
						while(PreviousRoom[i] != i)
						{
							//moves through cave and subtracts or add to path total and then sets current room again
							currentRoom = PreviousRoom[i];
							Graph[currentRoom][i] -= path;
							Graph[i][currentRoom] += path;
							i = currentRoom;
						}
						flow += path;
						break;
					}
				}
			}
		}
		//Checks if previous room exists if it doesnt breaks infinite loop
		if(PreviousRoom[t] == -1)
		{
			return false;
		}
	}
	//return our answer
	return flow;
}


int main()
{
	//logic for number of tests to run
	int test = 0;
	cout << "How many tests would you like to run? ";
	cin >> test;

	//logic to run program for all tests
	while(test--)
	{
		memset(Graph, 0, sizeof Graph);
		//get number of chambers in the cave
		cout << "How many chambers are in this cave? ";
		cin >> n;
		for(int i = 1; i < n; i++)
		{
			//get number of corridors exiting room 
			int m;
			cout << "which corridors exit the room? ";
			cin >> m;
			while(m--)
			{
				//logic for taking corridors and base cases
				int x;
				cin >> x;
				if( i == 1 || x == n)
				{
					Graph[i][x] = 1;
				}else {
					Graph[i][x] = 2147483647;
				}
			}
		}
		//Print answer
		cout << (NetworkFlow(1, n));
	}
}