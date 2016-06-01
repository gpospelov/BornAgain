// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/ImportDataWidgets/RealDataEditorWidget.cpp
//! @brief     Declares class RealDataEditorWidget
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "RealDataEditorWidget.h"
#include "SessionItem.h"
#include <QVBoxLayout>
#include <QLabel>

RealDataEditorWidget::RealDataEditorWidget(QWidget *parent)
    : QWidget(parent)
    , m_label(new QLabel("xxx"))
{
    setMinimumSize(400, 400);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(m_label);
    setLayout(layout);
}

void RealDataEditorWidget::setItem(SessionItem *item)
{
    m_label->setText(item->displayName());
}
