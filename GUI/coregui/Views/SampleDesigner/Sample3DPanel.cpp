// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/SampleDesigner/Sample3DPanel.cpp
//! @brief     Implements class Sample3DPanel
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Sample3DPanel.h"
#include "RealSpaceWidget.h"
#include <QHBoxLayout>

Sample3DPanel::Sample3DPanel(SampleModel* sampleModel,
                             QItemSelectionModel* selectionModel, QWidget* parent)
    : QWidget(parent)
    , m_realSpaceWidget(nullptr)
{
    setWindowTitle("Real Space");
    setObjectName("Sample3DPanel");

#ifdef BORNAGAIN_OPENGL
    QHBoxLayout* layout = new QHBoxLayout;
    layout->setMargin(0);
    layout->setSpacing(0);
    layout->setContentsMargins(0, 0, 0, 0);

    m_realSpaceWidget = new RealSpaceWidget(sampleModel, selectionModel);
    layout->addWidget(m_realSpaceWidget);

    setLayout(layout);
#endif

}

//QSize Sample3DPanel::minimumSizeHint() const { return QSize(300, 300); }

//QSize Sample3DPanel::sizeHint() const { return QSize(100, 100); }
