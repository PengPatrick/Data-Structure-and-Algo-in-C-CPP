#include "pathPlanning.h"


bool Graph::contains(const Node &v) {
    return adj.find(v.id) != adj.end();
}


bool Graph::checkConnect(const Node &u, const Node &v) {
  // if graph has both u & v and they are not the same, check if there is edge between them ( whether it is in adjacent list)
    if (contains(u) && contains(v) && u != v) {
        set<Edge>::iterator iter;
        for (iter = adj[u.id].begin(); iter != adj[u.id].end(); iter++) {
            if (iter->vertex == v) {
                return true;
            }
        }
    }
    return false;
}


void Graph::createGraph(vector<Node> nodeList, vector<pair<int, int> > nodeIndex){
  // add vertices to the graph
    vector<Node>::iterator it;
    for(it = nodeList.begin(); it != nodeList.end(); it++){
        addVertex(*it);
    }
    // add edges to the graph
    vector<pair<int, int> >::iterator iter;
    for(iter = nodeIndex.begin(); iter != nodeIndex.end(); iter++){
        addEdge(nodeList.at(iter->first), nodeList.at(iter->second));
    }
}


void Graph::graphWithObs(vector<Node> nodeList, vector<pair<int, int> > nodeIndex, vector<vector<pair<int, int> > > obsList){
    vector<Node>::iterator it;
    // add vertices to the graph
    for(it = nodeList.begin(); it != nodeList.end(); it++){
        addVertex(*it);
    }
    // check each edge if it is intersect with obstacle edge, if not intersect, then add to graph
    vector<pair<int, int> >::iterator iter;
    for(iter = nodeIndex.begin(); iter != nodeIndex.end(); iter++){
      // mark whether edge intersect with any obstacle's edge
        bool isIntersect = false;
        vector<vector<pair<int, int> > >::iterator iter3;
        for(iter3 = obsList.begin(); iter3 != obsList.end(); iter3++) {
            vector<pair<int, int> >::iterator iter4;
            for(iter4 = iter3->begin(); iter4 != iter3->end(); iter4++) {
	      // check if obstacle's id is in the range of node in graph
	      if(iter4->first + 1 > (int)getVertices().size() || iter4->second + 1 > (int)getVertices().size()){
		cerr << "Obstacle Node Out of Range!" << endl;
		exit(EXIT_FAILURE);
	      }
	      // whether intersect
                if (doIntersect(nodeList.at(iter->first), nodeList.at(iter->second), nodeList.at(iter4->first), nodeList.at(iter4->second))){
                    isIntersect = true;
                    break;
                }
            }
            if(isIntersect) break;
        }
	// add the edge to the graph
        if(!isIntersect){
            addEdge(nodeList.at(iter->first), nodeList.at(iter->second));
        }
    }
}


void Graph::printGraph(vector<Node> nodeList){
  // print the graph following the rule in the README
  // node location in order of node's id
  // adjacent list
    vector<Node>::iterator iter2;
    for(iter2 = nodeList.begin(); iter2 != nodeList.end(); iter2++){
        cout << "(" << iter2->x<< "," << iter2->y << ")" << " ";
    }
    cout << endl;

    map<int, set<Edge> >::iterator ite;
    for(ite = adj.begin(); ite !=adj.end(); ite++){
        cout << ite->first << ": ";
        set<Edge>::iterator iter1;
        for(iter1 = ite->second.begin(); iter1 != ite->second.end(); iter1++){
            cout << iter1->vertex.id << "," << iter1->weight << " ";
        }
        cout << endl;
    }
}


void Graph::addVertex(const Node &v) {
  // add the vertex to the graph
    if (!contains(v)) {
        set<Edge> edge_list;
        adj[v.id] = edge_list;
    }
}


void Graph::addEdge(const Node &u, const Node &v) {
  // add the edge to the graph
    if (!checkConnect(u, v)) {
        adj[u.id].insert(Edge(v, v.distanceFrom(u)));
        adj[v.id].insert(Edge(u, u.distanceFrom(v)));
    }
}

