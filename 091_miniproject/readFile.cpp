#include "readFile.h"
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

int locate(char* filename){
  // Use count to locate the specific line
    int count = 0;
    string str;
    ifstream file;
    file.open(filename);
    if(file.fail()){
        cerr << "fail to open file" << endl;
        exit(EXIT_FAILURE);
    }
    // Readfile to locate
    while(!file.eof()){
        count++;
        getline(file, str);
        if(str == "$edges"){
            file.close();
            return count;
        }
    }
    file.close();
    cerr << "Error in the input file" << endl;
    exit(EXIT_FAILURE);
}


pair<vector<Node>, vector<pair<int, int> > > readGrid(char *filename){

    vector<Node> list;
    vector<pair<int, int> > index;
    int count = 0;
    int locateEdge = locate(filename);
    string str;
    ifstream file;
    file.open(filename);
    if(file.fail()){
        cerr << "fail to open file" << endl;
        exit(EXIT_FAILURE);
    }
    while(!file.eof()){
        count++;
        getline(file, str);
	// Guarantee the first line to be "$nodes"
        if(count < locateEdge && str.size() > 0) {
            if (count == 1) {
                if (str != "$nodes") {
                    cerr << "Error in the input file!" << endl;
                    exit(EXIT_FAILURE);
                }
                continue;
            }
	    // Guarantee the node is continuous and no duplicate
	    if(parseNode(str).id != (int)list.size()){
	      cerr << "Wrong node information is given!" << endl;
	      exit(EXIT_FAILURE);
	    }
	    // parse the string and store the nodelist
            list.push_back(parseNode(str));
        }
        if(count > locateEdge && str.size() > 0){
	  // parse the string and store the edge index
            index.push_back(parseEdge(str));
        }
    }
    file.close();
    return make_pair(list, index);
}



Node parseNode(string str){
    vector<string> res;
    string result;
    stringstream input(str);
    while(input >> result){
        res.push_back(result);
    }
    // Node should have id, x, y
    if(res.size() != 3){
      cerr << "Invalid node information!" << endl;
      exit(EXIT_FAILURE);
    }
    // id should be non-negative integer, and x, y should be number
    if(!isPosInt(res[0]) || !isNum(res[1]) || !isNum(res[2])){
      cerr << "Invalid node information!" << endl;
      exit(EXIT_FAILURE);
    }

    return Node(strtol(res[0].c_str(), NULL, 0), strtod(res[1].c_str(), NULL), strtod(res[2].c_str(), NULL));
}

pair<int, int> parseEdge(string str){
    vector<string> res;
    string result;
    stringstream input(str);
    while(input >> result){
        res.push_back(result);
    }
    // Edge should be id, id
    if(res.size() != 2){
      cerr << "Invalid edge information" << endl;
      exit(EXIT_FAILURE);
    }
    // Node's id should be non-negative integer
    if(!isPosInt(res[0]) || !isPosInt(res[1])){
      cerr << "Invalid edge information!" << endl;
      exit(EXIT_FAILURE);
    }

    return pair<int, int>(strtol(res[0].c_str(), NULL, 0), strtol(res[1].c_str(), NULL, 0));
}


vector<vector<pair<int, int> > > readObs(char *filename){
    vector<vector<pair<int, int> > > res;
    int count = 0;
    string str;
    ifstream file;
    file.open(filename);
    if(file.fail()){
        cerr << "fail to open file" << endl;
        exit(EXIT_FAILURE);
    }

    while(!file.eof()){
        count++;
        getline(file, str);
	// only deal with non-empty line
        if(str.size() > 0) {
	  // Guarantee the first line should be "$obstacles"
            if (count == 1) {
                if (str != "$obstacles") {
                    cerr << "Error in the input file" << endl;
                    exit(EXIT_FAILURE);
                }
                continue;
            }
            res.push_back(parseObs(str));
        }
    }
    file.close();
    return res;
}

vector<pair<int, int> > parseObs(string str){
    vector<string> res;
    vector<pair<int, int> > ans;
    string result;
    stringstream input(str);
    while(input >> result){
        res.push_back(result);
    }
    // obstacle exist, then it should be more than one node
    if(res.size() < 2){
        cerr << "Wrong format of obstacles" << endl;
        exit(EXIT_FAILURE);
    }
    // node id should be non-negative integer
    for(int i = 0; i < (int) res.size(); i++){
      if(!isPosInt(res[i])){
	cerr << "Invalid obstacle information!" << endl;
	exit(EXIT_FAILURE);
      }
    }
    // store as pair of node
    ans.push_back(make_pair(strtol(res[res.size() - 1].c_str(), NULL, 0), strtol(res[0].c_str(), NULL, 0)));
    if(res.size() > 2) {
        for (int i = 1; i < (int) res.size(); i++) {
            ans.push_back(make_pair(strtol(res[i - 1].c_str(), NULL, 0), strtol(res[i].c_str(), NULL, 0)));
        }
    }
    return ans;
}

bool isNum(string str){
  stringstream sin(str);
  double d;
  char c;
  // check if cannot be double
  if(!(sin >> d)){
    return false;
  }
  // check if character
  if(sin >> c){
    return false;
  }
  return true;
}

bool isPosInt(string str){
  return isNum(str) && str.find(".") == str.npos && str.find("-") == str.npos;
}

