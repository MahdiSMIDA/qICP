#include "ccIcpDialog.h"
//Local
#include "ccGLWindow.h"
//qCC_db
#include <ccLog.h>
//Qt
#include <QEvent>
#include <QKeyEvent>
#include <QApplication>
#include <qmenu.h>
#include <qaction.h>
//system
#include <assert.h>
#include "ccStdPluginInterface.h"

ccIcpDialog::ccIcpDialog(QWidget* parent/*=0*/)
    : ccOverlayDialog(parent)
    , Ui::icpDialog()

{
    setupUi(this);
    //set background color
    QPalette p;
    p.setColor(backgroundRole(), QColor(240, 240, 240, 200));
    setPalette(p);
    setAutoFillBackground(true);
}


void ccIcpDialog::mousePressEvent(QMouseEvent *event) {
    m_nMouseClick_X_Coordinate = event->x();
    m_nMouseClick_Y_Coordinate = event->y();
}


void ccIcpDialog::mouseMoveEvent(QMouseEvent *event) {
    move(event->globalX()-m_nMouseClick_X_Coordinate,event->globalY()-m_nMouseClick_Y_Coordinate);
}

