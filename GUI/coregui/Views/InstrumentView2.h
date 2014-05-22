#ifndef INSTRUMENTVIEW2_H
#define INSTRUMENTVIEW2_H

#include <QWidget>
class QSplitter;

class InstrumentSelectorWidget;
//class InstrumentEditorWidget;
class SessionModel;
class QListView;
class QStackedWidget;
class QMenu;
class QAction;

class InstrumentView2 : public QWidget
{
    Q_OBJECT

public:
    InstrumentView2(SessionModel *model, QWidget *parent = 0);

private:
    SessionModel *m_instrumentModel;
//    QSplitter *m_splitter;
    InstrumentSelectorWidget *m_instrumentSelector;
//    InstrumentEditorWidget *m_instrumentEditor;

    QListView *m_listView;
    QStackedWidget *m_stackWidget;

};


#endif
