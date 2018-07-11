 //Your code here!
#include "dsets.h"
#include <iostream>
void disjointSets::insert(vector<Vertex> v) {

    for(auto item : v) {
        parent[item] = item;
        //sizes.push_back(1);
    }


}
void disjointSets::setUnion(string a, string b) {

    string pa = find(a);
    string pb = find(b);

    parent[pb] = pa;


}
string disjointSets::find(string elem) {

    while(elem != parent[elem]) {
        parent[elem] = parent[parent[elem]];
        elem = parent[elem];
    }
    return elem;
}
