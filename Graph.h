#ifndef GRAPH_H
#define GRAPH_H
#include<vector>
#include<iostream>

struct vertex;

/*This is the struct for the adjacent vertices for each
 vertex in the graph. */
struct adjVertex{
    vertex *v;
    float weight;
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
        void addEdge(std::string v1, std::string v2, float weight); //Rami
        void addVertex(std::string name); //Richard
        void displayEdges(std::string startingSta); //Rami  //main
        float pathLength(std::string startingSta, std::string endingSta); //Richard
        void showAllSta(); //Rami  //main
        std::vector<vertex> TSPNN(std::string startingSta, float *dis); //Richard  //main ompare with TSP20PT
        void nearestFive(std::string sta); //Richard //main
        //void shortestPath(std::string Sta1, std::string Sta2, std::string Sta3, std::string Sta4, std::string Sta5);
        void bestSS(std::string startingSta); //Rami //main
        //void TSPCW(std::string hub);  //Clarke-Wright rami
        std::vector<vertex> TSP2Opt(std::string startingSta, float *dis); //Richard
        void printR(std::vector<vertex> path); //Rami
        float totalTourLength(std::vector<vertex> path);
	bool isStation(std::string station);


    protected:
    private:
        std::vector<vertex> stations;
        vertex * findVertex(std::string name);
};

#endif // GRAPH_H
