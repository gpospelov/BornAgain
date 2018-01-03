// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/PropertyEditor/ComponentTreeActions.cpp
//! @brief     Implements class ComponentTreeActions
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "ComponentTreeActions.h"
#include "SessionItem.h"
#include "item_constants.h"
#include <QMenu>
#include <QAction>
#include <QSignalMapper>

ComponentTreeActions::ComponentTreeActions(QObject* parent)
    : QObject(parent)
{
}

//! Creates right-mouse-click context menu on top of ComponentTreeView
//! which will allow user to switch between scientific notation and the notation
//! with specifid number of decimals.

void ComponentTreeActions::onCustomContextMenuRequested(const QPoint& point, SessionItem& item)
{
    bool sc_editor = item.editorType() == Constants::ScientificEditorType;

    std::unique_ptr<QSignalMapper> mapper(new QSignalMapper);

    QMenu menu;
    QAction* scientificAction = menu.addAction("Scientific presentation");
    scientificAction->setCheckable(true);
    auto doubleMenu = menu.addMenu("Double presentation");

    // To select scientific notation
    scientificAction->setChecked(sc_editor);
    connect(scientificAction, &QAction::triggered, [&]()
    {
        if (scientificAction->isChecked())
            item.setEditorType(Constants::ScientificEditorType);
        else
            item.setEditorType(Constants::DefaultEditorType);
    });

    // to select number of decimals
    const int nmaxdigits = 8;
    for (int i=1; i<=nmaxdigits; ++i) {
        auto action = doubleMenu->addAction(QString("%1 digits").arg(i));
        if (!sc_editor && item.decimals() == i)
            action->setChecked(true);
        connect(action, SIGNAL(triggered()), mapper.get(), SLOT(map()));
        mapper->setMapping(action, i);
    }

    connect(mapper.get(),  static_cast<void (QSignalMapper::*)(int)>(&QSignalMapper::mapped),
            [&](int decimals)
    {
        item.setEditorType(Constants::DefaultEditorType);
        item.setDecimals(decimals);
    });

    menu.exec(point);
}

