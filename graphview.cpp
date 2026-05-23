#include "graphview.h"
#include "graph.h"

#include <QMessageBox>

GraphView::GraphView(QWidget *parent) :
    QGraphicsView (parent), nextNodeId(1){
    m_scene = new QGraphicsScene(this);
    setScene(m_scene);

    setRenderHint(QPainter::Antialiasing);
    setSceneRect(0, 0, 1000, 700);
    setBackgroundBrush(QBrush(Qt::white));
    setMouseTracking(true);



    graphClass = new graph();

    this->addNode(346, 41);
    this->addNode(188, 161);
    this->addNode(33, 309);
    this->addNode(320, 462);
    this->addNode(284, 255);
    this->addNode(504, 188);


}

void GraphView::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        QPointF scenePos = mapToScene(event->pos());
        addNode(scenePos.x(), scenePos.y());
        qDebug() << "Добавлена вершина" << (nextNodeId - 1)
                 << "в позиции" << scenePos;
    }

    QGraphicsView::mousePressEvent(event);
}

void GraphView::addNode(int x, int y) {

    GraphNode *node = new GraphNode(x, y, nextNodeId++, 25, this->graphClass);

    scene()->addItem(node);
    update();
}