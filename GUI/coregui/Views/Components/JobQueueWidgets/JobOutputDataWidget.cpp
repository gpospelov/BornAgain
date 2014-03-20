#include "JobOutputDataWidget.h"
#include "JobQueueModel.h"
#include "OutputDataWidget.h"
#include <QVBoxLayout>
#include <QPushButton>
#include "styledbar.h"

JobOutputDataWidget::JobOutputDataWidget(JobQueueModel *model,QWidget *parent)
    : QWidget(parent)
    , m_jobQueueModel(model)
    , m_outputDataWidget(new OutputDataWidget(model, this))
{
    setMinimumSize(400, 400);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    setWindowTitle(QLatin1String("Job OutputData"));
    setObjectName(QLatin1String("Job OutputData"));
//    setStyleSheet("background-color:blue;");

//    addToolBar(m_toolBar);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->setMargin(0);
    mainLayout->setSpacing(0);

    Manhattan::StyledBar *bar = new Manhattan::StyledBar;
    mainLayout->addWidget(bar);
    mainLayout->addWidget(m_outputDataWidget);


    setLayout(mainLayout);


}


