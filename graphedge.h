#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <QGraphicsScene>
#include "graphnode.h"

class GraphEdge {
public:
    GraphEdge(GraphNode* from, GraphNode* to, int weight = 1);
    ~GraphEdge();

    void updatePosition();
    QGraphicsLineItem* getLineItem() { return lineItem; }
    QGraphicsTextItem* getWeightItem() { return weightItem; }

    GraphNode* getFrom() const { return fromNode; }
    GraphNode* getTo() const { return toNode; }
    int getWeight() const { return weight; }

private:
    GraphNode* fromNode;
    GraphNode* toNode;
    int weight;
    QGraphicsLineItem* lineItem;
    QGraphicsTextItem* weightItem;
};


#endif // GRAPH_H