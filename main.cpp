#include <iostream>
#include "Graph.h"
#include <fstream>  //allows istream/ostream
#include <string>
#include <sstream>      // std::stringstream, std::stringbuf

using namespace std;

void readFileIntoGraph(Graph & g, char* fileName);

int main(int argc, char*argv[])
{
    // Create a graph
    Graph g;

    // Read file into graph
    //readFileIntoGraph(g, "bcycleStations.txt");
    readFileIntoGraph(g, argv[1]);
	
	bool end = true;
	string userIn;
	string data;
	
	while(end){
		
		cout<<"======Main Menu======"<<endl;
		cout<<"1. Show all stations"<<endl;
		cout<<"2. Nearest five stations"<<endl;
		cout<<"3. Find route"<<endl;
		cout<<"4. Find best starting station"<<endl;
		cout<<"5. How far other stations from me"<< endl; 
		cout<<"6. Quit"<<endl;

		getline(cin,userIn);
		
		if (userIn == "1"){
			g.showAllSta();
		} else if (userIn == "2"){
			cout<<"Enter a station name:"<<endl;
			getline(cin,data);
			if(!g.isStation(data)){
				cout<<"Enter a valid station (press 1 to view all stations)"<<endl;
			} else{
				g.nearestFive(data);
			}
		} else if (userIn == "3"){
			cout<<"Enter the starting station:"<<endl;
			getline(cin,data);
			if(!g.isStation(data)){
				cout<<"Enter a valid station (press 1 to view all stations)"<<endl;
			}else{
				float n = 0;
				vector<vertex> rout = g.TSP2Opt(data, &n);
				g.printR(rout);
				cout<<"It has a distance of "<<n << " miles." << endl;
			}
		} else if (userIn == "4"){
			cout << "Enter a station name:" << endl;
			getline(cin,data);
			if(!g.isStation(data)){
				cout<<"Enter a valid station (press 1 to view all stations)"<<endl;
			} else{
				g.bestSS(data);
			}
		} else if (userIn == "5"){
			cout << "Enter a station name:" << endl;
			getline(cin,data);
			if(!g.isStation(data)){
				cout<<"Enter a valid station (press 1 to view all stations)"<<endl;
			}else{
				g.displayEdges(data);
			}
		} else if (userIn == "6"){
			cout<<"Goodbye!"<<endl;
			break;
		} else {
			cout<< "error: Invalid entry,\n choose a valid number!"<<endl;
		}

	}
    return 0;
}

/* reads file into graph */
void readFileIntoGraph(Graph & g, char* fileName)
{
    vector<string> cities;
    ifstream in_stream;
    //cout << fileName << endl;
    in_stream.open(fileName);
    if (!in_stream)
    {
        cout << "Could not open file\n";
        return;
    }

    string city;
    string line;
    getline(in_stream,line);
    std::stringstream ss(line);
    //int y = 0;

    // Read a list of cities from the first line
    while (getline(ss,city,','))
    {
        if (city != "stations")
        {
            g.addVertex(city);
            cities.push_back(city);
        }
    }

    // Now read in all the vertices
    int i = 0;
    string in;
    while (!in_stream.eof())
    {
        i = -1;
        getline(in_stream,line);
        stringstream ss(line); // why does ss.str(line) not work?

        while (getline(ss,in,','))
        {
            if (i == -1)
            {
                city = in;
            }
            else
            {
                if (in != "-1" && in != "0")
                {
                    g.addEdge(city,cities[i],stof(in.c_str()));
                }
            }
            i++;
        }
    }

}
