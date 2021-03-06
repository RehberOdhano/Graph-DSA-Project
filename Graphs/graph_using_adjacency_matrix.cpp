#include <iostream>
#include <string>
#include <limits.h>
#include "queue.cpp" // simple FIFO and priority queue
#include "stack.cpp"
using namespace std;

class Graph {
	public:
		int** adjacency_matrix;
		int* visited_nodes;
		int* distances;
		int* mst_list;
		int* parent_nodes;
		int num_of_vertices = 0;
	public:

		// initializing the adjacency matrix
		void Create_Graph(int numOfVertices);

		// setting/adding the edge
		void set_edge(int from, int to, int cost);

		// removing an edge by the element at [i][j]th position to 0
		void remove_edge(int from, int to);

		// displaying the adjacency matrix
		void display_graph();

		// setting the elements of visited_nodes to 0
		void reset();

		// Breadth-First Search
		// s -> source node
		void BFS(int s);

		// Depth-First Search
		void DFS(int s);

		// finding the shortest path
		void dijkstra_shortest_path(int src);

		// finding the path with minimum cost
		void prims_MST(int random_node);

		// for finding the valid edge and used in prim's algorithm
		bool is_valid_edge(int u, int v);

		// HELPER FUNCTIONS FOR KRUSKAL'S ALGORITHM
		int find_set(int i);
		void union_set(int i, int j);

		// finding the path with minimum cost
		void kruskal_MST();

		// destructor - used for removing the adjacency matrix from the memory
		~Graph();
		
};

void Graph::Create_Graph(int numOfVertices) {
	this->num_of_vertices = numOfVertices;
	visited_nodes = new int[num_of_vertices];
	mst_list = new int[num_of_vertices];
	distances = new int[num_of_vertices];
	parent_nodes = new int[num_of_vertices];

	for(int i = 0; i < num_of_vertices; i++) {
		visited_nodes[i] = 0;
		distances[i] = INT_MAX;
		mst_list[i] = 0;
	}

	adjacency_matrix = new int*[num_of_vertices];
	for(int i = 0; i < num_of_vertices; i++) {
		adjacency_matrix[i] = new int[num_of_vertices];
		for(int j = 0; j < num_of_vertices; j++) {
			adjacency_matrix[i][j] = INT_MAX;
		}
	}
}

Graph::~Graph() {
	for(int i = 0; i < num_of_vertices; i++) {
		delete[] adjacency_matrix[i];
	}
	delete[] adjacency_matrix;
	num_of_vertices = 0;
	cout<<"GRAPH IS DELETED SUCCESSFULLY!"<<endl;
}

void Graph::display_graph() {
	if(num_of_vertices == 0) {
		cout<<"GRAPH IS EMPTY!"<<endl;
	} else {
		cout<<"\nGRAPH - ADJACENCY MATRIX"<<endl;
		cout<<"------------------------"<<endl;
		for(int i = 0; i < num_of_vertices; i++) {
			for(int j = 0; j < num_of_vertices; j++) {
				cout<<adjacency_matrix[i][j]<<" ";
			}
			cout<<endl;
		}
		cout<<"------------------------"<<endl;
	}
}

void Graph::remove_edge(int from, int to) {
	if((adjacency_matrix[from][to] == INT_MAX && adjacency_matrix[from][to] < INT_MAX) || 
		(adjacency_matrix[to][from] == INT_MAX && adjacency_matrix[to][from] < INT_MAX)) {
		cout<<"EDGE("<<from<<", "<<to<<") IS ALREADY REMOVED!"<<endl;		
	} else {
		adjacency_matrix[from][to] = INT_MAX;
		adjacency_matrix[to][from] = INT_MAX;
		cout<<"EDGE("<<from<<", "<<to<<") IS REMOVED SUCCESSFULLY!"<<endl;
	}
}

void Graph::set_edge(int from, int to, int cost) {
	if((adjacency_matrix[from][to] >= 0 && adjacency_matrix[from][to] < INT_MAX) || 
		(adjacency_matrix[to][from] >= 0 && adjacency_matrix[to][from] < INT_MAX)) {
		cout<<"EDGE("<<from<<", "<<to<<") IS ALREADY SET!"<<endl;		
	} else {
		if((from >= 0 && from < num_of_vertices) && (to >= 0 && to < num_of_vertices)) {
			adjacency_matrix[from][to] = cost;
			adjacency_matrix[to][from] = cost;
			cout<<"EDGE("<<from<<", "<<to<<") IS SET SUCCESSFULLY!"<<endl;		
		} else {
			cout<<"PLEASE ENTER A VALID POSITION..."<<endl;
		}	
	}
}

