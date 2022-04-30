#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <cstdio>

using namespace std;

void splitString(string& s, vector<string>& v, string& c)
{
  string::size_type pos1, pos2;
  pos2 = s.find(c);
  pos1 = 0;
  while(string::npos != pos2)
  {
    v.push_back(s.substr(pos1, pos2-pos1));
 
    pos1 = pos2 + c.size();
    pos2 = s.find(c, pos1);
  }
  if(pos1 != s.length())
    v.push_back(s.substr(pos1));
}

map<string, vector<string> > wordDic(char *filename){
  map<string, vector<string> > dic;
  ifstream ifs(filename);
  if(!ifs.is_open()){
    perror("Fail to open file!");
    exit(EXIT_FAILURE);
  }
  string line;
  while(getline(ifs, line)){
    vector<string> cur;
    string c = ":";
    splitString(line, cur, c);
    if(cur.size() != 2){
      perror("Wrong words file!");
      exit(EXIT_FAILURE);
    }
    dic[cur[0]].push_back(cur[1]);
  }
  return dic;
}

void lineReplace(string &line,map<string, vector<string> > &dic){
  string l;//random name
  string::size_type pos1, pos2;
  string temp;
  while(line.find("_") != line.npos){
    pos1 = line.find("_");
    pos2 = line.find("_",pos1+1);
    //input error like _time
    if(pos2 == line.npos){
      perror("Input Error:lack second _");
   	  exit(EXIT_FAILURE);
    }
    temp = line.substr(pos1+1,pos2-pos1-1);
    //std::cout<<"temp = "<<temp<<std::endl;//debug test
    if(atoi(temp.c_str()) == 0){
      //Story file with nonexistent category
      if(dic.count(temp) == 0){
        perror("Story file with nonexistent category");
   	    exit(EXIT_FAILURE);
      }
      int r = rand() % dic[temp].size();//random number
      //std::cout<<"random number= "<<r<<std::endl;//debug test
      l = (dic[temp])[r];
    }
    else{
      int n = dic["used"].size()-atoi(temp.c_str());
      if(n < 0){
        perror("Number refers past beginning of story");
   	    exit(EXIT_FAILURE);
      }
      l = (dic["used"])[n]; 
    }
    line = line.replace(pos1,temp.length()+2,l);
    dic["used"].push_back(l);//keep track of used words
  }
}
vector<string> makeStory(char* filename,map<string, vector<string> > dic){
  vector<string> S;
  ifstream ifs(filename);
  if(!ifs.is_open()){
    perror("Could not open Story");
   	exit(EXIT_FAILURE);
  }
  string line;
  while(getline(ifs,line)){
    lineReplace(line,dic);
    cout << line << endl;
    S.push_back(line);
  }
  return S;
}
int main(int argc, char ** argv){
  if(argc != 4) {
    fprintf(stderr, "Input Error:3 command line arguments\n");
    return EXIT_FAILURE;
  }
  int r = atoi(argv[3]);//random seed
  if(r <= 0) {
    fprintf(stderr, "Input Error:random seed must be 1 or greater\n");
    return EXIT_FAILURE;
  }
  srand(r);//set the random seed
  //(1) read and store the categories and words in a map
  map<string, vector<string> > dic;
  dic = wordDic(argv[2]);
  //(2) read the story template, parsing each blank and selecting an appropriate word.
  vector<string> S;//Story
  S = makeStory(argv[1],dic);
  return EXIT_SUCCESS;
}
