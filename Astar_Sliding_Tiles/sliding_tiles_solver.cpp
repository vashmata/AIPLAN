// Example program
#include <iostream>
#include <vector>
#include <array>

using namespace std;

array<int,9> initialState = {7,2,4,5,0,6,8,3,1};
array<int,9> randomState = {3,7,4,5,0,6,2,8,1};
array<int,9> goalState = {0,1,2,3,4,5,6,7,8};

int maxIterations = 15;
int gridWidth = 3;
int gridHeight = 3;

void printState(array<int,9> state);

int findRow(int tile, array<int,9> state);
int findCol(int tile, array<int,9> state);

int resetState(vector<array<int,9>> fringe, int pos);
int setState(vector<array<int,9>> fringe, int pos, array<int,9> state);
int findEmptyTile(array<int,9> state);

int h1(array<int,9> state);
int g1(array<int,9> state);
int h2(array<int,9> state);
int g2(array<int,9> state);


int greedy1(array<int,9> currState){
    int hVal = h1(currState);
    return hVal;
}
int aStar1(array<int,9> currState){
    int hVal = h1(currState);
    int gVal = g1(currState);
    return hVal+gVal;
}

int greedy2(array<int,9> currState){
    int hVal = h2(currState);
    return hVal;
}
int aStar2(array<int,9> currState){
    int hVal = h2(currState);
    int gVal = g2(currState);
    return hVal+gVal;
}


int selectFrom(vector<array<int,9>> fringe, int (*strategy)(array<int,9> state), int numNodes){
	cout<<"Calculating cost from ";
	if(strategy==aStar2) cout<<"A*2";
	if(strategy==greedy2) cout<<"Greedy2";
	cout<<" method\n";
	int bestNode = 0;
	int bestCost = strategy(fringe[bestNode]);
	cout << "cost is " << bestCost << "\n";
	int nodePos=1;
	while(nodePos < numNodes){
	    int cost = strategy(fringe[nodePos]);
	    cout << "cost is " << cost << "\n";
	    if(cost<bestCost){
	        bestNode = nodePos;
	        bestCost = cost;
	    }
	    nodePos++;
	}
	return bestNode;
}

vector<array<int,9>> explore(array<int,9> state){
    int emptyTile = findEmptyTile(state);
    int tileRow = findRow(0,state);
    int tileCol = findCol(0,state);
    int possibleStates;
    
    vector<array<int,9>> fringe;
    array<int,9> state1, state2, state3, state4;
    switch(emptyTile){
        case 0:
        case 2:
        case 6:
        case 8:
            possibleStates = 2;
            int v,h;
            switch(emptyTile){
                case 0:
                    v = 3; h = 1;
                    break;
                case 2:
                    v = 3; h = -1;
                    break;
                case 6:
                    v = -3; h = 1;
                    break;
                case 8:
                    v = -3; h = -1;
                    break;
            }
            for(int i=0;i<9;i++){
                if(i==emptyTile){
                    state1[i] = state[i+v];
                    state2[i] = state[i+h];
                }
                else if(i==emptyTile+v){
                    state1[i] = 0;
                    state2[i]=state[i];
                }
                else if(i==emptyTile+h){
                    state2[i] = 0;
                    state1[i]=state[i];
                }
                else{
                    state1[i]=state[i];
                    state2[i]=state[i];
                }
            }
            fringe.push_back(state1);
            fringe.push_back(state2);
            break;
        case 1:
        case 3:
        case 5:
        case 7:
            possibleStates = 3;
            int s1,s2,t;
            switch(emptyTile){
                case 1:
                    s1=-1;s2=1;t=3;
                    break;
                case 7:
                    s1=-1;s2=1;t=-3;
                    break;
                case 3:
                    s1=-3;s2=3;t=1;
                    break;
                case 5:
                    s1=-3;s2=3;t=-1;
                    break;
            }
            for(int i=0;i<9;i++){
                if(i==emptyTile){
                    state1[i] = state[i+s1];
                    state2[i] = state[i+s2];
                    state3[i] = state[i+t];
                }
                else if(i==emptyTile+s1){
                    state1[i] = 0;
                    state2[i]=state[i];
                    state3[i]=state[i];
                }
                else if(i==emptyTile+s2){
                    state2[i] = 0;
                    state1[i]=state[i];
                    state3[i]=state[i];
                }
                else if(i==emptyTile+t){
                    state3[i] = 0;
                    state1[i]=state[i];
                    state2[i]=state[i];
                }
                else{
                    state1[i]=state[i];
                    state2[i]=state[i];
                    state3[i]=state[i];
                }
            }
            fringe.push_back(state1);
            fringe.push_back(state2);
            fringe.push_back(state3);
            break;
        case 4:
            possibleStates = 4;
            for(int i=0;i<9;i++){
                if(i==emptyTile){
                    state1[i] = state[i-1];
                    state2[i] = state[i+1];
                    state3[i] = state[i-3];
                    state4[i] = state[i+3];
                }
                else if(i==emptyTile-1){
                    state1[i] = 0;
                    state2[i]=state[i];
                    state3[i]=state[i];
                    state4[i]=state[i];
                }
                else if(i==emptyTile+1){
                    state2[i] = 0;
                    state1[i]=state[i];
                    state3[i]=state[i];
                    state4[i]=state[i];
                }
                else if(i==emptyTile-3){
                    state3[i] = 0;
                    state1[i]=state[i];
                    state2[i]=state[i];
                    state4[i]=state[i];
                }
                else if(i==emptyTile+3){
                    state4[i] = 0;
                    state1[i]=state[i];
                    state2[i]=state[i];
                    state3[i]=state[i];
                }
                else{
                    state1[i]=state[i];
                    state2[i]=state[i];
                    state3[i]=state[i];
                    state4[i]=state[i];
                }
            }
            fringe.push_back(state1);
            fringe.push_back(state2);
            fringe.push_back(state3);
            fringe.push_back(state4);
            break;
        default:
            possibleStates = 0;
            break;
    }

    return fringe;
}

