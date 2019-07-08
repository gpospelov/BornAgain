// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/ImportDataWidgets/RealDataSelectorToolBar.h
//! @brief     Defines class RealDataSelectorToolBar
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "RealDataSelectorHBar.h"

namespace {
const int toolbar_icon_size = 32;
}

RealDataSelectorHBar::RealDataSelectorHBar(RealDataSelectorActions* actions, QWidget* parent)
    : QToolBar(parent)
    , m_dropDownMenuAction(nullptr)
{
    setIconSize(QSize(toolbar_icon_size, toolbar_icon_size));
    setProperty("_q_custom_style_disabled", QVariant(true));

    m_dropDownMenuAction = new QAction(QStringLiteral("Add new material"), parent);
    m_dropDownMenuAction->setIcon(QIcon(":/images/toolbar32dark_newitem.svg"));
    m_dropDownMenuAction->setToolTip(QStringLiteral("Drop down menu with additional actions to import/modify datasets"));
    connect(m_dropDownMenuAction, &QAction::triggered,
            this, &RealDataSelectorHBar::onDropDownMenuAction);
    addAction(m_dropDownMenuAction);

}

void RealDataSelectorHBar::onDropDownMenuAction()
{

}
