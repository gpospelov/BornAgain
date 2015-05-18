
#include "DistributionDialog.h"

DistributionDialog::DistributionDialog(QWidget *parent)
    : QDialog(parent)
    , m_editor(new DistributionEditor)
{
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(m_editor);
    setLayout(layout);
    setAttribute(Qt::WA_DeleteOnClose, true);
    setMinimumSize(800, 600);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    this->show();
}

void DistributionDialog::setItem(ParameterizedItem *item)
{
    m_editor->setItem(item);
}
