#include "graph.h"
#include "graphview.h"
#include "graphnode.h"

#include <QMessageBox>

#include <queue>

#include <QDebug>

#include <climits>

graph::graph() {

}
void graph::addVertex(GraphNode* node) {
    int new_ind = this->adjacency.size();
    this->adjacency.resize(new_ind+1);
    this->adjacency[new_ind] = {};

    int new_ind_nodes = this->graphNodesPtrs.size();
    this->graphNodesPtrs.resize(new_ind_nodes+1);
    this->graphNodesPtrs[new_ind_nodes] = node;
}
void graph::addEdge(int firstV, int secondV, int weight) {
    this->addtoAdj(firstV, secondV, weight);
    this->addtoAdj(secondV, firstV, weight);
}

void graph::addtoAdj(int firstV, int secondV, int weight) {
    int new_ind = this->adjacency[firstV].size();
    this->adjacency[firstV].resize(new_ind+1);
    std::pair<int, int> newEdge;
    newEdge.first = secondV;
    newEdge.second = weight;
    this->adjacency[firstV][new_ind] = newEdge;
}

QString graph::bfs(int start) {
    QString res = "";

    std::vector<bool> done(int(this->adjacency.size()), false);

    std::vector<bool> inQueue(int(this->adjacency.size()), false);

    std::queue<int> q;

    q.push(start);
    while(!q.empty()) {
        int current = q.front();
        q.pop();
        for (std::pair<int, int> el : this->adjacency[current]) {
            if (done[el.first]) {
                continue;
            }
            if (!inQueue[el.first]) {
                q.push(el.first);
                inQueue[el.first] = true;
            }

        }
        done[current] = true;
        res += std::to_string(current+1) + ' ';
    }
    return res;
}

QString graph::dfs(int start) {
    QString res = "";
    std::vector<bool> done(int(this->adjacency.size()), false);
    return this->dfsRecursion(done, res, start);
}

QString graph::dfsRecursion(std::vector<bool>& done, QString res, int start) {
    qDebug() << start;
    done[start] = true;
    for (std::pair<int, int> s_pair : this->adjacency[start]) {
        if (!done[s_pair.first]) {
            res = dfsRecursion(done, res, s_pair.first);
        }
    }
    return res + QString::fromStdString(std::to_string(start+1)) + ' ';
}

std::vector<int> graph::reconstructPath(int from, int to,
                                        const std::vector<int>& prev) {
    std::vector<int> path;
    if (prev[to] == -1) {
        return path;
    }

    for (int at = to; at != -1; at = prev[at]) {
        path.push_back(at);
    }
    std::reverse(path.begin(), path.end());

    if (path.empty() || path[0] != from) {
        return std::vector<int>();
    }

    return path;
}


std::vector<Route> graph::dijkstra(int from) {
    std::vector<Route> routes;

    int n = adjacency.size();
    if (from >= n) return routes;

    std::vector<int> dist(n, std::numeric_limits<int>::max());
    std::vector<int> prev(n, -1);
    std::vector<bool> visited(n, false);

    dist[from] = 0;

    using P = std::pair<int, int>;
    std::priority_queue<P, std::vector<P>, std::greater<P>> pq;
    pq.push({0, from});

    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();

        if (visited[u]) continue;
        visited[u] = true;

        for (const auto& neighbor : adjacency[u]) {
            int v = neighbor.first;
            int weight = neighbor.second;

            if (!visited[v] && dist[u] != std::numeric_limits<int>::max()) {
                int newDist = dist[u] + weight;
                if (newDist < dist[v]) {
                    dist[v] = newDist;
                    prev[v] = u;
                    pq.push({newDist, v});
                }
            }
        }
    }

    for (int to = 0; to < n; ++to) {
        Route route;
        route.path = reconstructPath(from, to, prev);
        route.totalWeight = (dist[to] != std::numeric_limits<int>::max()) ?
                                dist[to] : -1;
        routes.push_back(route);
    }

    return routes;
}


std::vector<std::vector<int>> graph::floid() {
    std::vector<std::vector<int>> res(this->adjacency.size(), std::vector<int>(this->adjacency.size(), INT_MAX/3));
    for (int i = 0; i < int(this->adjacency.size()); i++) {
        res[i][i] = 0;
        for(const std::pair<int, int> route: this->adjacency[i]) {
            res[i][route.first] = route.second;
        }
    }

    for (int through = 0;through  < int(this->adjacency.size());through++) {
        for (int from = 0; from < int(this->adjacency.size());from++) {
            for (int to = 0; to < int(this->adjacency.size());to++) {
                res[from][to] = std::min(res[from][to], res[from][through]+res[through][to]);
            }
        }
    }
    return res;
}
