#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <QString>

class GraphNode;
class GraphView;

struct Route {
    std::vector<int> path;
    int totalWeight;
};



class graph
{
private:
    std::vector<std::vector<std::pair<int, int>>> adjacency{};
    void addtoAdj(int firstV, int secondV, int weight);
    std::vector<GraphNode*> graphNodesPtrs{};
    QString dfsRecursion(std::vector<bool>& done, QString res, int start);
    std::vector<int> reconstructPath(int from, int to, const std::vector<int>& prev);
public:
    graph();
    void addVertex(GraphNode* node = nullptr);
    void addEdge(int firstV, int secondV, int weight);
    GraphNode* getNode(int ind) {return graphNodesPtrs[ind]; };
    QString bfs(int start);
    QString dfs(int start);
    std::vector<Route> dijkstra(int from);
    std::vector<std::vector<int>> floid();
};

#endif // GRAPH_H
