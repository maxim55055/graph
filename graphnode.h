#ifndef GRAPHNODE_H
#define GRAPHNODE_H

#include <QGraphicsEllipseItem>
#include <QGraphicsTextItem>
#include <QPen>
#include <QBrush>
#include <QFont>

#include "graph.h"

class GraphNode : public QGraphicsEllipseItem
{
public:
    explicit GraphNode(qreal x, qreal y, int id, qreal radius = 30, graph* gr = nullptr);
    ~GraphNode();

    int getId() const { return m_id; }

    void updateTextPosition();

private:
    int m_id;
    qreal m_radius;
    QGraphicsTextItem* m_textItem;
};

#endif