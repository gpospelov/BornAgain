
#include "DistributionDialog.h"

// FIXME Fix layout of DistributionEditor
//       1) make a gap around close button
//       2) make "close" button not sensitive to "Enter" event
//       3) QLabel with [x,y] - should be shifted a bit
//       4) Change behavior of QDialog, when shown, MainApplication is gray and not active
//       5) Change title of QDialog from BornAgain to Select Distribution

// FIXME Fix title of groupBox in DistributionEditor

// FIXME Take care of "QPainter::fontMetrics: Painter not active" warning
//       Still there
//       may be this --> http://stackoverflow.com/questions/17704597/qpainterbegin-widget-painting-can-only-begin-as-a-result-of-a-paintevent

// Provide y-Axis caption -> "probability" instead of "y"
// Provide x-Axis caption -> name of group instead of name of the distribution

// Fix: When click on "Azimuthal angle" -> see nothing

// create "i" Icon using inkscape
// try to place it in the right corner of QGroupBox



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
