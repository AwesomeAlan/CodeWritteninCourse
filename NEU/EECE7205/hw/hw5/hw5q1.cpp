#include <iostream>
#include <limits.h>
#include <array>
#include <vector>
#include <queue>
using namespace std;

// An adjacency list. Each vec[i] holds all the adjacent nodes of i
// The first int is the vertex of the adjacent nodes, the second int is the edge weight
vector< vector<pair<int, int> > > adjacency_list()
{
    // adjacency list is stored in vec
    vector< vector<pair<int, int> > > vec;

    const int n = 7;
    for(int i = 0; i < n; i++)
    {
        vector<pair<int, int> > row;
        vec.push_back(row);
    }

    // add edges into the adjacency list

    vec[0].push_back(make_pair(1, 2));
    vec[0].push_back(make_pair(2, 3));

    vec[1].push_back(make_pair(0, 2));
    vec[1].push_back(make_pair(5, 1));

    vec[2].push_back(make_pair(0, 3));
    vec[2].push_back(make_pair(5, 2));

    vec[3].push_back(make_pair(1, 4));
    vec[3].push_back(make_pair(4, 1));
    vec[3].push_back(make_pair(6, 2));

    vec[4].push_back(make_pair(3, 1));
    vec[4].push_back(make_pair(5, 2));
    vec[4].push_back(make_pair(6, 1));

    vec[5].push_back(make_pair(1, 1));
    vec[5].push_back(make_pair(2, 2));
    vec[5].push_back(make_pair(4, 2));
    vec[5].push_back(make_pair(6, 2));

    vec[6].push_back(make_pair(3, 2));
    vec[6].push_back(make_pair(4, 1));
    vec[6].push_back(make_pair(5, 2));

    //return the graph
    return vec;
}

// dijiksra finds all shortest paths from "start" to all other vertices
vector<int> dijiksra(vector< vector<pair<int, int> > > &vec, int &start)
{
    vector<int> length;
    int n = vec.size();
    for(int i = 0; i < n; i++)
    {
        length.push_back(1000000007); // Define "infinity" as necessary by constraints
    }

    priority_queue<pair<int, int>, vector< pair<int, int> >, greater<pair<int, int> > > pq;

    pq.push(make_pair(start, 0));
    length[start] = 0;

    while(pq.empty() == false)
    {
        int u = pq.top().first;
        pq.pop();

        for(int i = 0; i < vec[u].size(); i++)
        {
            int v = vec[u][i].first;
            int weight = vec[u][i].second;

            if(length[v] > length[u] + weight)
            {

                length[v] = length[u] + weight;

                pq.push(make_pair(v, length[v]));
            }
        }
    }

    return length;
}

void minimal_length(vector<int> &length, int &start)
{
    cout <<"Vertex \t Distance from Source" << endl;
    for (int i = 0; i < length.size(); i++)
        cout  << i << " \t\t\t\t" <<length[i]<< endl;
}

int main()
{
    // Construct the adjacency list
    vector< vector<pair<int, int> > > vec = adjacency_list();

    int node = 0;
    vector<int> length = dijiksra(vec, node);

    // Print the list.
    minimal_length(length, node);

    return 0;
}