int main()
{
    /*
    cout << "h1 for initial state gives: " << h1(initialState) << "\n";
    cout << "h1 for goal state gives: " << h1(goalState) << "\n";
    cout << "g1 for initial state gives: " << g1(initialState) << "\n";
    cout << "g1 for goal state gives: " << g1(goalState) << "\n";
    cout << "\n";
    cout << "h2 for initial state gives: " << h2(initialState) << "\n";
    cout << "h2 for random state gives: " << h2(randomState) << "\n";
    cout << "h2 for goal state gives: " << h2(goalState) << "\n";
    cout << "g2 for initial state gives: " << g2(initialState) << "\n";
    cout << "g2 for random state gives: " << g2(randomState) << "\n";
    cout << "g2 for goal state gives: " << g2(goalState) << "\n";
    cout << "\n";
    */
    
    /*
    //int fringe[maxSize][9];
    
    setState(fringe, 0, initialState);
    setState(fringe, 1, randomState);
    setState(fringe, 2, goalState);
    
    int greedy1Result = selectFrom(fringe,greedy1,3);
    cout << "greedy1 node is " << greedy1Result << "\n";
    cout << "\n";
    int aStar1Result = selectFrom(fringe,aStar1,3);
    cout << "A*1 node is " << aStar1Result << "\n";
    cout << "\n";
    int greedy2Result = selectFrom(fringe,greedy2,3);
    cout << "greedy2 node is " << greedy2Result << "\n";
    cout << "\n";
    int aStar2Result = selectFrom(fringe,aStar2,3);
    cout << "A*2 node is " << aStar2Result << "\n";
    cout << "\n";
    */
    
    cout << "The goal state is:" << "\n";
    printState(goalState);
    cout << "The initial state is:" << "\n";
    printState(initialState);
    
    vector<array<int,9>> fringe;
    fringe.push_back(initialState);
    int emptyTile = findEmptyTile(initialState);
    cout << "Row: " << findRow(0,initialState) << "\tCol: " << findCol(0,initialState) << "\n";
    cout << "\n";
    
    vector<array<int,9>> currFringe = explore(initialState);
    cout<<"Printing available future states: \n\n";
    for (int i=0;i<currFringe.size();i++){
        printState(currFringe[i]);
        cout<<"\n";
    }
    //int bestGreedyNode = selectFrom(currFringe, greedy2, currFringe.size());
    int bestAStarNode = selectFrom(currFringe, aStar2, currFringe.size());
    int iteration = 1;
    
    while(aStar2(currFringe[bestAStarNode]) != 0 && iteration < maxIterations){
        cout << "Starting again from option " << bestAStarNode << ":\n";
        cout << "Cost of option is " << aStar2(currFringe[bestAStarNode]) << "\n";
        printState(currFringe[bestAStarNode]);
        currFringe = explore(currFringe[bestAStarNode]);
        cout<<"Printing available future states: \n\n";
        for (int i=0;i<currFringe.size();i++){
            printState(currFringe[i]);
            cout<<"\n";
        }
        bestAStarNode = selectFrom(currFringe, aStar2, currFringe.size());
        iteration++;
    }
    if(iteration==maxIterations) cout<<maxIterations<<" iterations have occured, giving up\n";
    else cout<<"Succeeded in finding goal!\n";
 
}

