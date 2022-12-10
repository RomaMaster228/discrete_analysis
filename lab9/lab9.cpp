#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>

using namespace std;

bool BFS(vector<unordered_map<int,int>>& graph, int start, int end, vector<int>& parents) {
    parents.clear();
    parents.resize(graph.size(), -1);
    vector<bool> visited(graph.size());
    queue<int> q;
    q.push(start);
    visited[start] = true;

    while (!q.empty()) {
        int cur_vertex = q.front();
        q.pop();
        for (auto edge : graph[cur_vertex]) {
            int new_vertex = edge.first;
            int new_capacity = edge.second;
            if (!visited[new_vertex] && new_capacity) {
                visited[new_vertex] = true;
                q.push(new_vertex);
                parents[new_vertex] = cur_vertex;
                if (new_vertex == end) {
                    return true;
                }
            }
        }
    }
    return false;
}

long long MaxFlow(vector<unordered_map<int,int>>& graph, int source, int sink) {
    long long resFlow = 0;
    vector<int> parents;
    while (BFS(graph, source, sink, parents)) {
        int flow = 1000000001;
        for (int i = sink; i != source; i = parents[i]) {
            if (i == -1) {
                throw runtime_error("Can't find a parent for not source node.");
            }
            if (graph[parents[i]][i] < flow) {
                flow = graph[parents[i]][i];
            }
        }
        resFlow += flow;

        for (int i = sink; i != source; i = parents[i]) {
            graph[parents[i]][i] -= flow;
            graph[i][parents[i]] += flow;
        }
    }
    return resFlow;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    vector<unordered_map<int,int>> graph(n);
    for (int i = 0; i < m; ++i) {
        int from, to, capacity;
        cin >> from >> to >> capacity;
        --from;
        --to;
        graph[from][to] = capacity;
    }
    cout << MaxFlow(graph, 0, n - 1) << "\n";
}