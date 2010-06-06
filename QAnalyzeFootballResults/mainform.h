/* 
 * File:   mainform.h
 * Author: valera
 *
 * Created on 5 Июнь 2010 г., 0:33
 */

#ifndef _MAINFORM_H
#define	_MAINFORM_H

#include "ui_mainform.h"

class mainform : public QMainWindow {
    Q_OBJECT
public:
    mainform();
    virtual ~mainform();
private:
    Ui::mainform widget;
};

#endif	/* _MAINFORM_H */
