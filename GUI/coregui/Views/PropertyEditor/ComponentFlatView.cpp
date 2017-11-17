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
#include <QLabel>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QDataWidgetMapper>

ComponentFlatView::ComponentFlatView(QWidget* parent)
    : QWidget(parent)
    , m_gridLayout(new QGridLayout)
{
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    auto layout = new QVBoxLayout;
    layout->setMargin(10);
    layout->setSpacing(0);

    m_gridLayout->setSpacing(6);
    layout->addLayout(m_gridLayout);
    layout->addStretch(1);

    setLayout(layout);
}

void ComponentFlatView::addItemProperties(SessionItem* item)
{
    Q_ASSERT(item);

    clearLayout();

    int nrow(0);
    for (auto child : ComponentUtils::componentItems(*item)) {
        auto editor = PropertyEditorFactory::CreateEditor(*child, this);
        if (!editor)
            continue;

        auto label = new QLabel(child->displayName(), this);
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
    for(int idx = 0; idx < m_gridLayout->count(); ++idx) {
        auto layoutItem = m_gridLayout->takeAt(idx);
        delete layoutItem->widget();
        delete layoutItem;
    }
}
