// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/FitWidgets/FitParameterWidget.cpp
//! @brief     Implements class FitParameterWidget
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "MinimizerSettingsWidget.h"
#include "AwesomePropertyEditor.h"
#include "FitModel.h"
#include "FitParameterItems.h"
#include <QHBoxLayout>
#include <QSplitter>

MinimizerSettingsWidget::MinimizerSettingsWidget(FitModel *fitModel, QWidget *parent)
    : QWidget(parent)
{
    QHBoxLayout *layout = new QHBoxLayout;
    AwesomePropertyEditor *editor = new AwesomePropertyEditor(this);
    editor->setItem(fitModel->getMinimizerSettings());
    layout->addWidget(editor);
    setLayout(layout);
}
