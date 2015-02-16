// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/InstrumentWidgets/TestDetectorEditorWidget.cpp
//! @brief     Implements class TestDetectorEditorWidget
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "TestDetectorEditorWidget.h"
#include <QGroupBox>
#include <QVBoxLayout>

TestDetectorEditorWidget::TestDetectorEditorWidget(QWidget *parent)
    : QWidget(parent)
{
    QGroupBox *detectorGroup = new QGroupBox("Detector Parameters");

    // main layout
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(detectorGroup);
    setLayout(mainLayout);
}