/*
void Graph::removeVertex(const Node &v) {
    if (contains(v)) {
        map<int, set<Edge> >::iterator iter;
        for(iter = adj.begin(); iter != adj.end(); iter++){
            set<Edge>::iterator it;
            for(it = iter->second.begin(); it != iter->second.end();){
                // Here we need to be very careful, as if we use erase(it), then the iterator will be deleted
                // and the program will crash. We need to make iterator first point to the following position,
                // then use the erase operation
                if(it->vertex.id == v.id){
                    iter->second.erase(it++);
                }else{
                    it++;
                }
            }
        }
        adj.erase(v.id);
    }
}
*/

/*
void Graph::removeEdge(const Node &u, const Node &v){
    if (u == v || !contains(u) || !contains(v)) return;

    if (adj[u.id].find(Edge(v)) != adj[u.id].end()) {
        adj[u.id].erase(Edge(v));
        adj[v.id].erase(Edge(u));
    }
}
*/

vector<int> Graph::getVertices() {
  // store all the node's id in one vector
    vector<int> vertices;
    map<int, set<Edge> >::iterator iter;
    for (iter = adj.begin(); iter != adj.end(); iter++){
        vertices.push_back(iter->first);
    }
    return vertices;
}

void Graph::Dijkstra(int start, int goal){
    vector<int> allNode = getVertices();
    // guarantee that start and end node is in the node's id range
    if(start + 1 > (int) allNode.size() || goal + 1 > (int) allNode.size()){
      cerr << "The node is out of range!" << endl;
      exit(EXIT_FAILURE);
    }
    // path to record the shortest path
    vector<int> path;
    // pre to record from which node update the shortest path, say it is predecessor node
    vector<int> pre(allNode.size());
    pre[start] = start;
    // vector to record the min distance from start point to current
    vector<double> dis(allNode.size());
    fill(dis.begin(), dis.end(), INFINITY);
    dis[start] = 0;
    // vector to record whether it is visited or not
    vector<int> visited(allNode.size());
    fill(visited.begin(), visited.end(), 0);

    // use priority-queue to get the shortest cost and predecessor node, sort with distance and the first element is min value
    priority_queue<pair<double, int>, vector<pair<double, int> >, greater<pair<double, int> > > q;
    q.push(make_pair(0, start));
    while(!q.empty()){
        // sort with dis, so the top should have the min cost
        pair<double, int> n = q.top();
        q.pop();
        int v = n.second;
	// if already current min
        if(dis[v] < n.first){
            continue;
        }
	// if have already visited, then jump to visited coming node in the priority queue
        if(visited[v]){
            continue;
        }
        visited[v] = 1;
	// check all the near nodes to see if any update
        for(size_t i = 0; i < allNode.size(); i++){
            set<Edge>::iterator it;
            for(it = adj[v].begin(); it != adj[v].end(); it++){
	      // find the current node's id
                if(it->vertex.id == (int) i){
		  // if hasn't been visited and has smaller cost, then update the distance and make the current node as predecessor node 
                    if(!visited[i] && dis[i] > dis[v] + it->weight){
                        dis[i] = dis[v] + it->weight;
                        pre[i] = v;
                        q.push(make_pair(dis[i], i));
                    }
                }
            }
        }
    }

    /******  queue implementation   *******/ 
    //queue<int> q;
    //q.push(start);
    //while(!q.empty()){
    //    int n = q.front();
    //    q.pop();
    //    visited[start] = 1;

    //    set<Edge>::iterator it;
    //    for(it = adj[n].begin(); it != adj[n].end(); it++){
    //        if(visited[it->vertex.id] == 0 && dis[it->vertex.id] > dis[n] + it->weight){
    //            dis[it->vertex.id] = dis[n] + it->weight;
    //            pre[it->vertex.id] = n;
    //            q.push(it->vertex.id);
    //        }
    //    }
    //}

    // parse the path and print it
    int id = goal;
    while(id != start){
        path.insert(path.begin(), id);
        id = pre[id];
    }
    path.insert(path.begin(), id);
    vector<int>::iterator iter;
    for(iter = path.begin(); iter != path.end(); iter++){
        cout << *iter << " ";
    }
    // print the shortest path
    cout << ": " << dis[goal] << endl;
}


