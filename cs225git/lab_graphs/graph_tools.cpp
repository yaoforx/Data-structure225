/**
 * @file graph_tools.cpp
 * This is where you will implement several functions that operate on graphs.
 * Be sure to thoroughly read the comments above each function, as they give
 *  hints and instructions on how to solve the problems.
 */

#include "graph_tools.h"
#include <iostream>
/**
 * Finds the minimum edge weight in the Graph graph.
 * THIS FUNCTION IS GRADED.
 *
 * @param graph - the graph to search
 * @return the minimum weighted edge
 *
 * @todo Label the minimum edge as "MIN". It will appear blue when
 *  graph.savePNG() is called in minweight_test.
 *
 * @note You must do a traversal.
 * @note You may use the STL stack and queue.
 * @note You may assume the graph is connected.
 *
 * @hint Initially label vertices and edges as unvisited.
 */
int GraphTools::findMinWeight(Graph& graph)
{
    //TODO: YOUR CODE HERE
    Unexplored(graph);

    Vertex s = graph.getStartingVertex();
    int minWeight = INT_MAX;
    Vertex minV;
    Vertex minW;

    //BFS
    queue<Vertex> myQueue;
    graph.setVertexLabel(s, "V");
    myQueue.push(s);
    while(!myQueue.empty()) {

        Vertex top = myQueue.front();
        myQueue.pop();
        vector<Vertex> aj = graph.getAdjacent(top);
        for(size_t i = 0; i < aj.size(); i++) {
            Vertex a = aj[i];
            if(graph.getVertexLabel(a) == "U" && graph.getEdgeLabel(top,a) == "U") {
                graph.setEdgeLabel(top,a,"D");
                graph.setVertexLabel(a,"V");
                myQueue.push(a);
            }
            if(graph.getEdgeWeight(top,a) < minWeight) {
                minWeight = graph.getEdgeWeight(top,a);
                minV = top;
                minW = a;
            }
            else if(graph.getEdgeLabel(top,a) == "U") {
                graph.setEdgeLabel(top, a, "C");
            }
        }

    }
    graph.setEdgeLabel(minV,minW,"MIN");

    return minWeight;
}

/**
 * Returns the shortest distance (in edges) between the Vertices
 *  start and end.
 * THIS FUNCTION IS GRADED.
 *
 * @param graph - the graph to search
 * @param start - the vertex to start the search from
 * @param end - the vertex to find a path to
 * @return the minimum number of edges between start and end
 *
 * @todo Label each edge "MINPATH" if it is part of the minimum path
 *
 * @note Remember this is the shortest path in terms of edges,
 *  not edge weights.
 * @note Again, you may use the STL stack and queue.
 * @note You may also use the STL's unordered_map, but it is possible
 *  to solve this problem without it.
 *
 * @hint In order to draw (and correctly count) the edges between two
 *  vertices, you'll have to remember each vertex's parent somehow.
 */
int GraphTools::findShortestPath(Graph& graph, Vertex start, Vertex end)
{
    //TODO: YOUR CODE HERE
    Unexplored(graph);
    unordered_map<Vertex,Vertex> table;
    queue<Vertex> myQueue;
    graph.setVertexLabel(start, "V");
    myQueue.push(start);
    while(!myQueue.empty()) {
        Vertex top = myQueue.front();
        myQueue.pop();
        vector<Vertex> aj = graph.getAdjacent(top);
        for(size_t i = 0; i < aj.size(); i++) {
            Vertex a = aj[i];
            if(graph.getVertexLabel(a) == "U" && graph.getEdgeLabel(top,a) == "U") {
                table[a] = top;
                graph.setEdgeLabel(top,a,"D");
                graph.setVertexLabel(a,"V");
                myQueue.push(a);
            }
            else if(graph.getEdgeLabel(top,a) == "U") {
                graph.setEdgeLabel(top, a, "C");
            }
        }

    }
    int count = 0;
    while(start != end) {
        graph.setEdgeLabel(end,table[end],"MINPATH");
        end = table[end];
        count++;
    }


    return count;
}

/**
 * Finds a minimal spanning tree on a graph.
 * THIS FUNCTION IS GRADED.
 *
 * @param graph - the graph to find the MST of
 *
 * @todo Label the edges of a minimal spanning tree as "MST"
 *  in the graph. They will appear blue when graph.savePNG() is called.
 *
 * @note Use your disjoint sets class from MP 7.1 to help you with
 *  Kruskal's algorithm. Copy the files into the dsets.h and dsets.cpp .
 * @note You may call std::sort instead of creating a priority queue.
 */
void GraphTools::Unexplored(Graph &graph) {
    Vertex s = graph.getStartingVertex();
    graph.setVertexLabel(s, "U");
    queue<Vertex> myQueue;
    myQueue.push(s);
    while(!myQueue.empty()) {
        Vertex top = myQueue.front();
        myQueue.pop();
        vector<Vertex> aj = graph.getAdjacent(top);
        for(size_t i = 0; i < aj.size(); i++) {
            Vertex node = aj[i];
            if(graph.getVertexLabel(node) != "U") {
                graph.setVertexLabel(node, "U");
                graph.setEdgeLabel(top, node, "U");
                myQueue.push(node);
            }
            else if(graph.getEdgeLabel(top,node) != "U")
                graph.setEdgeLabel(top,node,"U");
        }
    }
}
bool GraphTools::comp(Edge a , Edge b) { return a.getWeight() < b.getWeight();}

void GraphTools::findMST(Graph& graph)
{
    //TODO: YOUR CODE HERE
    vector<Edge> Edges = graph.getEdges();

    sort(Edges.begin(),Edges.end(), comp);

    disjointSets verSet;
    vector<Vertex> verList = graph.getVertices();

    verSet.insert(verList);
    for(size_t i = 0; i < Edges.size(); i++) {
        Vertex u = Edges[i].source;
        Vertex v = Edges[i].dest;
        if(verSet.find(u) != verSet.find(v)) {
            verSet.setUnion(u,v);

            graph.setEdgeLabel(u,v,"MST");
        }
    }



}


