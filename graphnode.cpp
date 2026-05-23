#include "graphnode.h"
#include <QFont>

#include <queue>
#include <algorithm>

GraphNode::GraphNode(qreal x, qreal y, int id, qreal radius, graph* gr)
    : QGraphicsEllipseItem(-radius, -radius, radius * 2, radius * 2)
    , m_id(id)
    , m_radius(radius)
    , m_textItem(nullptr)
{
    // Устанавливаем позицию узла
    setPos(x, y);

    // Настройка внешнего вида узла
    setBrush(QBrush(QColor(255, 255, 200)));  // Светло-желтый
    setPen(QPen(Qt::black, 2));
    setFlags(QGraphicsItem::ItemIsMovable |
             QGraphicsItem::ItemIsSelectable |
             QGraphicsItem::ItemSendsGeometryChanges);
    setZValue(10);

    // Создаем текст с ID
    m_textItem = new QGraphicsTextItem(this);
    m_textItem->setPlainText(QString::number(m_id));
    m_textItem->setDefaultTextColor(Qt::black);

    // Настройка шрифта
    QFont font("Arial", 12);
    font.setBold(true);
    m_textItem->setFont(font);

    // Центрируем текст
    QRectF textRect = m_textItem->boundingRect();
    qreal textX = radius - textRect.width() / 2;
    qreal textY = radius - textRect.height() / 2;
    m_textItem->setPos(textX, textY);

    // Настройка текста
    m_textItem->setZValue(11);
    m_textItem->setFlag(QGraphicsItem::ItemIsSelectable, false);
    m_textItem->setFlag(QGraphicsItem::ItemIgnoresTransformations, true);
    m_textItem->setAcceptedMouseButtons(Qt::NoButton);

    gr->addVertex(this);
}

GraphNode::~GraphNode()
{
    // m_textItem удалится автоматически как дочерний элемент
}

void GraphNode::updateTextPosition()
{
    if (m_textItem) {
        QRectF textRect = m_textItem->boundingRect();
        qreal textX = m_radius - textRect.width() / 2;
        qreal textY = m_radius - textRect.height() / 2;
        m_textItem->setPos(textX, textY);
    }
}
