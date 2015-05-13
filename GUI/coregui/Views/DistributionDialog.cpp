#include "DistributionDialog.h"


DistributionDialog::DistributionDialog(QWidget *parent)
    : QDialog(parent)
{
    QVBoxLayout *layout = new QVBoxLayout;
    DistributionEditor *editor = new DistributionEditor;
    layout->addWidget(editor);
    setLayout(layout);
    this->show();

}
