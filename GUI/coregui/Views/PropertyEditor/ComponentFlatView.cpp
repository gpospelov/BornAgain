// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/PropertyEditor/ComponentFlatView.cpp
//! @brief     Implements class ComponentFlatView
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "ComponentFlatView.h"
#include "ComponentUtils.h"
#include "PropertyEditorFactory.h"
#include "SessionItem.h"
#include "SessionModel.h"
#include "LayoutUtils.h"
#include <QLabel>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QDataWidgetMapper>

ComponentFlatView::ComponentFlatView(QWidget* parent)
    : QWidget(parent)
    , m_mainLayout(new QVBoxLayout)
    , m_gridLayout(nullptr)
{
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    m_mainLayout->setMargin(10);
    m_mainLayout->setSpacing(0);

    initGridLayout();

    setLayout(m_mainLayout);
}

void ComponentFlatView::addItemProperties(SessionItem* item)
{
    Q_ASSERT(item);

    clearLayout();

    int nrow(0);
    for (auto child : ComponentUtils::componentItems(*item)) {
        auto editor = PropertyEditorFactory::CreateEditor(*child);
        if (!editor)
            continue;

        auto label = new QLabel(child->displayName());

        label->setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed));
        m_gridLayout->addWidget(label, nrow, 0);
        m_gridLayout->addWidget(editor, nrow, 1);

        auto mapper = new QDataWidgetMapper(this);
        mapper->setModel(child->model());
        mapper->setRootIndex(child->parent()->index()); // item might be != child->parent()
        mapper->setCurrentModelIndex(child->index());
        mapper->addMapping(label, 0);
        mapper->addMapping(editor, 1);
        mapper->toFirst();

        ++nrow;
    }
}

void ComponentFlatView::clearLayout()
{
    Q_ASSERT(m_gridLayout);
    LayoutUtils::clearLayout(m_gridLayout);
//    initGridLayout();
//    for(int idx = 0; idx < m_gridLayout->count(); ++idx) {
//        auto layoutItem = m_gridLayout->takeAt(idx);
//        delete layoutItem->widget();
//        delete layoutItem;
    //    }
}

void ComponentFlatView::initGridLayout()
{
    delete m_gridLayout;
    m_gridLayout = new QGridLayout;
    m_gridLayout->setSpacing(6);
    m_mainLayout->addLayout(m_gridLayout);
    m_mainLayout->addStretch(1);
}
