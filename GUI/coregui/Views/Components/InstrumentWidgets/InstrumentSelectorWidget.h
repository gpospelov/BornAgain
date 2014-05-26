#ifndef INSTRUMENT_SELECTOR_WIDGET_H
#define INSTRUMENT_SELECTOR_WIDGET_H


#include <QWidget>
class SessionModel;
class QListView;
class QAction;
class QItemSelectionModel;
class QItemSelection;

class InstrumentSelectorWidget : public QWidget
{
    Q_OBJECT

public:
    InstrumentSelectorWidget(SessionModel *model, QWidget *parent = 0);

    QSize sizeHint() const { return QSize(200, 600); }
    QSize minimumSizeHint() const { return QSize(128, 300); }

    void setInstrumentModel(SessionModel *model);

    QItemSelectionModel *getSelectionModel();

signals:
    void selectionChanged(const QItemSelection&, const QItemSelection&);

//public slots:
//    void onAddDefaultGISAS();

private:
    SessionModel *m_instrumentModel;
    QListView *m_listView;
//    QAction *m_addDefaultGisasAction;
};


#endif

