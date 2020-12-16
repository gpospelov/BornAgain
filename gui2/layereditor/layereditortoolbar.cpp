// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "gui2/layereditor/layereditortoolbar.h"
#include "gui2/layereditor/layereditoractions.h"
#include "gui2/mainwindow/styleutils.h"
#include <QAction>
#include <QMenu>
#include <QToolButton>

namespace gui2 {

LayerEditorToolBar::LayerEditorToolBar(LayerEditorActions* actions, QWidget* parent)
    : QToolBar(parent) {
    StyleUtils::SetToolBarStyleTextBesides(this);

    auto layer_menu = create_layer_menu(actions);

    auto add_layer_button = new QToolButton;
    add_layer_button->setText("Add");
    add_layer_button->setToolTip(
        "Adds a new single layer (default) or new layer-repeater after currently selected.\nIf "
        "nothing is selected, appends to the end. Click and hold to see possible choices.");
    add_layer_button->setPopupMode(QToolButton::MenuButtonPopup);
    add_layer_button->setIcon(QIcon(":/icons/plus-circle-outline.svg"));
    add_layer_button->setMenu(layer_menu);
    add_layer_button->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    addWidget(add_layer_button);
    m_toolbarWidgets.insert(std::pair<std::string, QWidget*>("Add", add_layer_button));
    connect(add_layer_button, &QToolButton::clicked,
            [layer_menu]() { layer_menu->defaultAction()->triggered(); });

    auto action = new QAction("Clone", this);
    action->setIcon(QIcon(":/icons/plus-circle-multiple-outline.svg"));
    action->setToolTip("Clones selected layer");
    connect(action, &QAction::triggered, actions, &LayerEditorActions::onClone);
    addAction(action);
    m_toolbarWidgets.insert(std::pair<std::string, QWidget*>("Clone", widgetForAction(action)));

    action = new QAction("Remove", this);
    action->setIcon(QIcon(":/icons/beaker-remove-outline.svg"));
    action->setToolTip("Removes selected layer");
    connect(action, &QAction::triggered, actions, &LayerEditorActions::onRemove);
    addAction(action);
    m_toolbarWidgets.insert(std::pair<std::string, QWidget*>("Remove", widgetForAction(action)));

    addSeparator();

    action = new QAction("Up", this);
    action->setIcon(QIcon(":/icons/arrow-up-circle-outline.svg"));
    action->setToolTip("Moves selected layer up");
    connect(action, &QAction::triggered, actions, &LayerEditorActions::onMoveUp);
    addAction(action);
    m_toolbarWidgets.insert(std::pair<std::string, QWidget*>("Up", widgetForAction(action)));

    action = new QAction("Down", this);
    action->setIcon(QIcon(":/icons/arrow-down-circle-outline.svg"));
    action->setToolTip("Moves selected layer down");
    connect(action, &QAction::triggered, actions, &LayerEditorActions::onMoveDown);
    addAction(action);
    m_toolbarWidgets.insert(std::pair<std::string, QWidget*>("Down", widgetForAction(action)));

    m_toolbarWidgets["Add"]->setEnabled(true);
    m_toolbarWidgets["Clone"]->setEnabled(true);
    m_toolbarWidgets["Remove"]->setEnabled(true);
    m_toolbarWidgets["Up"]->setEnabled(false);
    m_toolbarWidgets["Down"]->setEnabled(false);
}

//! Creates menu to add layer and layer-repeater.

QMenu* LayerEditorToolBar::create_layer_menu(LayerEditorActions* editor_actions) {
    auto result = new QMenu("Add", this);
    result->setToolTipsVisible(true);
    result->menuAction()->setToolTip("Adds a single layer or layer-repeater.");
    result->setIcon(QIcon(":/icons/plus-circle-outline.svg"));

    // add layer action
    auto action = result->addAction("Adds a single layer");
    action->setIcon(QIcon(":/icons/layers-outline.svg"));
    action->setToolTip("Adds a new layer after selected one");
    connect(action, &QAction::triggered, editor_actions, &LayerEditorActions::onAddLayer);
    result->setDefaultAction(action);

    // add layer repeater action
    action = result->addAction("Adds layer repeater");
    action->setIcon(QIcon(":/icons/layers-triple-outline.svg"));
    action->setToolTip("Adds a new layer-repeater after selected one.\n"
                       "Layer repeater allows to repeat it content (i.e. bi-layer) "
                       "certain amount of times");
    connect(action, &QAction::triggered, editor_actions, &LayerEditorActions::onAddMultiLayer);

    return result;
}

//! Handle the QToolButtons for their enabled state depending on what is selected
void LayerEditorToolBar::updateToolButtonStates(bool first_present, bool last_present) {
    m_toolbarWidgets["Add"]->setEnabled(true);
    m_toolbarWidgets["Clone"]->setEnabled(true);
    m_toolbarWidgets["Remove"]->setEnabled(true);
    m_toolbarWidgets["Up"]->setEnabled((!first_present) ? (true) : (false));
    m_toolbarWidgets["Down"]->setEnabled((!last_present) ? (true) : (false));
}

} // namespace gui2
