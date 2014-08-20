#ifndef INSTRUMENTVIEW_H
#define INSTRUMENTVIEW_H

#include <QWidget>
#include <QString>
#include <QMap>
class InstrumentSelectorWidget;
class InstrumentEditorWidget;
class InstrumentModel;
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
    InstrumentView(InstrumentModel *model, QWidget *parent = 0);

public slots:
    void updateView();
    void resetView();
    void onSelectionChanged(const QItemSelection&, const QItemSelection&);
    void onAddInstrument();
    void onRemoveInstrument();
    void onRowsAboutToBeRemoved(QModelIndex,int,int);

private:
    void createActions();
    QString getNewInstrumentName(const QString &name);

    InstrumentModel *m_instrumentModel;
    QToolBar *m_toolBar;
    InstrumentSelectorWidget *m_instrumentSelector;
    QStackedWidget *m_stackWidget;
    QMap<ParameterizedItem *, InstrumentEditorWidget *> m_instrumentToEditor;
    QAction *m_addInstrumentAction;
    QAction *m_removeInstrumentAction;

    QMap<QString, int> m_name_to_copy;
};


#endif
