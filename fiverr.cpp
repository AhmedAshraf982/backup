#include<iostream>
#include<vector>
#define MAX 1000   //Letting a max number of vertices and edges to be 1000, can be changed
using namespace std;
class Stack{    //stack will be used to do bactracking to find total possible circuits n the given graph
	vector<int> stack;
	public:
		Stack(){
		}
		void push(int element){
			stack.push_back(element);
		}
		int pop(){
			int hold = stack[stack.size()-1];
			stack.pop_back();
			return hold;
		}
		bool isPresent(int element){
			for(int x = 0; x < stack.size(); x++){
				if(element == stack[x]){
					return true;
				}
			}
			return false;
		}
		void showStack(){  //for checking purpose, not required for the given problem
			for(int x = 0; x < stack.size(); x++){
				cout << stack[x] << " ";
			}
			cout << endl;
		}
		int size(){
			return stack.size();
		}
		vector<int> vectorify(){
			return stack;
		}
};
class Graph{
	int vertexCount;    		 //number of given POIs
	vector<int> vertices[MAX];   //a 2D vector to hold the vertices(POIs) in all circuits
	vector<int> weights[MAX];    //a 2D vector to hold the weights of edges in all circuits
	vector<int> sumOfWeights;    //a 1D vector to hold the sum of weights in the reduced circuit
	vector<int> numPOI;          //a 1D vector to hold the number of vertices in each circuit
	vector<int> answers;		 //a 1D vector to hold answers of all the questions asked
	vector<vector<int> > track;  //a 2D vector to keep track of all the source vertices in a circuit
	vector<vector<int> > trackSrcs;  //a 2D vector to keep track of all the source vertices in reduced circuit
	vector<vector<int> > trackDests; //a 2D vector to keep track of all the destination vertices in reduced circuit
	Stack stack;
	int cyclesCount;     //total number of cycles in given graph
	int maxCircuitSize;  //number of POIs in largest circuit
	private:
		void separateVertices(vector<int>& sources, vector<int>& dests, vector<int> subgraph){
			for(int x = 0; x < subgraph.size()-1; x++){
				sources.push_back(subgraph[x]);
				dests.push_back(subgraph[(x+1)%subgraph.size()]);
			}
		}
		void swap(int& num1, int& num2){  //supporting function of sortWeights()
			int hold = num1;
			num1 = num2;
			num2 = hold;
		}
		void sortWeights(vector<int>& sources, vector<int>& dests, vector<int>& subweights){  //sorting the edges and weights
			for(int x = 0; x < subweights.size()-1; x++){
				for(int y = 0; y < subweights.size() - x - 1; y++){
					if(subweights[y] > subweights[y+1]){
						swap(subweights[y], subweights[y+1]);
						swap(sources[y], sources[y+1]);
						swap(dests[y], dests[y+1]);
					}
				}
			}
		}
		bool allVisited(bool isVisited[], int size){  //returns true if all the vertices are revealed
			for(int x = 0; x < size; x++){
				if(isVisited[x] == false){
					return false;
				}
			}
			return true;
		}
		bool isConnected(vector<int> subsources, vector<int> subdests){  //checks if all the vertices are connectet in the subgraph
			if(subsources.size() == 1){   //pre check for smallest possible circuit based on two verices
				return true;
			}
			for(int x = 0; x < subsources.size(); x++){
				int source = subsources[x];
				int dest = subdests[x];
				bool check = false;
				for(int y = 0; y < subsources.size(); y++){
					if(x != y){  
						if(source == subdests[y] || dest == subsources[y]){
							//connected edge
							check = true;
							break;
						}
					}
				}
				if(!check){
					return false;
				}
			}
			return true;
		}
		bool isAlreadyTracked(vector<int> sources, vector<int> dests){  //returns true, if two cycles are the same
			for(int x = 0; x < track.size(); x++){
				if(track[x] == sources){
					return true;
				}
			}
			track.push_back(sources);  //if its a new cycle, push to the track vector
			return false;
		}
		bool isOverlapping(vector<int> sources, vector<int> dests, vector<int> weights, int sum, int size){
			bool check = false;
			int sum_ = 0;
			int pos;
			int commEdges = 0;
			//	if there are common edges, we calculate the sum of weights of those edges, which are common
			for(int x = 0; x < trackSrcs.size(); x++){  //checks which previous reduced circuit is in common with new one
				for(int y = 0; y < trackSrcs[x].size(); y++){
					for(int z = 0; z < sources.size(); z++){
						if(sources[z] == trackSrcs[x][y] && dests[z] == trackDests[x][y]){
							check = true;	//overlapping
							sum_ += weights[z];
							pos = x;
							commEdges++;  //how many vertices are common in both circuits
						}
					}
				}
			}
			if(check){  //if edges are commmon, we add the total weighted sum of both circuits and subtract the sum of weights of those edges which are common
				sumOfWeights[pos] += sum;
				sumOfWeights[pos] -= sum_;
				numPOI[pos] += size;
				numPOI[pos] -= commEdges*2;   //one edge common has two vertices, thus mutiplying by two
				cyclesCount--;  //as both circuits are single unit now, we decrement the count of cycles
			}else{
				//if no edge is common, just simply push the newly detected circuit to tracking vecetors for future circuits to be compared
				trackSrcs.push_back(sources);
				trackDests.push_back(dests);
				numPOI.push_back(size);   //to keep record of maximum pois in each circuit
			}
			return check;
		}
		void kruskalsAlgo(vector<int> subgraph, vector<int> subweights){
			vector<int> sources;
			vector<int> dests;
			separateVertices(sources, dests, subgraph); //this function classifies all the sources in 'sources vector' and destinations in 'destinations vector'
			sortWeights(sources, dests, subweights);   	//sorting weights in increasing order along with corresponding source and destination, as said by Kruskal in his algorithm!
			if(isAlreadyTracked(sources, dests)){  //remember we had a tracking 2D vector called 'track'? here its use comes!
				return;
			}
			cyclesCount++;  //if a new cycle is detected, we increment the cycles count
			bool isVisited[sources.size()]; 			//to keep track of revealed vertices
			for(int x = 0; x < sources.size(); x++){    //initializing each vertex as false which means they are currenty not revealed
				isVisited[x] = false;
			}
			int sum = 0; 	//to compute sum of the weigths of each cycle
			vector<int> subsource;   //source vector that holds the sources of the edges to be added in the reduced circuit
			vector<int> subdest;	//destination vector that holds the destinations of the edges to be added in the reduced circuit
			bool check = true; //just a flag
			for(int x = 0; x < subweights.size(); x++){
				int pos1 = findPos(subgraph, sources[x]);	//same purpose of this findPos() function as previously did!
				int pos2 = findPos(subgraph, dests[x]);
				if(isVisited[pos1] && isVisited[pos2] && check){   //if those two vertices have already been revealed, just move to the next iteration of the loop
					continue;
				}
				//else, add that edge, and reveal those two vertices
				isVisited[pos1] = true;
				isVisited[pos2] = true;
				sum += subweights[x];	//as an edge is added, add its weight to the sum of weights
				subsource.push_back(sources[x]);   //push that source to the subsource vector
				subdest.push_back(dests[x]);		//push that destination to the subsource destination
				if(allVisited(isVisited, sources.size())){   //if all the vertices have been revealed, check for any gaps(disconnections) in graph
					if(isConnected(subsource, subdest)){  //if all the vertices that have been revealed are connected, congrats! we have a reduced graph!
						break;
					}
					//else, connect the next edge to connect the vertices
					check = false;
				}
			}
			//check for intersection of the circuits, if any two different circuits have edges in common, join them to make a single unit
			if(!isOverlapping(subsource, subdest, subweights, sum, subgraph.size()-1)){  //if there is no edge common, just push the weighted sum to the sumOfWeights vector
				sumOfWeights.push_back(sum);
			}
		}
		int findPos(vector<int> vertexList, int neigh){
			for(int x = 0; x < vertexList.size(); x++){
				if(vertexList[x] == neigh){
					return x;
				}
			}
		}
		void makeSubset(Stack stack){  //this function makes two vectors, the vertices in the circuit, and weights between two adjacent vertices in the vertex vector
			vector<int> subgraph = stack.vectorify();   //subset of the graph which forms a ciruit in vector form
			vector<int> subWeights;						//weights of two consecutive vertices in the subgraph vector
			for(int x = 0; x < stack.size()-1; x++){    //subgraph vector includes the source vertex again at the end, thus reducing size by 1
				int pos = findPos(vertices[subgraph[x]], subgraph[x+1]);  //findPos() function gives the position of a particular element in the given vector
				subWeights.push_back(weights[subgraph[x]][pos]);  //subWeights vector is filled here, holding the weights of the edges in the cycle we previously detected
			}
			//after the successful execution of the above loop, we have two vectors, subgraph, which has the vertices of the cycle, and subWeights, which has the weights of the edges in that cycle
			kruskalsAlgo(subgraph, subWeights); //Now, the Kruskal's Algorithm turn!
		}
		void detectCycleFromAVertex(int source, int next){
			if(source == next){   //to avoid this check for first function call, we set next = -1
			//if source and next are equal, it shows a cycle has been detected
				stack.push(next);
				makeSubset(stack);   //after the detection of a cycle, next step is to reduce it according to the given conditions in the question!
				stack.pop();
				return;
			}
			if(next == -1){
				next = source;   //setting back next to the source as the first check has been avoided
			}
			if(stack.isPresent(next)){  //we check the repetition of a vertex other than the source. If a vertex is repeated, it will be discarded because only those cycles will be considered, which  are formed by the source vertex 
				return;
			}
			stack.push(next);  //keep adding neighbouring vertices to the stack 
			for(int x = 0; x < vertices[next].size(); x++){  //recursive call with respect to its neighbour as the 'next'
				detectCycleFromAVertex(source, vertices[next][x]);
			}
			stack.pop();   //for each backtracking, we pop the recently added vertex.
		}
	public:
		Graph(){  //default constructor
		}
		Graph(int num){ //parametric constructor
			vertexCount = num;
			cyclesCount = 0;
			maxCircuitSize = 0;
		}
		void setVertexCount(int num){  //a setter funtion of vertexCount
			vertexCount = num;
			cyclesCount = 0;
			maxCircuitSize = 0;
		}
		void addEdge(int source, int dest, int weight){   //adding edges to the graph
			vertices[source-1].push_back(dest-1);
			weights[source-1].push_back(weight);
		}
		void adjacencyList(){  //for checking purpose, not required for the problem
			for(int x = 0; x < vertexCount; x++){
				for(int y = 0; y < vertices[x].size(); y++){
					cout << vertices[x][y] << " ";
				}
				cout << endl;
			}
		}
		vector<int> cycleDetection(int queries){  //a wrapper function which calls detectCycleFromAVertex(), which is used to detect a cycle from a passed vertex  as its parameter
			for(int x = 0; x < vertexCount; x++){
				detectCycleFromAVertex(x, -1);   //here -1 shows that this function call has just begun!
			}
			//after successful execution of detectCycleFromAVertex(), we are able to get answers of all the 4 asked questions, which are stored and retruned in answers vector as follows:
			answers.push_back(getCycles());
			answers.push_back(getMaxPOI());
			answers.push_back(longestLane());
			answers.push_back(getTotalLength());
			vector<int> temp;
			for(int x = 0; x < queries; x++){   //depending upon the number of questions asked, we return a vector to the main function, having answers to the asked question only
				temp.push_back(answers[x]);
			}
			return temp;
		}
		void showSum(){   //for checking purpose, not required for the problem
			for(int x = 0; x < sumOfWeights.size(); x++){
				cout << sumOfWeights[x] << endl;
			}
		}
		int getTotalLength(){   //question 4
			int sum = 0;
			for(int x = 0; x < sumOfWeights.size(); x++){
				sum += sumOfWeights[x];
			}
			return sum;
		}
		int getMaxPOI(){   //question 2
			if(numPOI.size() > 0){
				int max = numPOI[0];
				for(int x = 1; x < numPOI.size(); x++){
					if(max < numPOI[x]){
						max = numPOI[x];
					}
				}
				return max;
			}
		}
		int getCycles(){   //question 1
			return cyclesCount;
		}
		int longestLane(){  //question 3
			if(sumOfWeights.size() > 0){
				int max = sumOfWeights[0];
				for(int x = 1; x < sumOfWeights.size(); x++){
					if(max < sumOfWeights[x]){
						max = sumOfWeights[x];
					}
				}
				return max;
			}
		}
};

//driver code
int main(){
	int num; 
	//Enter the data as mentioned in the test case
	cin >> num;   //number of test cases
	int pois, conns, ques;
	vector<vector<int> > answers;
	for(int x = 0; x < num; x++){
		cin >> pois >> conns >> ques;   //the convention is same as mentioned in the quesion, i.e. number of pois, number of connections(edges), number of questions
		Graph graph(pois);
		for(int y = 0; y < conns; y++){
			int source, dest, weight;
			cin >> source >> dest >> weight;
			graph.addEdge(source, dest, weight);
		}
		answers.push_back(graph.cycleDetection(ques));   //here the work begins!
	}
	//showing answers
	for(int x = 0; x < answers.size(); x++){
		for(int y = 0; y < answers[x].size(); y++){
			cout << answers[x][y] << " ";
		}
		cout << endl;
		
	}
}
