// Your code here!
#include <unordered_map>
#include <vector>
#include <string>
#include "graph.h"
using namespace std;

class disjointSets {
public:
    void insert(vector<Vertex> v);
    string find(string elem);
    void setUnion(string elem1, string elem2);


private:
    unordered_map<string,string> parent;
    //vector<int> sizes;

};

