#ifndef GRAPH_H
#define GRAPH_H
#include<vector>
#include<iostream>

struct vertex;

/*This is the struct for the adjacent vertices for each
 vertex in the graph. */
struct adjVertex{
    vertex *v;
    int weight;
};
/*this is the struct for each vertex in the graph.*/
struct vertex{
    vertex *parent;
    std::string name;
    bool visited;
    std::vector<adjVertex> adj;
};
struct queueVertex{
    int distance;
    std::vector<vertex *> path;
};
class Graph
{
    public:
        Graph();
        ~Graph();
        void addEdge(std::string v1, std::string v2, int weight); //Rami
        void addVertex(std::string name); //Richard
        void displayEdges(); //Rami
        int pathLength(std::string startingSta, std::string endingSta); //Richard
        void showAllSta(); //Rami
        void TSPNN(std::string startingSta); //Richard
        void nearestFive(std::string sta); //Richard
        //void shortestPath(std::string Sta1, std::string Sta2, std::string Sta3, std::string Sta4, std::string Sta5);
        void bestSS(std::string startingSta); //Rami
        void TSPCW(std::string hub);  //Clarke-Wright rami
        void TSP2Opt(std::string startingSta); //Richard
        void printR(queueVertex route); //Rami



    protected:
    private:
        std::vector<vertex> stations;
        vertex * findVertex(std::string name);
};

#endif // GRAPH_H
