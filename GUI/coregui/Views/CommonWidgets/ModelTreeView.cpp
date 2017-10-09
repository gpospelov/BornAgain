// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/CommonWidgets/ModelTreeView.cpp
//! @brief     Implements class ModelTreeView
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2017
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   J. Burle, J. M. Fisher, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "ModelTreeView.h"
#include "SessionDecorationModel.h"
#include "SessionModel.h"
#include "GUIHelpers.h"
#include <QVBoxLayout>
#include <QTreeView>

ModelTreeView::ModelTreeView(QWidget* parent, SessionModel* model)
    : QWidget(parent)
    , m_tree(new QTreeView)
    , m_decorationProxy(new SessionDecorationModel(this, model))
    , m_is_expanded(false)
{
    if (!model)
        throw GUIHelpers::Error("ModelTreeView::ModelTreeView() -> Error. Nullptr as model.");

   setObjectName(model->getModelTag());

   auto layout = new QVBoxLayout;
   layout->setMargin(0);
   layout->setSpacing(0);
   layout->addWidget(m_tree);

   m_decorationProxy->setSessionModel(model);
   m_tree->setModel(m_decorationProxy);


   if (m_decorationProxy->rowCount(QModelIndex()) > 0)
       setExpanded(true);

   setLayout(layout);
}

void ModelTreeView::setItemDelegate(QAbstractItemDelegate* delegate)
{
    m_tree->setItemDelegate(delegate);
}

void ModelTreeView::toggleExpanded()
{
    setExpanded(!isExpanded());
}

void ModelTreeView::setExpanded(bool expanded)
{
    Q_ASSERT(m_tree);
    if (expanded) {
        m_tree->expandAll();
        m_tree->resizeColumnToContents(0);
        m_tree->resizeColumnToContents(1);
    } else {
        m_tree->collapseAll();
    }
    m_is_expanded = expanded;
}