void printState(array<int,9> state){
    cout << state[0] << " " << state[1] << " " << state[2] << "\n";
    cout << state[3] << " " << state[4] << " " << state[5] << "\n";
    cout << state[6] << " " << state[7] << " " << state[8] << "\n";
}

int findRow(int tile, array<int,9> state){
    if(tile==state[0] || tile==state[1] || tile==state[2]) return 0;
	else if(tile==state[3] || tile==state[4] || tile==state[5]) return 1;
	else if(tile==state[6] || tile==state[7] || tile==state[8]) return 2;
	else return -1;
}
int findCol(int tile, array<int,9> state){
    if(tile==state[0] || tile==state[3] || tile==state[6]) return 0;
	else if(tile==state[1] || tile==state[4] || tile==state[7]) return 1;
	else if(tile==state[2] || tile==state[5] || tile==state[8]) return 2;
	else return -1;
}

int resetState(vector<array<int,9>> fringe, int pos){
    for(int i=0;i<9;i++) fringe[pos][i]=0;
}
int setState(vector<array<int,9>> fringe, int pos, array<int,9> state){
    for(int i=0;i<9;i++) fringe[pos][i]=state[i];
}
int findEmptyTile(array<int,9> state){
    for(int i=0;i<9;i++){
        if(state[i]==0){
            cout << "The empty tile is in position " << i << "\n";
            return i;
        }
    }
    cout << "The empty tile was not found\n";
    return -1;
}

int h1(array<int,9> state){
	int misplacedTiles = 0;
	for(int i=0;i<9;i++){
		if(state[i] != goalState[i]){
			if(state[i] != 0) misplacedTiles++;
		}
	}
	return misplacedTiles;
}
int g1(array<int,9> state){
	int misplacedTiles = 0;
	for(int i=0;i<9;i++){
		if(state[i] != initialState[i]){
			if(state[i] != 0) misplacedTiles++;
		}
	}
	return misplacedTiles;
}

int h2(array<int,9> state){
	int blockDistance = 0;
	//cout << "h2 = ";
	for(int i=0;i<9;i++){
	    if (state[i] != 0){
    	    int tileVal = state[i];
    		int tileRow = findRow(tileVal,state);
    		int tileCol = findCol(tileVal,state);
    		int goalRow = findRow(tileVal,goalState);
    		int goalCol = findCol(tileVal,goalState);
    		int rowDist = abs(tileRow-goalRow);
    		int colDist = abs(tileCol-goalCol);
    		blockDistance +=  rowDist + colDist;
    		//cout << rowDist+colDist;
    		//if(i<8) cout << "+";
    		//cout << "pos " << i << " has val " << tileVal << "\n";
    		//cout << "pos " << i << " has rowdist " << rowDist << " and coldist " << colDist << "\n";
	    }
	}
	//cout << " = " << blockDistance << "\n";
	return blockDistance;
}
int g2(array<int,9> state){
	int blockDistance = 0;
	for(int i=0;i<9;i++){
	    if (state[i] != 0){
    	    int tileVal = state[i];
    		int tileRow = findRow(tileVal,state); int tileCol = findCol(tileVal,state);
    		int initRow = findRow(tileVal,initialState); int initCol = findCol(tileVal,initialState);
    		blockDistance +=  abs(tileRow-initRow) + abs(tileCol-initCol);
	    }
	}
	return blockDistance;
}

