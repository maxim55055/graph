#ifndef GRAPHVIEW_H
#define GRAPHVIEW_H

#include <QGraphicsView>
#include "graphnode.h"
#include <QMouseEvent>
#include "graph.h"

class graph;

class GraphView : public QGraphicsView
{
public:
    GraphView(QWidget *parent = nullptr);
    void addNode(int x, int y);
    graph* getgraph() { return graphClass; };
    QGraphicsScene* getScene() {return m_scene; };
private:
    QGraphicsScene *m_scene;
    int nextNodeId;
    graph* graphClass;
protected:
    void mousePressEvent(QMouseEvent *event) override;
};

#endif // GRAPHVIEW_H
