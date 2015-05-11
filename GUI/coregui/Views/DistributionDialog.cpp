#include "DistributionDialog.h"


DistributionDialog::DistributionDialog(QWidget *parent)
    : QDialog(parent)
{
    QHBoxLayout *mainLayout;
    mainLayout->addWidget(new DistributionEditor);
    setLayout(mainLayout);
}
