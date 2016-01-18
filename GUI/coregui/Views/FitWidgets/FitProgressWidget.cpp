// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/FitWidgets/RunFitWidget.h
//! @brief     Defines class RunFitWidget
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "FitProgressWidget.h"
#include <QLabel>
#include <QVBoxLayout>

FitProgressWidget::FitProgressWidget(QWidget *parent)
    : QWidget(parent)
    , m_status(new QLabel(this))
{
    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(m_status);
    layout->addStretch();
    m_status->setText("hallo");
    setLayout(layout);
}

void FitProgressWidget::updateStatus(const QString &text)
{
    m_status->setText(text);
}
