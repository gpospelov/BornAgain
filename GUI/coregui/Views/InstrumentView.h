#ifndef INSTRUMENTVIEW_H
#define INSTRUMENTVIEW_H

#include <QWidget>
#include <QMap>
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

class InstrumentView : public QWidget
{
    Q_OBJECT

public:
    InstrumentView(SessionModel *model, QWidget *parent = 0);

public slots:
    void onSelectionChanged(const QItemSelection&, const QItemSelection&);
    void onAddInstrument();
    void onRemoveInstrument();
    void onRowsAboutToBeRemoved(QModelIndex,int,int);

private:
    void createActions();

    SessionModel *m_instrumentModel;
    QToolBar *m_toolBar;
    InstrumentSelectorWidget *m_instrumentSelector;
    QStackedWidget *m_stackWidget;
    QMap<ParameterizedItem *, InstrumentEditorWidget *> m_instrumentToEditor;
    QAction *m_addInstrumentAction;
    QAction *m_removeInstrumentAction;
};


#endif
