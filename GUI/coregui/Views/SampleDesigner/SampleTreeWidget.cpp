// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/SampleDesigner/SampleTreeWidget.cpp
//! @brief     Implements class SampleTreeWidget
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "SampleTreeWidget.h"
#include <QVBoxLayout>
#include <QTreeView>

SampleTreeWidget::SampleTreeWidget(QWidget* parent)
    : QWidget(parent)
    , m_treeView(new QTreeView)
{
    auto mainLayout = new QVBoxLayout;
    mainLayout->setMargin(0);
    mainLayout->setSpacing(0);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->addWidget(m_treeView);
    setLayout(mainLayout);
}

