// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/JobWidgets/RealDataPropertiesWidget.cpp
//! @brief     Implements class RealDataPropertiesWidget
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "RealDataPropertiesWidget.h"
#include "ComponentEditor.h"
#include "RealDataItem.h"
#include "SessionModel.h"
#include <QVBoxLayout>
#include <QLineEdit>
#include <QDataWidgetMapper>

RealDataPropertiesWidget::RealDataPropertiesWidget(QWidget *parent)
    : QWidget(parent)
    , m_propertyEditor(new ComponentEditor)
//    , m_propertyEditor2(new ComponentEditor)
    , m_dataNameMapper(new QDataWidgetMapper)
    , m_dataNameEdit(new QLineEdit)
{
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    setWindowTitle("RealDataPropertiesWidget");


    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->setMargin(0);
    mainLayout->setSpacing(0);
    mainLayout->setContentsMargins(0,0,0,0);
    mainLayout->addWidget(m_propertyEditor);
//    mainLayout->addWidget(m_propertyEditor2);
    mainLayout->addWidget(m_dataNameEdit);

    setLayout(mainLayout);
}

void RealDataPropertiesWidget::setItem(SessionItem *item)
{
    m_propertyEditor->setItem(item);
//    m_propertyEditor2->setItem(item);
    m_dataNameMapper->clearMapping();
    if(!item)
        return;


    m_dataNameMapper->setModel(item->model());
    m_dataNameMapper->setRootIndex(item->index());
    m_dataNameMapper->setCurrentModelIndex(item->getItem(SessionItem::P_NAME)->index());
//    m_dataNameMapper->addMapping(m_dataNameEdit, 1, "plainText");
    m_dataNameMapper->addMapping(m_dataNameEdit, 1);
    m_dataNameMapper->toFirst();
}


//m_textEditMapper->setRootIndex(m_fitModel->rootItem()->getItem("", m_row)->index());
//m_textEditMapper->setCurrentModelIndex(m_fitModel->rootItem()->getItem("", m_row)->getItem(FittingWorkspace::P_PARAMETERS)->index());
//m_textEditMapper->addMapping(m_textEdit, 1, "plainText");


