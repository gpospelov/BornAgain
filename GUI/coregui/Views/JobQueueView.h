#ifndef JOBQUEUEVIEW_H
#define JOBQUEUEVIEW_H

//#include <QMainWindow>
#include <QWidget>
#include <QVector>

class JobSelectorWidget;
class JobOutputDataWidget;

class QListView;
class QPushButton;
class JobQueueModel;
class QDockWidget;
class QSplitter;

class JobQueueView : public QWidget
{
    Q_OBJECT

public:
    enum SubWindows
    {
        JobSelectorWindow,
        JobPropertiesWindow,
        JobOutputDataWindow,
        NumberOfSubWindows
    };

    JobQueueView(QWidget *parent = 0);
    virtual ~JobQueueView() {}

public slots:

private slots:
    void save();

private:
//    void initSubWindows();
//    QDockWidget *addDockForWidget(QWidget *widget);

    JobQueueModel *m_jobQueueModel;
//    QPushButton *m_button1;
//    QPushButton *m_button2;
//    QPushButton *m_saveButton;
//    QListView *m_listView;


//    QVector<QWidget *> m_subWindows;
//    QVector<QDockWidget *> m_dockWidgets;

//    QWidget *m_subWindows[NumberOfSubWindows];
//    QDockWidget *m_dockWidgets[NumberOfSubWindows];

    QSplitter *m_splitter;
    JobSelectorWidget *m_jobSelector;
    JobOutputDataWidget *m_jobOutputData;


};

#endif // JOBQUEUEVIEW_H
