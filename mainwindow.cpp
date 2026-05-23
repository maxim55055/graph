#include "mainwindow.h"
#include "ui_mainwindow.h"


struct EdgeInfo {
    QGraphicsLineItem* line;
    QGraphicsTextItem* weightText;
    int weight;
    GraphNode* from;
    GraphNode* to;
};

void updateEdgePosition(EdgeInfo* edge) {
    if (!edge || !edge->from || !edge->to) return;

    // Получаем центры узлов
    QPointF fromCenter = edge->from->boundingRect().center() + edge->from->pos();
    QPointF toCenter = edge->to->boundingRect().center() + edge->to->pos();

    // Вычисляем радиусы узлов (предполагаем что узлы круглые)
    qreal fromRadius = edge->from->boundingRect().width() / 2;
    qreal toRadius = edge->to->boundingRect().width() / 2;

    // Вычисляем направление и расстояние
    QPointF direction = toCenter - fromCenter;
    qreal distance = QLineF(fromCenter, toCenter).length();

    if (distance < 1.0) return; // Узлы слишком близко

    QPointF unitDirection = direction / distance;

    // Точки на границах кругов
    QPointF fromPoint = fromCenter + unitDirection * fromRadius;
    QPointF toPoint = toCenter - unitDirection * toRadius;

    // Обновляем линию
    edge->line->setLine(QLineF(fromPoint, toPoint));

    // Обновляем позицию текста веса
    QPointF midPoint = (fromPoint + toPoint) / 2;

    // Смещение текста перпендикулярно линии
    QPointF offset(-unitDirection.y() * 15, unitDirection.x() * 15);
    QPointF textPos = midPoint + offset;

    QRectF textRect = edge->weightText->boundingRect();
    edge->weightText->setPos(textPos.x() - textRect.width() / 2,
                             textPos.y() - textRect.height() / 2);
}

// Функция для создания ребра между двумя узлами
EdgeInfo* drawEdge(QGraphicsScene* scene, GraphNode* from, GraphNode* to, int weight = 1) {
    if (!scene || !from || !to) return nullptr;

    EdgeInfo* edge = new EdgeInfo();
    edge->from = from;
    edge->to = to;
    edge->weight = weight;

    // Создаем линию
    edge->line = new QGraphicsLineItem();
    QPen pen(Qt::black, 2);
    edge->line->setPen(pen);
    edge->line->setZValue(1); // Под узлами

    // Создаем текст для веса
    edge->weightText = new QGraphicsTextItem();
    edge->weightText->setPlainText(QString::number(weight));

    QFont font;
    font.setPointSize(10);
    font.setBold(true);
    edge->weightText->setFont(font);
    edge->weightText->setDefaultTextColor(Qt::red);
    edge->weightText->setZValue(5);

    // Устанавливаем флаг игнорирования трансформаций для текста
    edge->weightText->setFlag(QGraphicsItem::ItemIgnoresTransformations, true);

    // Добавляем на сцену
    scene->addItem(edge->line);
    scene->addItem(edge->weightText);

    // Устанавливаем начальные позиции
    updateEdgePosition(edge);

    return edge;
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    graph* grapClass = ui->graphicsView->getgraph();

    grapClass->addEdge(0, 1, 11);
    drawEdge(ui->graphicsView->getScene(),  grapClass->getNode(0), grapClass->getNode(1), 11);

    grapClass->addEdge(0, 5, 15);
    drawEdge(ui->graphicsView->getScene(),  grapClass->getNode(0), grapClass->getNode(5), 16);

    grapClass->addEdge(1, 2, 18);
    drawEdge(ui->graphicsView->getScene(),  grapClass->getNode(1), grapClass->getNode(2), 18);

    grapClass->addEdge(1, 4, 23);
    drawEdge(ui->graphicsView->getScene(),  grapClass->getNode(1), grapClass->getNode(4), 32);

    grapClass->addEdge(2, 4, 6);
    drawEdge(ui->graphicsView->getScene(),  grapClass->getNode(2), grapClass->getNode(4), 6);

    grapClass->addEdge(2, 3, 16);
    drawEdge(ui->graphicsView->getScene(),  grapClass->getNode(2), grapClass->getNode(3), 16);

    grapClass->addEdge(3, 5, 9);
    drawEdge(ui->graphicsView->getScene(),  grapClass->getNode(3), grapClass->getNode(5), 9);

    grapClass->addEdge(4, 5, 3);
    drawEdge(ui->graphicsView->getScene(),  grapClass->getNode(4), grapClass->getNode(5), 3);

    connect(ui->addEdgeButton, &QPushButton::clicked, this, [this, grapClass] () {
        int start = ui->start->toPlainText().toInt() - 1, end = ui->end->toPlainText().toInt() - 1, weight = ui->weight->toPlainText().toInt();
        grapClass->addEdge(start, end, weight);
        drawEdge(ui->graphicsView->getScene(),  grapClass->getNode(start), grapClass->getNode(end), weight);
    });

    connect(ui->bfsButton, &QPushButton::clicked, this, [this, grapClass] () {
        ui->bfsInput->setText(grapClass->bfs(3));
    });

    connect(ui->dfsButton, &QPushButton::clicked, this, [this, grapClass] () {
        ui->dfsInput->setText(grapClass->dfs(3));
    });

    connect(ui->dijkstraButton, &QPushButton::clicked, this, [this, grapClass] () {
        QString routes;
        for(Route r : grapClass->dijkstra(3)) {
            for(int v : r.path) {
                routes += std::to_string(v+1) + ' ';
            }
            if (r.totalWeight > 0)  routes += " | " + std::to_string(r.totalWeight) + "\n";
        }
        ui->dijkstraInput->setText(routes);
    });

    connect(ui->floidButton, &QPushButton::clicked, this, [this, grapClass]() {
        std::vector<std::vector<int>> routes = grapClass->floid();
        QString res;
        for (int i = 0; i < routes.size(); i++) {
            for (int j = 0; j < routes[i].size(); j++) {
                if (routes[i][j] < INT_MAX / 3){
                    res += std::to_string(i+1) + " -> " + std::to_string(j+1) + ": " + std::to_string(routes[i][j]) + "\n";
                } else {
                    res += std::to_string(i+1) + " -> " + std::to_string(j+1) + ": нет пути\n";
                }
            }
        }

        ui->floidOutput->setText(res);
    });

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_clearButton_clicked() {
    // Очистка всех вершин
    QGraphicsScene *scene = ui->graphicsView->scene();
    if (scene) {
        scene->clear();
    }
}