void Graph::AStar(vector<Node> nodeList, int start, int goal) {
    vector<int> allNode = getVertices();
    // check if start and goal node is within range
    if(start + 1 > (int) allNode.size() || goal + 1 > (int) allNode.size()){
      cerr << "The node is out of range!" << endl;
      exit(EXIT_FAILURE);
    }
    // vector to record path
    vector<int> path;
    // vector to record each node's predecessor
    vector<int> pre(allNode.size());
    pre[start] = start;
    // vector to record the min distance from start point to current
    vector<double> dis(allNode.size());
    fill(dis.begin(), dis.end(), INFINITY);
    // vector to record the f, f = g + h, guiding the search direction
    vector<double> his(allNode.size());
    fill(his.begin(), his.end(), INFINITY);
    // initialize
    dis[start] = 0.0;
    his[start] = 0.0;
    // vector to record whether it is visited or not
    vector<int> visited(allNode.size());
    fill(visited.begin(), visited.end(), 0);

    priority_queue<pair<double, int>, vector<pair<double, int> >, greater<pair<double, int> > > q;
    q.push(make_pair(0, start));
    while(!q.empty()){
      // sort with history, so guiding the search
        pair<double, int> n = q.top();
        q.pop();
        int v = n.second;
        if(his[v] < n.first){
            continue;
        }
	// if visited, jump to coming node
        if(visited[v]){
            continue;
        }
	// if the goal is found, exit
        if(visited[goal]){
            break;
        }
        visited[v] = 1;
        for(size_t i = 0; i < allNode.size(); i++){
            set<Edge>::iterator it;
            for(it = adj[v].begin(); it != adj[v].end(); it++){
                if(it->vertex.id == (int) i){
                    if(!visited[i] && his[i] > his[v] + it->weight + nodeList[i].distanceFrom(nodeList[goal])){
		      // update the history and true cost
                        his[i] = his[v] + it->weight + nodeList[i].distanceFrom(nodeList[goal]);
                        dis[i] = dis[v] + it->weight;
                        pre[i] = v;
                        q.push(make_pair(his[i], i));
                    }
                }
            }
        }
    }

    int id = goal;
    while(id != start){
        path.insert(path.begin(), id);
        id = pre[id];
    }
    path.insert(path.begin(), id);
    vector<int>::iterator iter;
    for(iter = path.begin(); iter != path.end(); iter++){
        cout << *iter << " ";
    }
    cout << ": " << dis[goal] << endl;
}


// It is provided material
// If I were to implement by myself, I would just make equation of two line segment to see if there is answer and whether the answer is within the range of either line segment

bool Graph::onSegment(Node p, Node q, Node r)
{
    if (q.x <= max(p.x, r.x) && q.x >= min(p.x, r.x) &&
        q.y <= max(p.y, r.y) && q.y >= min(p.y, r.y))
        return true;

    return false;
}

// To find orientation of ordered triplet (p, q, r).
// The function returns following values
// 0 --> p, q and r are collinear
// 1 --> Clockwise
// 2 --> Counterclockwise

int Graph::orientation(Node p, Node q, Node r)
{
    // See https://www.geeksforgeeks.org/orientation-3-ordered-points/
    // for details of below formula.
    double val = (q.y - p.y) * (r.x - q.x) -
                 (q.x - p.x) * (r.y - q.y);

    if (val == 0) return 0;  // collinear

    return (val > 0)? 1: 2; // clock or counterclock wise
}

// The main function that returns true if line segment 'p1q1'
// and 'p2q2' intersect.
bool Graph::doIntersect(Node p1, Node q1, Node p2, Node q2)
{
    // Find the four orientations needed for general and
    // special cases
    int o1 = orientation(p1, q1, p2);
    int o2 = orientation(p1, q1, q2);
    int o3 = orientation(p2, q2, p1);
    int o4 = orientation(p2, q2, q1);

    // General case
    if (o1 != o2 && o3 != o4)
        return true;

    // Special Cases
    // p1, q1 and p2 are collinear and p2 lies on segment p1q1
    if (o1 == 0 && onSegment(p1, p2, q1)) return true;

    // p1, q1 and q2 are collinear and q2 lies on segment p1q1
    if (o2 == 0 && onSegment(p1, q2, q1)) return true;

    // p2, q2 and p1 are collinear and p1 lies on segment p2q2
    if (o3 == 0 && onSegment(p2, p1, q2)) return true;

    // p2, q2 and q1 are collinear and q1 lies on segment p2q2
    if (o4 == 0 && onSegment(p2, q1, q2)) return true;

    return false; // Doesn't fall in any of the above cases
}
