#include <iostream>
#include <cmath>
#include <cstdlib>
#include <queue>
#include <map>
#include <set>
#include <vector>


using namespace std;

class Node {
public:
    int id;
    double x;
    double y;
    Node():id(0), x(0.0), y(0.0){}
    Node(int i, double a, double b):id(i), x(a), y(b){}
  // Calculate the distance between two node
    double distanceFrom(const Node &rhs)const {
        return sqrt(pow(x - rhs.x, 2) + pow(y - rhs.y, 2));
    };
  // Compare node with its id
    bool operator!=(const Node &rhs)const {
        return id != rhs.id;
    };
    bool operator<(const Node &rhs)const {
        return id < rhs.id;
    };
    bool operator==(const Node &rhs)const {
        return id == rhs.id;
    };
  ~Node(){};
};

class Edge {
public:
    Node vertex;
    double weight;
    Edge(Node v, double w) {
        vertex = v;
        weight = w;
    }
    /*
    Edge(Node v){
        vertex = v;
        weight = 0;
    }
     */
    bool operator<(const Edge &rhs)const {
        return vertex.id < rhs.vertex.id;
    }
};

class Graph {
public:
  // adjacent list
    map<int, set<Edge> > adj;

  // check if graph contains node v
    bool contains(const Node &v);

  // check if two node has edge between them
    bool checkConnect(const Node &u, const Node &v);

  // create graph with node and edge information
    void createGraph(vector<Node> nodeList, vector<pair<int, int> > nodeIndex);

  // create graph with node, edge and obstacle information
    void graphWithObs(vector<Node> nodeList, vector<pair<int, int> > nodeIndex, vector<vector<pair<int, int> > > obsList);

  // print the graph, for step1
    void printGraph(vector<Node> nodeList);

  // add vertex in the graph
    void addVertex(const Node &v);

  // add edge in the graph
    void addEdge(const Node &u, const Node &v);

    //void removeVertex(const Node &v);

    //void removeEdge(const Node &u, const Node &v);

  // store all the node in the graph
    vector<int> getVertices();

  // Dijkstra algorithm, inside print the path and cost
    void Dijkstra(int start, int goal);

  // A* search algorithm, inside print the path and cost
    void AStar(vector<Node> nodeList, int start, int goal);
  // check if node on the segment
    bool onSegment(Node p, Node q, Node r);

  // calculate orientation
    int orientation(Node p, Node q, Node r);

  // check if two line segment intersect with each other
    bool doIntersect(Node p1, Node q1, Node p2, Node q2);
};
