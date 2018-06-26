#ifndef CC_ICP_DIALOG_HEADER
#define CC_ICP_DIALOG_HEADER

//Qt
#include <QDialog>
#include <QList>
#include <QAction>

//CC
#include <ccGLWindow.h>
#include <ccOverlayDialog.h>

//Local
#include "ui_icpDialog.h"


class ccIcpDialog:public ccOverlayDialog, public Ui::icpDialog
{
    Q_OBJECT

public:
    //! Default constructor
    explicit ccIcpDialog(QWidget* parent = 0);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

    int m_nMouseClick_X_Coordinate;
    int m_nMouseClick_Y_Coordinate;
};


#endif
