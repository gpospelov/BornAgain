
#include "DistributionDialog.h"

// FIXME Fix layout of DistributionEditor

// FIXME Fix title of groupBox in DistributionEditor

// FIXME Take care of "QPainter::fontMetrics: Painter not active" warning

// FIXME Implement tooltip for an icon which calls DistributionDialog

// FIXME Implement "close" button for Right Bottom corner of the distribution dialog

// FIXME Implement right mouse button -> "reset"

// FIXME unused variable pixHeight In member function 'QPixmap GroupBox::mergeSideBySide(const QPixmap&, QString)':

// FIXME try another icon (look http://glyphicons.com/ or similar)

DistributionDialog::DistributionDialog(QWidget *parent)
    : QDialog(parent)
    , m_editor(new DistributionEditor)
{
    QVBoxLayout *layout = new QVBoxLayout;
    QPushButton *button = new QPushButton("Close" , this);
    connect(button, SIGNAL(pressed()),this, SLOT(closeDialog()));
    layout->addWidget(m_editor);
    layout->addWidget(button,0, Qt::AlignBottom | Qt::AlignRight);
//    button->move(700, 500);
    layout->setContentsMargins(0,0,0,0);
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

void DistributionDialog::setNameOfEditor(QString name)
{
    m_editor->setNameOfEditor(name);
}

void DistributionDialog::closeDialog()
{
    this->close();
}
