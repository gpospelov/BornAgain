#include "DistributionDialog.h"


DistributionDialog::DistributionDialog(QWidget *parent)
    : QDialog(parent)
{
    QVBoxLayout *layout = new QVBoxLayout;
    DistributionEditor *editor = new DistributionEditor;
    layout->addWidget(editor,1);
    setLayout(layout);
    setAttribute(Qt::WA_DeleteOnClose, true);
//    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::ExpandFlag);
    this->show();

}
