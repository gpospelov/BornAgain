#include "JobOutputDataWidget.h"
#include "OutputDataWidget.h"
#include <QVBoxLayout>
#include <QPushButton>
#include "styledbar.h"

JobOutputDataWidget::JobOutputDataWidget(QWidget *parent)
    : QWidget(parent)
    , m_outputDataWidget(new OutputDataWidget(this))
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
//    QVBoxLayout *layout = new QHBoxLayout(bar);
//    layout->setMargin(0);
//    layout->setSpacing(0);

    mainLayout->addWidget(bar);
    mainLayout->addWidget(m_outputDataWidget);


    setLayout(mainLayout);


}


