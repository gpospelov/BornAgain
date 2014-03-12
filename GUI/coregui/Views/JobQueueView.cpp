#include "JobQueueView.h"
#include "JobQueueModel.h"
#include "JobQueueItem.h"
#include "JobSelectorWidget.h"
#include "JobOutputDataWidget.h"

#include "minisplitter.h"

#include <QGridLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QListView>
#include <QTreeView>
#include <QTableView>
#include <QPushButton>
#include <QDebug>
#include <QDockWidget>
#include <QSplitter>



class QStandardItemModel;


JobQueueView::JobQueueView(QWidget *parent)
    : QWidget(parent)
    , m_jobQueueModel(new JobQueueModel())
    , m_splitter(new Manhattan::MiniSplitter(this))
    , m_jobSelector(new JobSelectorWidget(m_jobQueueModel, this))
    , m_jobOutputData(new JobOutputDataWidget(this))
//    , m_button1(new QPushButton("Run"))
//    , m_button2(new QPushButton("Submit"))
//    , m_saveButton(new QPushButton("Save"))
//    , m_listView(new QListView(this))
{

    setObjectName("JobQueueView");


    m_jobQueueModel->addJob(new JobQueueItem("job1"));
    m_jobQueueModel->addJob(new JobQueueItem("job2"));
    m_jobQueueModel->addJob(new JobQueueItem("job3"));


//    //
//    QHBoxLayout *buttonsLayout = new QHBoxLayout;
//    buttonsLayout->addWidget(m_button1);
//    buttonsLayout->addWidget(m_button2);
//    buttonsLayout->addWidget(m_saveButton);
//    buttonsLayout->addStretch(1);

//    QGridLayout *gridLayout = new QGridLayout;
//    gridLayout->addWidget(m_listView, 0, 0);
////    gridLayout->addWidget(m_listView2, 1, 0);
////    gridLayout->addWidget(m_treeView, 0, 1);
////    gridLayout->addWidget(m_tableView, 1, 1);

//    QVBoxLayout *mainLayout = new QVBoxLayout;
//    mainLayout->addLayout(buttonsLayout);
//    mainLayout->addLayout(gridLayout);

//    setLayout(mainLayout);

//    m_listView->setDragEnabled(true);
//    m_listView->setAcceptDrops(true);
//    m_listView->setModel(m_jobQueueModel);
//    m_listView->setDefaultDropAction(Qt::MoveAction);


//    //m_jobQueueModel->save("tmp.xml");
//    m_jobQueueModel->load("model.xml");

//    //m_jobQueueModel->save("tmp2.xml");

//    connect(m_saveButton, SIGNAL(clicked()), this, SLOT(save()));


//    m_splitter = new QSplitter(this);


//    m_jobSelector = new JobSelectorWidget(this);
//    m_jobOutputData = new JobOutputDataWidget(this);
    m_splitter->addWidget(m_jobSelector);
    m_splitter->addWidget(m_jobOutputData);


    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->setMargin(0);
    mainLayout->setSpacing(0);
    mainLayout->addWidget(m_splitter);
    setLayout(mainLayout);


//    initSubWindows();

//    QList<QAbstractItemView*> frames =
//                    m_jobSelector->findChildren<QAbstractItemView*>();
//            for (int i = 0 ; i< frames.count(); ++i)
//                frames[i]->setFrameStyle(QFrame::NoFrame);




}


//void JobQueueView::initSubWindows()
//{

//}


//void JobQueueView::initSubWindows()
//{
//    m_subWindows.resize(NumberOfSubWindows);
//    m_dockWidgets.resize(NumberOfSubWindows);

//    m_subWindows[JobSelectorWindow] = JobQueueWidgets::createJobSelectorWidget(this);
//    m_subWindows[JobPropertiesWindow] = JobQueueWidgets::createJobPropertiesWidget(this);
//    m_subWindows[JobOutputDataWindow] = JobQueueWidgets::createJobOutputDataWidget(this);

//    for (int i = 0; i < NumberOfSubWindows; i++) {
//        QWidget *subWindow = m_subWindows[i];
//        m_dockWidgets[i] = addDockForWidget(subWindow);

//        QList<QAbstractItemView*> frames =
//                subWindow->findChildren<QAbstractItemView*>();
//        for (int i = 0 ; i< frames.count(); ++i)
//            frames[i]->setFrameStyle(QFrame::NoFrame);


//    }

//    addDockWidget(Qt::LeftDockWidgetArea, m_dockWidgets[JobSelectorWindow]);
//    addDockWidget(Qt::LeftDockWidgetArea, m_dockWidgets[JobPropertiesWindow]);
//    addDockWidget(Qt::RightDockWidgetArea, m_dockWidgets[JobOutputDataWindow]);

//    foreach (QDockWidget *dockWidget, m_dockWidgets)
//        dockWidget->show();

//}



//QDockWidget *JobQueueView::addDockForWidget(QWidget *widget)
//{
//    QDockWidget *result = new QDockWidget(widget->windowTitle(), this);
//    result->setWidget(widget);
////    dockWidget->setObjectName(widget->objectName() + QLatin1String("DockWidget"));
//    result->setFeatures(QDockWidget::DockWidgetMovable);
//    return result;
//}



void JobQueueView::save()
{
    qDebug() << "JobQueueView::save() -> ";
    m_jobQueueModel->save("tmp2.xml");

}


