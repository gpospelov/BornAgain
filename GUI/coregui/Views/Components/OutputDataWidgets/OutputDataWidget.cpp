#include "OutputDataWidget.h"



OutputDataWidget::OutputDataWidget(QWidget *parent)
    : QWidget(parent)
{
    setMinimumSize(600, 600);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    setWindowTitle(QLatin1String("Job Properties"));
    setObjectName(QLatin1String("Job Properties"));
//    setStyleSheet("background-color:white;");
}