void Graph::reset() {
	for(int i = 0; i < num_of_vertices; i++) {
		visited_nodes[i] = 0;
		distances[i] = INT_MAX;
		mst_list[i] = 0;
	}
}

void Graph::BFS(int s) {
	Queue q;

	// cout<<"VISITED: ";
	// for(int i = 0; i < num_of_vertices; i++) {
	// 	cout<<visited_nodes[i]<<" ";
	// }
	// cout<<endl;

	visited_nodes[s] = 1;
	q.push(s);

	cout<<"BFS TRAVERSAL: ";
	while(!q.isEmpty()) {
		int node = q.pop();
		cout<<node<<" ";

		// neighbours of the current node
		int* nbr = adjacency_matrix[node];
		// int* temp = nbr;
		// cout<<"NBRS: ";
		// for(int i = 0; i < num_of_vertices; i++) {
		// 	cout<<*temp++<<" ";
		// } 

		for(int i = 0; i < num_of_vertices; i++) {
			// cout<<*nbr<<endl;
			if((*nbr >= 0 && *nbr < INT_MAX) && !visited_nodes[i]) {
				visited_nodes[i] = 1;
				q.push(i);
			}
			nbr++;
		}
		// cout<<endl;
		// q.display();
	}
	cout<<endl;
}

void Graph::DFS(int s) {
	Stack stack;

	// cout<<"VISITED: ";
	// for(int i = 0; i < num_of_vertices; i++) {
	// 	cout<<visited_nodes[i]<<" ";
	// }
	// cout<<endl;

	stack.push(s);

	while(!stack.isEmpty()) {
		int node = stack.pop();
		// cout<<"NODE: "<<node<<endl;
		if(!visited_nodes[node]) {
			cout<<node<<" ";
			visited_nodes[node] = 1;
		}

		int* nbr = adjacency_matrix[node];
		for(int i = 0; i < num_of_vertices; i++) {
			if((*nbr >= 0 && *nbr < INT_MAX) && !visited_nodes[i]) {
				stack.push(i);
			}
			nbr++;
		}
	}
	cout<<endl;
}

void Graph::dijkstra_shortest_path(int src) {
	
	Priority_Queue pq;
	pq.push(src);

	// setting the distance of source/starting node to 0
	distances[src] = 0; 

	while(!pq.isEmpty()) {
		int node = pq.pop();
		visited_nodes[node] = 1;
		// neighbours of the current node "node"
		int* nbrs = adjacency_matrix[node];

		for(int i = 0; i < num_of_vertices; i++) {
			// check if there is an edge or not and if the node is already
			// visited or not
			if((nbrs[i] > 0 && nbrs[i] < INT_MAX) && !visited_nodes[i]) {
				if(distances[node] + nbrs[i] < distances[i]) {
					distances[i] = distances[node] + nbrs[i];
					pq.push(i);
					// nbrs++;
				}
			} 
		}
	}

	cout<<"DIJKSTRA'S SHORTEST PATH: ";
	for(int i = 0; i < num_of_vertices; i++) {
		if(distances[i] == INT_MAX) cout<<" -1 ";
		else cout<<distances[i]<<" "; 
	}
	cout<<endl;
}

bool Graph::is_valid_edge(int u, int v) {
	// checks whether the edge(i, j) is valid or not
	// A valid egde is one whose one end is already 
	// included in mst_list and other end is not in mst_list
	if(u == v) return false;
	if(mst_list[u] == 0 && mst_list[v] == 0) return false;
	if(mst_list[u] == 1 && mst_list[v] == 1) return false;

	return true;
}

