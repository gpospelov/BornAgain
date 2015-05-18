
#include "DistributionDialog.h"


// FIXME Take care of "QPainter::fontMetrics: Painter not active" warning

// FIXME Implement tooltip for an icon which calls DistributionDialog

// Implement "close" button for Right Bottom corner of the distribution dialog


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
