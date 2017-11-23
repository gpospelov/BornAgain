// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/PropertyEditor/ComponentEditor.cpp
//! @brief     Implements ComponentEditor class
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "ComponentEditor.h"
#include "ComponentView.h"
#include "ComponentTreeView.h"
#include "ComponentFlatView.h"
#include <QGroupBox>
#include <QBoxLayout>

ComponentEditor::ComponentEditor(EditorType editorType)
    : m_type(editorType)
    , m_componentView(nullptr)
{
    m_componentView = createComponentView();

    auto mainLayout = new QVBoxLayout;
    mainLayout->setMargin(0);
    mainLayout->setSpacing(0);

    if (m_type.testFlag(GroupLayout)) {
        auto box = new QGroupBox("Title");
        auto boxlayout = new QVBoxLayout;

        boxlayout->addWidget(m_componentView);
        box->setLayout(boxlayout);

        mainLayout->addWidget(box);
    } else {
        mainLayout->addWidget(m_componentView);
    }

    setLayout(mainLayout);
}

void ComponentEditor::setItem(SessionItem* item)
{
    m_componentView->setItem(item);
}

void ComponentEditor::clearEditor()
{
    m_componentView->clearEditor();
}

ComponentView* ComponentEditor::createComponentView()
{
    ComponentView* result(nullptr);

    if (m_type.testFlag(Tree)) {
        auto view = new ComponentTreeView;
        view->setShowHeader(m_type.testFlag(T_Header));
        view->setShowRootItem(m_type.testFlag(T_Root));

        result = view;
    } else {
        auto view = new ComponentFlatView;
        result = view;
    }

    return result;
}
