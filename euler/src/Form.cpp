/*
 * File:   Form.cpp
 * Author: sova
 *
 */

#include "Form.h"
#include <QPainter>
#include <QDebug>
#include <cstdlib>

Form::Form() {
    widget.setupUi(this);
    connect(widget.pushSolve, SIGNAL(clicked()),
            this, SLOT(solve()));

    scene = widget.graphicsView->scene();
    if (scene == NULL) {
        scene = new QGraphicsScene();
        widget.graphicsView->setScene(scene);
    }
    ellipse1 = NULL;
    init();
}

void Form::init() {
    for (int i = 0; i < 28; i++) {
        scene->addLine(0, 25 * i, 699, 25 * i);
        scene->addLine(25 * i, 0, 25 * i, 699);
    }
}

inline int Form::getX(int x) {
    int modx = x % 25;
    x -= modx + ((modx < 14) ? 0 : -25);
    return x;
}

inline int Form::getY(int y) {
    int mody = y % 25;
    y -= mody + ((mody < 14) ? 0 : -25);
    return y;
}

void Form::mousePressEvent(QMouseEvent* e) {
    int x = e->x() - widget.graphicsView->x();
    int y = e->y() - widget.graphicsView->y();
    x = getX(x);
    y = getY(y);
    if ((x > 15) && (y > 15) && (x < 684) && (y < 684)) {
        QGraphicsEllipseItem* ellipse = findQGraphicsEllipseItem(x, y);
        if (widget.radioVertices->isChecked()) {
            if (ellipse != NULL) {
                deleteEllipse(ellipse);
            } else {
                drawEllipse(x, y);
            }
        } else {
            if (ellipse != NULL) {
                if (ellipse1 == NULL) {
                    setEllipseAsActive(ellipse);
                } else {
                    if (ellipse1 == ellipse) {
                        setEllipseAsNonActive(ellipse);
                    } else {
                        int x2 = ellipse1->rect().x() + 5;
                        int y2 = ellipse1->rect().y() + 5;
                        QGraphicsLineItem* line = findQGraphicsLineItem(x, y, x2, y2);
                        if (line == NULL) {
                            setEllipseAsNonActive(ellipse1);
                            drawLine(x, y, x2, y2);
                        } else {
                            deleteLine(line);
                        }
                    }
                }
            }
        }
    }
}

QGraphicsEllipseItem* Form::findQGraphicsEllipseItem(int x, int y) {
    for (int i = 0; i < ellipses.size(); i++) {
        QGraphicsEllipseItem* ellipse = ellipses[i];
        int x0 = ellipse->rect().x();
        int y0 = ellipse->rect().y();
        if (((x0 + 5) == x) && ((y0 + 5) == y)) {
            return ellipse;
        }
    }
    return NULL;
}

QGraphicsLineItem* Form::findQGraphicsLineItem(int x1, int y1, int x2, int y2) {
    for (int i = 0; i < lines.size(); i++) {
        QGraphicsLineItem* line = lines[i];
        int ix1 = line->line().x1();
        int iy1 = line->line().y1();
        int ix2 = line->line().x2();
        int iy2 = line->line().y2();
        if ((x1 == ix1) && (y1 == iy1) && (x2 == ix2) && (y2 == iy2)) {
            return line;
        }
        if ((x1 == ix2) && (y1 == iy2) && (x2 == ix1) && (y2 == iy1)) {
            return line;
        }
    }
    return NULL;
}

void Form::drawEllipse(int x, int y) {
    QBrush brush;
    brush.setColor(Qt::red);
    brush.setStyle(Qt::SolidPattern);
    QGraphicsEllipseItem* item = scene->addEllipse(x - 5, y - 5, 10, 10, Qt::SolidLine, brush);
    ellipses.push_back(item);
}

void Form::drawLine(int x, int y, int x2, int y2) {
    QBrush brushLine;
    brushLine.setColor(Qt::blue);
    brushLine.setStyle(Qt::SolidPattern);
    QPen pen;
    pen.setBrush(brushLine);
    pen.setStyle(Qt::SolidLine);
    pen.setWidth(3);
    QGraphicsLineItem* item = scene->addLine(x, y, x2, y2, pen);
    lines.push_back(item);
}

void Form::deleteEllipse(QGraphicsEllipseItem* item) {
    for (int j = 0; j < ellipses.size(); j++) {
        if (item == ellipses[j]) {
            int ix = item->rect().x() + 5;
            int iy = item->rect().y() + 5;
            ellipses.remove(j);
            scene->removeItem(item);
            ellipse1 = NULL;

            QVector<QGraphicsLineItem*> deleteItems;
            for (int k = 0; k < lines.size(); k++) {
                QLineF qline = lines[k]->line();
                if (((qline.x1() == ix) && (qline.y1() == iy)) ||
                        ((qline.x2() == ix) && (qline.y2() == iy))) {
                    deleteItems.push_back(lines[k]);
                }
            }
            foreach(QGraphicsLineItem* it, deleteItems) {
                deleteLine(it);
            }
            break;
        }
    }
}

void Form::deleteLine(QGraphicsLineItem* item) {
    for (int j = 0; j < lines.size(); j++) {
        if (item == lines[j]) {
            lines.remove(j);
            scene->removeItem(item);
            if (ellipse1 != NULL) {
                setEllipseAsNonActive(ellipse1);
            }
            break;
        }
    }
}

void Form::setEllipseAsActive(QGraphicsEllipseItem* item) {
    QBrush brush;
    brush.setColor(Qt::green);
    brush.setStyle(Qt::SolidPattern);
    item->setBrush(brush);
    ellipse1 = item;
}

void Form::setEllipseAsNonActive(QGraphicsEllipseItem* item) {
    QBrush brush;
    brush.setColor(Qt::red);
    brush.setStyle(Qt::SolidPattern);
    item->setBrush(brush);
    ellipse1 = NULL;
}

void Form::mouseMoveEvent(QMouseEvent*/* e*/) {
//    int x = e->x() - widget.graphicsView->x();
//    int y = e->y() - widget.graphicsView->y();
//    x = getX(x);
//    y = getY(y);
//    statusBar()->showMessage(QString("%1 - %2").arg(x).arg(y));
}

void Form::solve() {
//    statusBar()->showMessage(QString("ellipses: %1, lines: %2").arg(ellipses.size()).arg(lines.size()), 10000);
    const int SIZE = ellipses.size();
    State Matrix[SIZE][SIZE];
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            Matrix[i][j] = NONE;
        }
    }
    int ex, ey, e1, e2, lx1, lx2, ly1, ly2;
    for (int i = 0; i < lines.size(); i++) {
        lx1 = lines[i]->line().x1();
        lx2 = lines[i]->line().x2();
        ly1 = lines[i]->line().y1();
        ly2 = lines[i]->line().y2();
        e1 = -1, e2 = -1;
        for (int j = 0; j < ellipses.size(); j++) {
            ex = ellipses[j]->rect().x();
            ey = ellipses[j]->rect().y();
            if ((ex == lx1) && (ey == ly1)) {
                e1 = j;
            }
            if ((ex == lx2) && (ey == ly2)) {
                e2 = j;
            }
            if ((e1 != -1) && (e2 != -1)) {
                Matrix[e1][e2] = EXIST;
                Matrix[e2][e1] = EXIST;
                break;
            }
        }
    }
}
