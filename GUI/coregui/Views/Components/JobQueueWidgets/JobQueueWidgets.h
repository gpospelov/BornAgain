#ifndef JOBQUEUEWIDGETS_H
#define JOBQUEUEWIDGETS_H


#include <QWidget>
#include <QString>

class JobSelectorWidget : public QWidget
{
public:
    explicit JobSelectorWidget(QWidget *parent = 0) : QWidget(parent)
    {
        setMinimumSize(128, 128);
        setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        setWindowTitle(QLatin1String("Job Selector"));
        setObjectName(QLatin1String("Job Selector"));
        setStyleSheet("background-color:white;");
    }
};


class JobPropertiesWidget : public QWidget
{
public:
    explicit JobPropertiesWidget(QWidget *parent = 0) : QWidget(parent)
    {
        setMinimumSize(128, 128);
        setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        setWindowTitle(QLatin1String("Job Properties"));
        setObjectName(QLatin1String("Job Properties"));
        setStyleSheet("background-color:white;");
    }
};


class JobOutputDataWidget : public QWidget
{
public:
    explicit JobOutputDataWidget(QWidget *parent = 0) : QWidget(parent)
    {
        setMinimumSize(128, 128);
        setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        setWindowTitle(QLatin1String("Job OutputData"));
        setObjectName(QLatin1String("Job OutputData"));
        setStyleSheet("background-color:white;");
    }
};


class JobQueueWidgets
{
public:
    static JobSelectorWidget *createJobSelectorWidget(QWidget *parent);
    static JobPropertiesWidget *createJobPropertiesWidget(QWidget *parent);
    static JobOutputDataWidget *createJobOutputDataWidget(QWidget *parent);

};

#endif
