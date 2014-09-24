#include "AdvModelTuningWidget.h"
#include "JobItem.h"
#include <QLabel>
#include <QVBoxLayout>

AdvModelTuningWidget::AdvModelTuningWidget(QWidget *parent)
    : QWidget(parent)
    , m_currentJobItem(0)
{
    setMinimumSize(128, 128);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    QVBoxLayout *mainLayout = new QVBoxLayout;

    m_label = new QLabel();

    mainLayout->addWidget(m_label);

    setLayout(mainLayout);

}

void AdvModelTuningWidget::setCurrentItem(JobItem *item)
{
    m_currentJobItem = item;
    m_label->setText(item->getName());
}
