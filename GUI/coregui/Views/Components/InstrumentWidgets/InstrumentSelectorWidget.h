#ifndef INSTRUMENT_SELECTOR_WIDGET_H
#define INSTRUMENT_SELECTOR_WIDGET_H


#include <QWidget>
class SessionModel;
class QListView;

class InstrumentSelectorWidget : public QWidget
{
    Q_OBJECT

public:
    InstrumentSelectorWidget(SessionModel *model, QWidget *parent = 0);

    QSize sizeHint() const { return QSize(158, 600); }
    QSize minimumSizeHint() const { return QSize(64, 300); }

private:
    SessionModel *m_instrumentModel;
    QListView *m_listView;
};


#endif

