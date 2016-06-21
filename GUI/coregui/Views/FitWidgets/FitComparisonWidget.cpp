// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/FitWidgets/FitComparisonWidget.cpp
//! @brief     Implements class FitComparisonWidget
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "FitComparisonWidget.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QDebug>

FitComparisonWidget::FitComparisonWidget(QWidget *parent)
    : SessionItemWidget(parent)
{
    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(new QLabel("xxx"));

    setLayout(layout);
}

void FitComparisonWidget::setItem(SessionItem *item)
{
    Q_UNUSED(item);

}
