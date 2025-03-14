#include "dijkstras.h"
#include <algorithm>
#include <limits>
#include <queue>
#include <utility>
#include <vector>
constexpr int UNDEFINED = -1;

struct Node{
    int vertex;
    int weight;
    Node(int vertex, int weight) : vertex(vertex), weight(weight) {}
};


vector<int> dijkstra_shortest_path(const Graph& G, int source, vector<int>& previous){
    int num_Vertices = G.size();
    vector<int> distances(num_Vertices, INF);
    vector<bool> visited(num_Vertices, false);
    distances[source] = 0;
    previous[source] = UNDEFINED;
    priority_queue<pair<int, int>> minHeap;
    minHeap.push({source,0});
    while(!minHeap.empty()){
        int u = minHeap.top().first;
        minHeap.pop();
        if(visited[u]) continue;
        visited[u] = true;
        for(Edge e: G[u]){
            int v = e.dst;
            int weight = e.weight;
            if(!visited[v] && distances[u] + weight < distances[v]){
                distances[v] = distances[u] + weight;
                previous[v] = u;
                minHeap.push({v,distances[v]});
            }
        }
    }
    return distances;
}

vector<int> extract_shortest_path(const vector<int> & distances, const vector<int> &previous, int destination){
    vector<int> result;
    int position = destination;
    while(distances[position] != 0){
        result.push_back(position);
        position = previous[position];
    }
    result.push_back(position);
    std::reverse(result.begin(), result.end());
    return result;
}

void print_path(const vector<int> &v, int total){
    for(size_t i = 0; i < v.size(); ++i){
        cout << v[i] << " ";
    }
    cout << endl <<"Total cost is "<< total <<endl;
}