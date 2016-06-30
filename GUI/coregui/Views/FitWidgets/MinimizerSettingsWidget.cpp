// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/FitWidgets/MinimizerSettingsWidget.cpp
//! @brief     Implements class MinimizerSettingsWidget
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "MinimizerSettingsWidget.h"
#include "MinimizerItem.h"
#include "ComponentEditor.h"
#include "JobItem.h"
#include "FitSuiteItem.h"
#include <QVBoxLayout>
#include <QPushButton>
#include <QDebug>

MinimizerSettingsWidget::MinimizerSettingsWidget(QWidget *parent)
    : QWidget(parent)
    , m_currentItem(0)
    , m_propertyEditor(new ComponentEditor)
{
    setWindowTitle(QLatin1String("Minimizer Settings"));

    QVBoxLayout *layout = new QVBoxLayout;
    layout->setMargin(0);
    layout->setSpacing(0);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->addWidget(m_propertyEditor);

    setLayout(layout);
}

QSize MinimizerSettingsWidget::minimumSizeHint() const
{
    return QSize(25, 25);
}

void MinimizerSettingsWidget::setItem(JobItem *jobItem)
{
    Q_ASSERT(jobItem);
    setItem(jobItem->fitSuiteItem()->minimizerContainerItem());
}

void MinimizerSettingsWidget::setItem(MinimizerContainerItem *minimizerItem)
{
    Q_ASSERT(minimizerItem);
    m_currentItem = minimizerItem;
    m_propertyEditor->setItem(minimizerItem);
}
