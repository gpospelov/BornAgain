#include "RunFitWidget.h"
#include <QDebug>
#include <QVBoxLayout>



RunFitWidget::RunFitWidget(QWidget *parent)
    : QWidget(parent)
{

    QColor bgColor(255,255,255,255);
    QPalette palette;
    palette.setColor(QPalette::Background, bgColor);
    setAutoFillBackground(true);
    setPalette(palette);


    QVBoxLayout *vlayout = new QVBoxLayout(this);
    vlayout->setMargin(0);
    vlayout->setSpacing(0);
    //vlayout->addWidget(m_treeView);
    //vlayout->addStretch();
    this->setLayout(vlayout);

}
