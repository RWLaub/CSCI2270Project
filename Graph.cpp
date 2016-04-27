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
    //cout<<"Adding edge from " << v1 << " to " << v2 << " of weight " << weight << endl;

    for (unsigned i = 0; i < stations.size(); i++){
        if(stations[i].name == v1){
            for(unsigned j = 0; j < stations.size(); j++){
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
    for(unsigned i = 0; i < stations.size(); i++){
        if(stations[i].name == name){
            found = true;
            //cout<<stations[i].name<<" found."<<endl;
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

void Graph::displayEdges(std::string startingSta)
{
    for(unsigned i = 0; i < stations.size(); i++)
    {
        if(stations[i].name == startingSta)
        {
			for(unsigned s = 0; s < stations[i].adj.size(); s++)
			{
				cout<<stations[i].name<<" to "<< stations[i].adj[s].v->name <<" : "<< stations[i].adj[s].weight<<" miles"<<endl;
			}
			return;
        }
    }
    cout<<startingSta<<" does not exist."<<endl;
}

float Graph::pathLength(std::string startingSta, std::string endingSta)
{
    float indexOfStart;
    for (unsigned i = 0; i < stations.size(); i++)
    {
        if(stations[i].name == startingSta)
        {
            indexOfStart = i;
            break;
        }
    }
    for (unsigned i = 0; i < stations[indexOfStart].adj.size(); i++)
    {
        if(stations[indexOfStart].adj[i].v->name == endingSta)
        {
            return stations[indexOfStart].adj[i].weight;
        }
    }
    return 0;
}

void Graph::showAllSta()
{
	for(unsigned i= 0; i < stations.size(); i++)
	{
		cout<<stations[i].name<<endl;
	}
}

std::vector<vertex> Graph::TSPNN(std::string startingSta, float *dis)
{
    vector<vertex> V;
    vector<vertex> U;
    for (unsigned i = 0; i < stations.size(); i ++){
        if(stations[i].name != startingSta){
            V.push_back(stations[i]);
        } else{
            U.push_back(stations[i]);
        }
    }
    //float *totalDistance = dis;
    while(!V.empty()){
        vertex u;
        u = U[U.size()-1];
        vertex v;
        v = V[0];
        int index = 0;
        float distance = pathLength(u.name, V[0].name);
        for (unsigned i = 0; i < V.size(); i++){
            if(pathLength(u.name, V[i].name) < distance){
                v = V[i];
                index = i;
                distance = pathLength(u.name, V[i].name);
            }
        }
        U.push_back(v);
        V.erase(V.begin()+index);
        //*dis += distance;
    }
    //*dis += pathLength(U[U.size()].name, U[0].name);
    *dis = totalTourLength(U);
    /*cout<<"Here's the path to take: "<<endl;
    for (unsigned i = 0; i < U.size(); i++){
        cout<<U[i].name<<endl;
    }
    cout<<"It has a distance of "<<totalDistance << " miles." << endl;*/

    return U;
}

void Graph::nearestFive(std::string sta)
{
    vector<vertex> nearestFive;
    vector<vertex> V;
    for (unsigned i = 0; i < stations.size(); i ++){
        if(stations[i].name != sta){
            V.push_back(stations[i]);
        }
    }
    while(nearestFive.size() < 5){
        int index;
        vertex v;
        int distance = pathLength(sta, V[0].name) + 1;
        for (unsigned i = 0; i < V.size(); i++){
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
    for (unsigned i = 0; i < nearestFive.size(); i++){
        cout<<nearestFive[i].name<<endl;
    }
}

void Graph::bestSS(std::string startingSta)
{
	vector<vertex> nearest4;
	vector<vertex> V;
    for (unsigned i = 0; i < stations.size(); i ++){
        if(stations[i].name != startingSta){
            V.push_back(stations[i]);
        }
    }

	for(unsigned i = 0; i < stations.size(); i++)
    {
        if(stations[i].name == startingSta)
        {
			while(nearest4.size() < 4)
			{
				int index;
				vertex v;
				int distance = pathLength(startingSta, V[0].name) + 1;
				for (unsigned s = 0; s < V.size(); s++)
				{
					if(pathLength(startingSta, V[s].name) < distance)
					{
						v = V[s];
						index = s;
						distance = pathLength(startingSta, V[s].name);
					}
				}
				nearest4.push_back(v);
				V.erase(V.begin()+index);
			}
        }
    }

    float first = 0;
    float second = 0;
    float third = 0;
    float fourth = 0;
    float fifth = 0;
    vector<vertex> x = TSP2Opt(startingSta, &first);
    x = TSP2Opt(nearest4[0].name, &second);
    x = TSP2Opt(nearest4[1].name, &third);
    x = TSP2Opt(nearest4[2].name, &fourth);
    x = TSP2Opt(nearest4[3].name, &fifth);
    float compare = first;
    bool finish = false;
    while(!finish)
    {
		if(compare > second){
			compare = second;
		}else if(compare > third){
			compare = third;
		} else if(compare > fourth){
			compare = fourth;
		} else if(compare > fifth){
			compare = fifth;
		} else{
			finish = true;
		}
	}

	if(compare == second){
		cout<<"best starting station is: "<< nearest4[0].name<<endl;
	}else if(compare == third){
		cout<<"best starting station is: "<< nearest4[1].name<<endl;
	} else if(compare == fourth){
		cout<<"best starting station is: "<< nearest4[2].name<<endl;
	} else if(compare == fifth){
		cout<<"best starting staion is: "<< nearest4[3].name<<endl;
	} else{
		cout<<"best starting station is: "<< startingSta<<endl;
	}

}

void Graph::printR(std::vector<vertex> path)
{
	for (unsigned i = 0; i < path.size(); i++)
	{
        cout<<path[i].name<<endl;
    }
}

std::vector<vertex> Graph::TSP2Opt(std::string startingSta, float *dis){
    vector<vertex> T = TSPNN(startingSta,dis);
    bool noChange = true;
    while(noChange){
        for(int i = 0; i < T.size()-1; i++){
            for(int j = i + 1; j < T.size(); j++){
                vector<vertex> newT = T;
                vertex tmp = T[i];
                newT[i] = newT[j];
                newT[j] = tmp;
                if (totalTourLength(newT) < totalTourLength(T)){
                    T = newT;
                    noChange = false;
                    break;
                }
            }
        }
    }
    *dis = totalTourLength(T);
    return T;
}

float Graph::totalTourLength(std::vector<vertex> path){
    float dis;
    for(unsigned i = 1; i < path.size(); i++){
        dis += pathLength(path[i-1].name, path[i].name);
    }
    dis += pathLength(path[path.size()-1].name, path[0].name);
    return dis;
}

bool Graph::isStation(std::string station){
	for(unsigned i = 0; i<stations.size(); i++){
		if(stations[i].name == station){
			return true;
		}
	}
	return false;
}
