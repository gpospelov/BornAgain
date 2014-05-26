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
class QToolBar;

namespace Manhattan{
    class StyledBar;
}

class InstrumentView2 : public QWidget
{
    Q_OBJECT

public:
    InstrumentView2(SessionModel *model, QWidget *parent = 0);

//    void setInstrumentModel(SessionModel *model);

public slots:
    void onSelectionChanged(const QItemSelection&, const QItemSelection&);
    void onAddInstrument();
    void onRemoveInstrument();
//    void rowsRemoved(const QModelIndex &parent, int first, int last);
    void onRowsAboutToBeRemoved(QModelIndex,int,int);

private:
    void createActions();

    SessionModel *m_instrumentModel;
//    QSplitter *m_splitter;
//    Manhattan::StyledBar *m_toolBar;
    QToolBar *m_toolBar;
    InstrumentSelectorWidget *m_instrumentSelector;
//    InstrumentEditorWidget *m_instrumentEditor;

    QStackedWidget *m_stackWidget;

    QMap<ParameterizedItem *, InstrumentEditorWidget *> m_instrumentToEditor;
    QAction *m_addInstrumentAction;
    QAction *m_removeInstrumentAction;

};


#endif
