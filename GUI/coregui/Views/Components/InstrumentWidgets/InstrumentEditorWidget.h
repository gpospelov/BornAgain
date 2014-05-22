#ifndef INSTRUMENT_EDITOR_WIDGET_H
#define INSTRUMENT_EDITOR_WIDGET_H


#include <QWidget>
class SessionModel;

class InstrumentEditorWidget : public QWidget
{
    Q_OBJECT

public:
    InstrumentEditorWidget(SessionModel *model, QWidget *parent = 0);
    QSize sizeHint() const { return QSize(600, 600); }

private:
    SessionModel *m_instrumentModel;
};

#endif
