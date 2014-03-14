#ifndef JOBOUTPUTDATAWIDGET_H
#define JOBOUTPUTDATAWIDGET_H

#include <QWidget>

class OutputDataWidget;

class QToolBar;


class JobOutputDataWidget : public QWidget
{
    Q_OBJECT
public:
    explicit JobOutputDataWidget(QWidget *parent = 0);

private:
    OutputDataWidget *m_outputDataWidget;
};


#endif
