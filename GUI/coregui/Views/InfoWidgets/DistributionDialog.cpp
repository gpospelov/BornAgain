// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/InfoWidgets/DistributionDialog.cpp
//! @brief     Implements class DistributionDialog
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "DistributionDialog.h"
#include "DistributionEditor.h"
#include "ParameterizedItem.h"
#include <QHBoxLayout>
#include <QPushButton>

namespace
{
int minimumWidth_of_dialog = 800;
int minimumHeigth_of_dialog = 600;
}

DistributionDialog::DistributionDialog(QWidget *parent)
    : QDialog(parent), m_editor(new DistributionEditor)
{
    this->setWindowTitle("Select Distribution");
    QVBoxLayout *layout = new QVBoxLayout;
    QPushButton *button = new QPushButton("Close", this);
    connect(button, SIGNAL(clicked()), this, SLOT(close()));
    layout->addWidget(m_editor);
    layout->addWidget(button, 0, Qt::AlignBottom | Qt::AlignRight);
    layout->setContentsMargins(0, 0, 10, 10);
    setLayout(layout);
    setAttribute(Qt::WA_DeleteOnClose, true);
    setMinimumSize(minimumWidth_of_dialog, minimumHeigth_of_dialog);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    button->setAutoDefault(false);
    this->setModal(true);
}

void DistributionDialog::setItem(ParameterizedItem *item)
{
    m_editor->setItem(item);
}

void DistributionDialog::setNameOfEditor(const QString &name)
{
    m_editor->setNameOfEditor(name);
}
