// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/FitWidgets/FitParametersWidget.cpp
//! @brief     Implements class FitParametersWidget
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "FitParametersWidget.h"
#include <QTreeView>
#include <QVBoxLayout>

FitParametersWidget::FitParametersWidget(QWidget *parent)
    : QWidget(parent)
    , m_treeView(new QTreeView)
{
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(m_treeView);
    setLayout(layout);
}
