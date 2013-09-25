/* 
 * File:   Form.h
 * Author: sova
 *
 */

#ifndef _FORM_H
#define	_FORM_H

#include "ui_Form.h"
#include <QMouseEvent>
#include <QVector>
#include <QGraphicsEllipseItem>
#include <QGraphicsLineItem>

class Form : public QMainWindow {
    Q_OBJECT
public:
    Form();
private:
    Ui::Form widget;
    void init();
    QGraphicsScene* scene;
    QVector<QGraphicsEllipseItem*> ellipses;
    QVector<QGraphicsLineItem*> lines;
    void mousePressEvent(QMouseEvent* e);
    void mouseMoveEvent(QMouseEvent* e);
    QGraphicsEllipseItem* ellipse1;
    int* Matrix;
    void drawEllipse(int x, int y);
    void drawLine(int x, int y, int x2, int y2);
    void deleteEllipse(QGraphicsEllipseItem* item);
    void deleteLine(QGraphicsLineItem* item);
    void setEllipseAsActive(QGraphicsEllipseItem* item);
    void setEllipseAsNonActive(QGraphicsEllipseItem* item);
    QGraphicsEllipseItem* findQGraphicsEllipseItem(int x, int y);
    QGraphicsLineItem* findQGraphicsLineItem(int x1, int y1, int x2, int y2);
    int getX(int x);
    int getY(int y);
    void nextStep(int step, QVector<int> path, QVector<int> possible);
private slots:
    void solve();
};

#endif	/* _FORM_H */
