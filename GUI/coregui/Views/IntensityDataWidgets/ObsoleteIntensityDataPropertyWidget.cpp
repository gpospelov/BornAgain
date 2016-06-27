// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/IntensityDataWidgets/ObsoleteIntensityDataPropertyWidget.cpp
//! @brief     Implements class ObsoleteIntensityDataPropertyWidget
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "ObsoleteIntensityDataPropertyWidget.h"
#include "JobModel.h"
#include "IntensityDataItem.h"
#include "ComponentEditor.h"
#include <QVBoxLayout>
#include <QDebug>

ObsoleteIntensityDataPropertyWidget::ObsoleteIntensityDataPropertyWidget(QWidget *parent)
    : QWidget(parent)
    , m_currentItem(0)
    , m_componentEditor(0)
{
    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
    setWindowTitle(QLatin1String("Intensity Data Properties"));
    setObjectName(QLatin1String("Intensity Data Properties"));

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->setMargin(0);
    mainLayout->setSpacing(0);

    m_componentEditor = new ComponentEditor();

    mainLayout->addWidget(m_componentEditor);

    setLayout(mainLayout);
}

void ObsoleteIntensityDataPropertyWidget::setItem(IntensityDataItem *jobItem)
{
    m_componentEditor->setItem(jobItem);
}
