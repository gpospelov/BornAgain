// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/IntensityDataWidgets/IntensityDataPropertyWidget.cpp
//! @brief     Implements class IntensityDataPropertyWidget
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "IntensityDataPropertyWidget.h"
#include "JobModel.h"
#include "IntensityDataItem.h"
#include "ComponentEditor.h"
#include <QVBoxLayout>
#include <QDebug>

IntensityDataPropertyWidget::IntensityDataPropertyWidget(QWidget *parent)
    : QWidget(parent)
    , m_jobModel(0)
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

void IntensityDataPropertyWidget::setModel(JobModel *model)
{
    Q_ASSERT(model);
    if(model != m_jobModel) {
        if(m_jobModel)
            disconnect(m_jobModel,
                SIGNAL( selectionChanged(JobItem *) ),
                this,
                SLOT( setItem(JobItem *) )
                );

        m_jobModel = model;
        connect(m_jobModel,
            SIGNAL( selectionChanged(JobItem *) ),
            this,
            SLOT( setItem(JobItem *) )
            );
    }
}

void IntensityDataPropertyWidget::setItem(IntensityDataItem *jobItem)
{
    m_componentEditor->setItem(jobItem);
}
