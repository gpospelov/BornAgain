#include "rootcanvas.h"

/*

#include "TQtWidget.h"
#include "TObject.h"
#include "TCanvas.h"

#include <QEvent>
#include <QMenu>
#include <QMouseEvent>
#include <QVBoxLayout>
#include <QStatusBar>
#include <QLabel>

#include <iostream>


bool RCEventHandler::eventFilter(QObject *obj, QEvent *event)
{
    // given hadnler doesn nothing for right mouse button event simply passing it to parent widget
    if (event->type() == QEvent::ContextMenu) {
        QMouseEvent *mouseEvent = static_cast<QMouseEvent*> (event);
        send_rightButtonClicked(mouseEvent->globalPos());
        return true;
    } else {
        return QObject::eventFilter(obj, event);
    }
}


RootCanvas::RootCanvas(QWidget *parent)
    : QWidget(parent)
    , m_show_info(false)
{

    setMinimumSize(512, 512);

    m_qtroot_widget = new TQtWidget(this,"qt-canvas");
    m_qtroot_widget->EnableSignalEvents(kMousePressEvent);
    m_qtroot_widget->EnableSignalEvents(kMouseMoveEvent);
    //m_qtroot_widget->setAttribute(Qt::WA_TransparentForMouseEvents);

    //m_status_bar = new QStatusBar(this);
    //    m_status_bar->setSizeGripEnabled(false);
//    m_status_bar->showMessage("HelloWorld");
    m_status_bar = new QLabel(this);
    m_status_bar->setVisible(m_show_info);
    m_status_bar->setText("Hello World");

//    QLabel label;

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(m_qtroot_widget);
    layout->addWidget(m_status_bar);
    setLayout(layout);

//    installEventFilter(this);

    //RCEventHandler *evHandler = new RCEventHandler(this);
    // installing handler to root widget to skip right mouse button events
    //m_qtroot_widget->installEventFilter(evHandler);
    //connect(evHandler, SIGNAL(send_rightButtonClicked(const QPoint&)), this, SLOT(rightButtonClicked(const QPoint&)));
    //connect(evHandler, SIGNAL(send_rightButtonClicked(const QPoint&)), this, SLOT(ShowContextMenu(const QPoint&)));

    setContextMenuPolicy(Qt::CustomContextMenu);
    m_qtroot_widget->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(this, SIGNAL(customContextMenuRequested(const QPoint&)), this, SLOT(ShowContextMenu(const QPoint&)));
    connect(m_qtroot_widget, SIGNAL(customContextMenuRequested(const QPoint&)), this, SLOT(ShowContextMenu(const QPoint&)));

    connect(m_qtroot_widget, SIGNAL(RootEventProcessed(TObject *,unsigned int, TCanvas *)), this,SLOT(CanvasEvent(TObject *, unsigned int, TCanvas *)));

}


// show context menu for root canvas
void RootCanvas::ShowContextMenu(const QPoint& pos)
{
    QPoint globalPos = this->mapToGlobal(pos);

    QString ResetActionName("Reset");
    QString StatusBarActionName("Show status bar");
    if(m_show_info) StatusBarActionName = "Hide status bar";

    QMenu myMenu;
    myMenu.addAction(ResetActionName);
    myMenu.addAction(StatusBarActionName);

    QAction* selectedItem = myMenu.exec(globalPos);
    if (selectedItem) {
        if( selectedItem->text() == ResetActionName ) {
            std::cout << "AAA " << "reset was choosen" << std::endl;
        } else if( selectedItem->text() == StatusBarActionName ) {
            std::cout << "AAA " << "hide status bar was" << std::endl;
            m_show_info =! m_show_info;
            m_status_bar->setVisible(m_show_info);
        }
    }
    // otherwise nothing was choosen

}


// simple cd inside ROOT canvas
void RootCanvas::cd()
{
    m_qtroot_widget->GetCanvas()->cd();
}

// redraw ROOT canvas
void RootCanvas::Update()
{
    m_qtroot_widget->GetCanvas()->Modified();
    m_qtroot_widget->GetCanvas()->Update();
}


// print ROOT canvas object info in status bar
void RootCanvas::CanvasEvent(TObject *object,unsigned int event,TCanvas *canvas)
{
    assert(object);
    (void)event;
    (void)canvas;
    TQtWidget *tipped = (TQtWidget *)sender();
    const char *objectInfo = object->GetObjectInfo( tipped->GetEventX(),tipped->GetEventY() );
    //m_status_bar->showMessage(objectInfo);
    m_status_bar->setText(objectInfo);
 }


//void RootCanvas::rightButtonClicked(const QPoint &pos)
//{
//   (void)pos;
//}


//bool RootCanvas::eventFilter(QObject *obj, QEvent *event)
//{
//    if(event->type() == QEvent::ContextMenu) {
//        QMouseEvent *mouseEvent = static_cast<QMouseEvent*> (event);
//        QMenu *menu = new QMenu(this);

//        menu->addAction(new QAction("New",this));
//        menu->addAction(new QAction("Edit",this));
//        menu->addAction(new QAction("Delete",this));
//        menu->exec(mouseEvent->globalPos());
//        //menu->exec(mouseEvent->pos());
//        return false;
//    } else {
//        return QWidget::eventFilter(obj, event);
//    }
//}


*/
