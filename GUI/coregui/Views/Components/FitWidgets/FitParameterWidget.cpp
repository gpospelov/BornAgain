#include "FitParameterWidget.h"
#include <QDebug>
#include <QVBoxLayout>



FitParameterWidget::FitParameterWidget(FitModel *fitModel, QWidget *parent)
    : QWidget(parent)
    , m_fitModel(fitModel)
{

    QColor bgColor(255,255,255,255);
    QPalette palette;
    palette.setColor(QPalette::Background, bgColor);
    setAutoFillBackground(true);
    setPalette(palette);


    if(m_fitModel)
    {
        ParameterizedItem *old_item = m_fitModel->itemForIndex(m_fitModel->index(0,0, QModelIndex()));
        qDebug() << "FitModel: " << old_item;
    }

    QVBoxLayout *vlayout = new QVBoxLayout(this);
    vlayout->setMargin(0);
    vlayout->setSpacing(0);
    //vlayout->addWidget(m_treeView);
    //vlayout->addStretch();
    this->setLayout(vlayout);


}
