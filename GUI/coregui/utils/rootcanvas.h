#ifndef ROOTCANVAS_H
#define ROOTCANVAS_H

#include <QWidget>

class QObject;
class QEvent;
class TQtWidget;
class QPoint;
class QStatusBar;
class TObject;
class TCanvas;
class QLabel;



// ----------------------------------------------------------------------------
// Handles right mouse events
// ----------------------------------------------------------------------------
class RCEventHandler : public QObject
{
Q_OBJECT
public:
    explicit RCEventHandler(QObject *parent = 0) : QObject(parent) {}

protected:
    bool eventFilter(QObject *obj, QEvent *event);

signals:
    void send_rightButtonClicked(const QPoint &p);

};


// ----------------------------------------------------------------------------
// Wrapper around root canvas widget
// ----------------------------------------------------------------------------
class RootCanvas : public QWidget
{
    Q_OBJECT

public:
    explicit RootCanvas(QWidget *parent = 0);
    virtual ~RootCanvas(){}

    void cd();
    void Update();

public slots:
//    void rightButtonClicked(const QPoint &pos);
    void ShowContextMenu(const QPoint& pos);
    void CanvasEvent(TObject *obj,unsigned int event,TCanvas *);


private:
//    bool eventFilter(QObject *, QEvent *);

    TQtWidget *m_qtroot_widget;
    //QStatusBar *m_status_bar;
    QLabel *m_status_bar;

    bool m_show_info;

};




#endif // ROOTCANVAS_H
