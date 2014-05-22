#ifndef INSTRUMENT_SELECTOR_WIDGET_H
#define INSTRUMENT_SELECTOR_WIDGET_H


#include <QWidget>
class SessionModel;
class QListView;
class QListWidget;
class QAction;


class InstrumentSelectorWidget : public QWidget
{
    Q_OBJECT

public:
    InstrumentSelectorWidget(SessionModel *model, QWidget *parent = 0);

    QSize sizeHint() const { return QSize(200, 600); }
    QSize minimumSizeHint() const { return QSize(128, 300); }

    void setInstrumentModel(SessionModel *model);

public slots:
    void onAddDefaultGISAS();

private:
    void initFromModel();

    SessionModel *m_instrumentModel;
    QListWidget *m_listWidget;
    QAction *m_addDefaultGisasAction;
};


#endif