void Graph::prims_MST(int random_node) {
	// Priority_Queue pq;
	// pq.push(random_node);

	mst_list[random_node] = 1;
	int num_of_edges = 0, min_cost_of_path = 0;

	while (num_of_edges < (num_of_vertices - 1)) {
	    int min = INT_MAX, p = -1, q = -1;
	    for (int i = 0; i < num_of_vertices; i++) {
	      	if (mst_list[i]) {
		        for (int j = 0; j < num_of_vertices; j++) {
		          	if (!mst_list[j] && (adjacency_matrix[i][j] > 0 && adjacency_matrix[i][j] < INT_MAX)) {  
			            if (min > adjacency_matrix[i][j]) {
			              	min = adjacency_matrix[i][j];
			              	p = i;
			              	q = j;
			            }
		          	}
		        }
	    	}
    	}
    	if(p != -1 && q != -1) {
    		cout<<"EDGE ("<<p<<", "<<q<<"): "<<adjacency_matrix[p][q]<<endl;
			min_cost_of_path += min;
			mst_list[q] = mst_list[p] = 1;
			num_of_edges++;
		}
    	// cout<<"EDGE ("<<p<<", "<<q<<"): "<<adjacency_matrix[p][q]<<endl;
	    // mst_list[q] = 1;
	    // num_of_edges++;
	}
	cout<<"\nMINIMUM COST USING PRIM'S ALGORITHM: "<<min_cost_of_path<<endl;
}

int Graph::find_set(int i) {
  // If i is the parent of itself
  if (i == parent_nodes[i])
    return i;
  else
    // Else if i is not the parent of itself
    // Then i is not the representative of his set,
    // so we recursively call Find on its parent
    return find_set(parent_nodes[i]);
}

void Graph::union_set(int i, int j) {
  int m = find_set(i);
  int n = find_set(j);
  parent_nodes[m] = n;
}

void Graph::kruskal_MST() {
	int min_cost_of_path = 0;

	for(int i = 0; i < num_of_vertices; i++) {
		parent_nodes[i] = i;
	}

	// Include minimum weight edges one by one
    int num_of_edges = 0;
    while (num_of_edges < num_of_vertices - 1) {
        int min = INT_MAX, a = -1, b = -1;
        for (int i = 0; i < num_of_vertices; i++) {
            for (int j = 0; j < num_of_vertices; j++) {
                if (find_set(i) != find_set(j) && adjacency_matrix[i][j] < min) {
                    min = adjacency_matrix[i][j];
                    a = i;
                    b = j;
                }
            }
        }
 
        union_set(a, b);
        num_of_edges++;
        min_cost_of_path += min;
        cout<<"Edge "<<num_of_edges<<": ("<<a<<","<<b<<")-->Cost: "<<min<<endl;
    }
    cout<<"\nMINIMUM COST USING KRUSKAL'S ALGORITHM: "<<min_cost_of_path<<endl;
}

