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
{
    setObjectName("JobQueueView");

    m_jobQueueModel->addJob(new JobQueueItem("job1"));
    m_jobQueueModel->addJob(new JobQueueItem("job2"));
    m_jobQueueModel->addJob(new JobQueueItem("job3"));

    m_splitter->addWidget(m_jobSelector);
    m_splitter->addWidget(m_jobOutputData);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->setMargin(0);
    mainLayout->setSpacing(0);
    mainLayout->addWidget(m_splitter);
    setLayout(mainLayout);


//    connect(
//        m_jobQueueModel->selectionModel(),

//    );

}



