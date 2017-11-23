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
#include "ComponentEditor.h"
#include "FitSuiteItem.h"
#include "JobItem.h"
#include "MinimizerItem.h"
#include <QPushButton>
#include <QVBoxLayout>

MinimizerSettingsWidget::MinimizerSettingsWidget(QWidget *parent)
    : QWidget(parent)
    , m_currentItem(nullptr)
    , m_componentEditor(new ComponentEditor)
{
    setWindowTitle(QLatin1String("Minimizer Settings"));

    auto layout = new QVBoxLayout;
    layout->setMargin(0);
    layout->setSpacing(0);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->addWidget(m_componentEditor);

    setLayout(layout);
}

QSize MinimizerSettingsWidget::minimumSizeHint() const
{
    return QSize(25, 25);
}

void MinimizerSettingsWidget::setItem(JobItem* jobItem)
{
    Q_ASSERT(jobItem);
    setItem(jobItem->fitSuiteItem()->minimizerContainerItem());
}

void MinimizerSettingsWidget::setItem(MinimizerContainerItem* minimizerItem)
{
    Q_ASSERT(minimizerItem);
    m_currentItem = minimizerItem;
    m_componentEditor->setItem(minimizerItem);
}
