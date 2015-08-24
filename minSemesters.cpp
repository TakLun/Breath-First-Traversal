#include <iostream>
#include <queue>
#include <vector>
#include <iomanip>

using namespace std;

struct node{

	node *requires[2];
	bool isRoot;
	int value;
	int name;
	bool explored;

};

node *cs[16];
vector <int> rootNodes; 
int **adjMatrix = new int*[16];


void makeGraph(){

	
	cs[15]->requires[0] = cs[14];
	cs[15]->requires[1] = NULL;
	cs[15]->isRoot = 1;
	
	cs[14]->requires[0] = cs[4];
	cs[14]->requires[1] = cs[6];
	cs[14]->isRoot = 0;
	
	cs[13]->requires[0] = cs[6];
	cs[13]->requires[1] = NULL;
	cs[13]->isRoot = 1;
	
	cs[12]->requires[0] = cs[3];
	cs[12]->requires[1] = NULL;
	cs[12]->isRoot = 1;
	
	cs[11]->requires[0] = cs[8];
	cs[11]->requires[1] = NULL;
	cs[11]->isRoot = 1;
	
	cs[10]->requires[0] = cs[9];
	cs[10]->requires[1] = NULL;
	cs[10]->isRoot = 1;
	
	cs[9]->requires[0] = cs[7];
	cs[9]->requires[1] = NULL;
	cs[9]->isRoot = 0;
	
	cs[8]->requires[0] = cs[5];
	cs[8]->requires[1] = cs[6];
	cs[8]->isRoot = 0;
	
	cs[7]->requires[0] = cs[4];
	cs[7]->requires[1] = NULL;
	cs[7]->isRoot = 0;
	
	cs[6]->requires[0] = cs[1];
	cs[6]->requires[1] = cs[3];
	cs[6]->isRoot = 0;
	
	cs[5]->requires[0] = cs[4];
	cs[5]->requires[1] = NULL;
	cs[5]->isRoot = 0;
	
	cs[4]->requires[0] = cs[2];
	cs[4]->requires[1] = NULL;
	cs[4]->isRoot = 0;
	
	cs[3]->requires[0] = NULL;
	cs[3]->requires[1] = NULL;
	cs[3]->isRoot = 0;
	
	cs[2]->requires[0] = NULL;
	cs[2]->requires[1] = NULL;
	cs[2]->isRoot = 0;
		
	cs[1]->requires[0] = NULL;
	cs[1]->requires[1] = NULL;
	cs[1]->isRoot = 0;
}

void BFT(int root, int gSize){
	
	queue <node> Q;
	
	// Push initial vertex to the queue
    Q.push(*cs[root]);
    cs[root]->explored = true; // mark it as explored
    cs[root]->value = 1;
    
    
    /*cout << "Breadth first Search starting from vertex ";
    cout << root << " : " << endl;
    */
 
    while (!Q.empty()) {
    
        // Pop the vertex from the queue 
        int v = Q.front().name;
        Q.pop();
        
        // display the explored vertices 
        /*cout << v << " ";
        cout << "= " << cs[v]->value << " | ";*/
 
        //From the explored vertex v try to explore all the connected vertices
        for (int i = 1; i <= gSize; i++){
 
          if (adjMatrix[v][i]==1){
          	Q.push(*cs[i]);
          	if(!cs[i]->explored) {
	               cs[i]->explored = true;
               	cs[i]->value = cs[v]->value + 1;
               }else if(cs[i]->value <= cs[v]->value){
               	cs[i]->value = cs[v]->value + 1;               
               }
          }
            
        }
    }
    //cout << endl << endl;

}

int main(){
	
	int courseSize = 15;
	int numRoots = 0;
	int minSemesters = 0;
	
	
	for(int i=0;i<=courseSize;i++){
		cs[i] = new node;
		cs[i]->name = i;
		cs[i]->explored = 0;
	}
	
	makeGraph();
	
	for(int i=0;i<=courseSize;i++){
		if(cs[i]->isRoot == 1){
			numRoots++;
		}
	}
	
	for(int i=1;i<=courseSize;i++){
		if(cs[i]->isRoot == 1){
			rootNodes.push_back(cs[i]->name);
		}
	}

	//create Adjacency Matrix
	for(int i=0;i<16;i++){
		adjMatrix[i] = new int[16];	
	}
	
	for(int i=1;i<=courseSize;i++){
		for(int j=1;j<=courseSize;j++){
			if((cs[i]->requires[0] == cs[j]) || (cs[i]->requires[1] == cs[j]))
				adjMatrix[i][j] = 1;
		}
	}
	
	//Print out adjacency matrix
	/*cout << setw(10);
	for(int i=1; i<=courseSize;i++){
		cout << i << setw(2) << "|" << setw(2);
	}cout << endl;
	
	cout << "    ";
	for(int i=1; i<=courseSize;i++){
		cout << setw(4) << "|" << setw(4);
	}cout << "|" << endl;
	 
	cout << " ";
	for(int i=1; i<=courseSize;i++){
		cout << i << setw(2) << "|" << setw(4) << "|" << setw(2);
			
		for(int j=1; j<=courseSize; j++){
				if(adjMatrix[i][j] == 0)
					cout << "-" << setw(2) << "|" << setw(2);
				else
					cout << adjMatrix[i][j] << setw(2) << "|" << setw(2);
		}
		cout << endl;
	}*/
	
	
	
	for(int i=0;i<=courseSize;i++){
		cs[i]->explored = 0;
	}
	
	for(vector<int>::size_type i = 0; i != rootNodes.size(); i++) {
		BFT(rootNodes[i], courseSize);
	}
	
	
	minSemesters = cs[1]->value;
	for(int i=2;i<=courseSize;i++){
		if(minSemesters < cs[i]->value){
			minSemesters = cs[i]->value;
		}
	}
	
	
	cout << "Minimum number of semesters is " << minSemesters << " semesters" << endl;
	
	return 0;
}
