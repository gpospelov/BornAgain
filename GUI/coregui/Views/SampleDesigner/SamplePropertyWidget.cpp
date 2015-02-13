// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/SampleDesigner/SamplePropertyWidget.cpp
//! @brief     Implements class IntensityDataPropertyWidget
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "SamplePropertyWidget.h"
#include "UniversalPropertyEditor.h"
#include <QVBoxLayout>
#include <QDebug>

SamplePropertyWidget::SamplePropertyWidget(QItemSelectionModel *selection_model, QWidget *parent)
    : QWidget(parent)
    , m_selection_model(selection_model)
{
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    setWindowTitle(QLatin1String("Property Editor"));
    setObjectName(QLatin1String("SamplePropertyWidget"));

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->setMargin(0);
    mainLayout->setSpacing(0);

    m_propertyEditor = new UniversalPropertyEditor(selection_model, this);

    //m_propertyEditor->setCreateGroupProperty(false);

    mainLayout->addWidget(m_propertyEditor);
    setLayout(mainLayout);
}
