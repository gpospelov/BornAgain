// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/CommonWidgets/ModelListView.cpp
//! @brief     Implements class ModelListView
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2017
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   J. Burle, J. M. Fisher, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "ModelListView.h"
#include "SessionDecorationModel.h"
#include "SessionModel.h"
#include "GUIHelpers.h"
#include <QVBoxLayout>
#include <QListView>

ModelListView::ModelListView(QWidget* parent, SessionModel* model)
    : QWidget(parent)
    , m_listView(new QListView)
    , m_decorationProxy(new SessionDecorationModel(this, model))
{
    if (!model)
        throw GUIHelpers::Error("ModelListView::ModelListView() -> Error. Nullptr as model.");

   setObjectName(model->getModelTag());

   auto layout = new QVBoxLayout;
   layout->setMargin(0);
   layout->setSpacing(0);
   layout->addWidget(m_listView);

   m_decorationProxy->setSessionModel(model);
   m_listView->setModel(m_decorationProxy);

   setLayout(layout);
}
