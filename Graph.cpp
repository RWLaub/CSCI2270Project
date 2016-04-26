#include "Graph.h"

using namespace std;

Graph::Graph()
{
    //ctor
}

Graph::~Graph()
{
    //dtor
}

void Graph::addEdge(std::string v1, std::string v2, float weight)
{
    cout<<"Adding edge from " << v1 << " to " << v2 << " of weight " << weight << endl;

    for (int i = 0; i < stations.size(); i++){
        if(stations[i].name == v1){
            for(int j = 0; j < stations.size(); j++){
                if(stations[j].name == v2 && i != j){
                    adjVertex av;
                    av.v = &stations[j];
                    av.weight =weight;
                    stations[i].adj.push_back(av);
                }
            }
        }
    }
}

void Graph::addVertex(std::string name)
{
    bool found = false;
    for(int i = 0; i < stations.size(); i++){
        if(stations[i].name == name){
            found = true;
            cout<<stations[i].name<<" found."<<endl;
        }
    }
    if(found == false){
        vertex v;
        v.name = name;
        v.visited = false;
        v.parent = NULL;
        stations.push_back(v);
    }
}

int Graph::pathLength(std::string startingSta, std::string endingSta)
{
    int indexOfStart;
    for (int i = 0; i < stations.size(); i++){
        if(stations[i].name == startingSta){
            indexOfStart = i;
            break;
        }
    }
    for (int i = 0; i < stations[indexOfStart].adj.size(); i++){
        if(stations[indexOfStart].adj[i].v->name == endingSta){
            return stations[indexOfStart].adj[i].weight;
        }
    }
}

void Graph::TSPNN(std::string startingSta)
{
    vector<vertex> V;
    vector<vertex> U;
    for (int i = 0; i < stations.size(); i ++){
        if(stations[i].name != startingSta){
            V.push_back(stations[i]);
        } else{
            U.push_back(stations[i]);
        }
    }
    float totalDistance = 0;
    while(!V.empty()){
        vertex u;
        u = U[U.size()-1];
        vertex v;
        v = V[0];
        int index = 0;
        int distance = pathLength(u.name, V[0].name);
        for (int i = 0; i < V.size(); i++){
            if(pathLength(u.name, V[i].name) < distance){
                v = V[i];
                index = i;
                distance = pathLength(u.name, V[i].name);
            }
        }
        U.push_back(v);
        V.erase(V.begin()+index);
        totalDistance += distance;
    }
    cout<<"Here's the path to take: "<<endl;
    for (int i = 0; i < U.size(); i++){
        cout<<U[i].name<<endl;
    }
    cout<<"It has a distance of "<<totalDistance << " miles." << endl;
}

void Graph::nearestFive(std::string sta)
{
    vector<vertex> nearestFive;
    vector<vertex> V;
    for (int i = 0; i < stations.size(); i ++){
        if(stations[i].name != sta){
            V.push_back(stations[i]);
        }
    }
    while(nearestFive.size() < 5){
        int index;
        vertex v;
        int distance = pathLength(sta, V[0].name) + 1;
        for (int i = 0; i < V.size(); i++){
            if(pathLength(sta, V[i].name) < distance){
                v = V[i];
                index = i;
                distance = pathLength(sta, V[i].name);
            }
        }
        nearestFive.push_back(v);
        V.erase(V.begin()+index);
    }
    cout<<"The nearest five are: "<<endl;
    for (int i = 0; i < nearestFive.size(); i++){
        cout<<nearestFive[i].name<<endl;
    }
}
