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

    g.TSPNN("35th & Colorado");

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
    int y = 0;

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