int main() {

	int option, x, y, cost, src_node, vertices, random_node;
	Graph graph;
	do {
		cout<<"-----------------------------------------------|\n";
		cout<<"=>  MAIN MENU                                  |\n";
		cout<<"-----------------------------------------------|\n";
		cout<<"1.  CREATE A GRAPH                             |\n";
		cout<<"2.  SET AN EDGE                                |\n";
		cout<<"3.  REMOVE AN EDGE                             |\n";
		cout<<"4.  BREADTH-FIRST SEARCH (BFS)                 |\n";
		cout<<"5.  DEPTH-FIRST SEARCH (DFS)                   |\n";
		cout<<"6.  DIJKSTRA'S SHORTEST PATH                   |\n";
		cout<<"7.  PRIMS' MINIMUM SPANNING TREE (MST)         |\n";
		cout<<"8.  KRUSKAL'S MINIMUM SPANNING TREE (MST)      |\n";
		cout<<"9.  DELETE/REMOVE GRAPH                        |\n";
		cout<<"10. DISPLAY GRAPH                              |\n";
		cout<<"0.  EXIT                                       |\n";
		cout<<"-----------------------------------------------|\n";

		cout<<"SELECT AN OPTION FROM THE ABOVE MENU - [0-10]: \n";
		cin>>option;

		if(option < 0 || option > 10) {
			cout<<"INVALID OPTION IS SELECTED...! PLEASE SELECT A VALID OPTION FROM THE ABOVE MENU\n";
		} else {
			switch(option) {
				case 1:
					if(graph.num_of_vertices == 0) {
						cout<<"ENTER NUMBER OF VERTICES IN YOUR GRAPH: \n";
						cin>>vertices;
						while(true) {
							if(vertices > 0) break;
							else {
								cout<<"NUMBER OF VERTICES CAN'T BE NEGATIVE!\nPLEASE ENTER A VALID NUMBER!";
								cout<<"\nENTER NUMBER OF VERTICES IN YOUR GRAPH: \n";
								cin>>vertices;
							}
						}
						graph.Create_Graph(vertices);
						cout<<"GRAPH IS INITIALIZED SUCCESSFULLY!"<<endl;
					} else {
						cout<<"GRAPH IS ALREADY INITIALIZED!"<<endl;
					}
					break;
				case 2:
					cout<<"ENTER THE SOURCE NODE: \n";
					cin>>x;
					cout<<"ENTER THE DESTINATION NODE: \n";
					cin>>y;
					cout<<"ENTER THE COST OF THE EDGE: \n";
					cin>>cost;

					while(true) {
						if(x < 0 || x > (vertices-1)) {
							cout<<"PLEASE ENTER A VALID SOURCE NODE!\n";
							cout<<"ENTER THE SOURCE NODE: \n";
							cin>>x;
						} else if(y < 0 || y > (vertices-1)) {
							cout<<"PLEASE ENTER A VALID DESTINATION NODE!\n";
							cout<<"ENTER THE DESTINATION NODE: \n";
							cin>>x;
						} else if(cost < 0) {
							cout<<"COST CAN'T BE NEGATIVE! PLEASE ENTER A VALID VALUE FOR COST...\n";
							cout<<"ENTER THE COST OF THE EDGE: \n";
							cin>>cost;
						}
						else break;
					}
					graph.set_edge(x,y,cost);
					break;
				case 3:
					cout<<"ENTER THE SOURCE NODE: \n";
					cin>>x;
					cout<<"ENTER THE DESTINATION NODE: \n";
					cin>>y;

					while(true) {
						if(x < 0 || x > (vertices-1)) {
							cout<<"PLEASE ENTER A VALID SOURCE NODE!\n";
							cout<<"ENTER TEH SOURCE NODE: \n";
							cin>>x;
						} else if(y < 0 || y > (vertices-1)) {
							cout<<"PLEASE ENTER A VALID DESTINATION NODE!\n";
							cout<<"ENTER THE DESTINATION NODE: \n";
							cin>>x;
						} 
						else break;
					}
					graph.remove_edge(x,y);
					break;
				case 4:
					cout<<"ENTER THE STARTING/SOURCE NODE: \n";
					cin>>src_node;

					if(src_node < 0 || src_node > (vertices-1)) {
						cout<<"THE SOURCE NODE IS NOT IN THE GRAPH!\n";
					} else {
						graph.BFS(src_node);
					}
					graph.reset();
					break;
				case 5:
					cout<<"ENTER THE STARTING/SOURCE NODE: \n";
					cin>>src_node;

					if(src_node < 0 || src_node > (vertices-1)) {
						cout<<"THE SOURCE NODE IS NOT IN THE GRAPH!\n";
					} else {
						cout<<"DFS TRAVERSAL: ";
						// for(int i = 0; i < graph.num_of_vertices; i++) {
						// 	if(graph.visited_nodes[i] == 0) {
						// 		graph.DFS(i);
						// 	}
						// }
						graph.DFS(src_node);
						graph.reset();
					}
					break;
				case 6:
					cout<<"ENTER THE STARTING/SOURCE NODE: \n";
					cin>>src_node;

					if(src_node < 0 || src_node > (vertices-1)) {
						cout<<"THE SOURCE NODE IS NOT IN THE GRAPH!\n";
					} else {
						graph.dijkstra_shortest_path(src_node);
						graph.reset();
					}
					break;
				case 7:
					cout<<"SELECT A RANDOM NODE: \n";
					cin>>random_node;

					if(random_node < 0 || random_node > (vertices-1)) {
						cout<<"THE SOURCE NODE IS NOT IN THE GRAPH!\n";
					} else {
						graph.prims_MST(random_node);
						graph.reset();
					}
					break;
				case 8:
					graph.kruskal_MST();
					graph.reset();
					break;
				case 9:
					graph.~Graph();
					break;
				case 10:
					graph.display_graph();
					break;
				default:
					cout<<"THANK YOU FOR VISTING US... SEE YOU SOON... :)\n";
					break;
			}
		}

	} while(option != 0);

	return 0;
}