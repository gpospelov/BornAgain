#ifndef INSTRUMENTVIEW2_H
#define INSTRUMENTVIEW2_H

#include <QWidget>
#include <QMap>
class QSplitter;

class InstrumentSelectorWidget;
class InstrumentEditorWidget;
class SessionModel;
class QListView;
class QStackedWidget;
class QMenu;
class QAction;
class QItemSelection;
class ParameterizedItem;

class InstrumentView2 : public QWidget
{
    Q_OBJECT

public:
    InstrumentView2(SessionModel *model, QWidget *parent = 0);

//    void setInstrumentModel(SessionModel *model);

public slots:
    void onSelectionChanged(const QItemSelection&, const QItemSelection&);

private:
    SessionModel *m_instrumentModel;
//    QSplitter *m_splitter;
    InstrumentSelectorWidget *m_instrumentSelector;
//    InstrumentEditorWidget *m_instrumentEditor;

    QStackedWidget *m_stackWidget;

    QMap<ParameterizedItem *, InstrumentEditorWidget *> m_instrumentToEditor;
};


#endif
