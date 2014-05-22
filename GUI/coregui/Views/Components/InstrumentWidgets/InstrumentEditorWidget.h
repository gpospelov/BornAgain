#ifndef INSTRUMENT_EDITOR_WIDGET_H
#define INSTRUMENT_EDITOR_WIDGET_H


#include <QWidget>
#include <QLabel>

class ParameterizedItem;

class InstrumentEditorWidget : public QWidget
{
    Q_OBJECT

public:
    InstrumentEditorWidget(QWidget *parent = 0);
    QSize sizeHint() const { return QSize(600, 600); }

    void setInstrumentItem(ParameterizedItem *instrument);

private:
    QLabel *m_label;
};

#endif
