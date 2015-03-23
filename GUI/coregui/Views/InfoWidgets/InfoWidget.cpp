// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/InfoWidgets/InfoWidget.cpp
//! @brief     Implements class InfoWidget
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "InfoWidget.h"
#include "PySampleWidget.h"
#include <QVBoxLayout>

InfoWidget::InfoWidget(QWidget *parent)
    : QWidget(parent)
    , m_pySampleWidget(new PySampleWidget(this))
{
    setWindowTitle(tr("Info Stream"));
    setObjectName(tr("InfoStream"));
    setMinimumSize(128, 128);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(m_pySampleWidget);

    setLayout(mainLayout);
}

void InfoWidget::setSampleModel(SampleModel *sampleModel)
{
    Q_ASSERT(m_pySampleWidget);
    m_pySampleWidget->setSampleModel(sampleModel);
}

void InfoWidget::setInstrumentModel(InstrumentModel *instrumentModel)
{
    Q_ASSERT(m_pySampleWidget);
    m_pySampleWidget->setInstrumentModel(instrumentModel);
}
