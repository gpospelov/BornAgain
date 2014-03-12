#include "JobPropertiesWidget.h"


JobPropertiesWidget::JobPropertiesWidget(QWidget *parent)
    : QWidget(parent)
{
    setMinimumSize(128, 128);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    setWindowTitle(QLatin1String("Job Properties"));
    setObjectName(QLatin1String("Job Properties"));
//    setStyleSheet("background-color:white;");
}
