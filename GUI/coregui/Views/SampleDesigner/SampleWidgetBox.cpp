// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/SampleDesigner/SampleWidgetBox.cpp
//! @brief     Implements class SampleWidgetBox
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "styledbar.h"
#include "widgetbox.h"
#include "SampleWidgetBox.h"
#include <QVBoxLayout>

#if QT_VERSION < 0x050000
#define QStringLiteral QString
#endif


SampleWidgetBox::SampleWidgetBox(SampleDesignerInterface *core, QWidget *parent)
    : QWidget(parent)
    , m_core(core)
    , m_widgetBox(0)
{
    //Manhattan::StyledBar *bar = new Manhattan::StyledBar(this);

    setWindowTitle("Items Toolbox");

    m_widgetBox = new qdesigner_internal::WidgetBox(m_core, this);
    m_widgetBox->setFileName(QStringLiteral(":/widgetbox/widgetbox.xml"));
    m_widgetBox->load();
    m_widgetBox->setWindowTitle(QLatin1String("Widget Box"));
    m_widgetBox->setObjectName(QLatin1String("WidgetBox"));


    QVBoxLayout *layout = new QVBoxLayout;
    layout->setMargin(0);
    layout->setSpacing(0);
//    layout->addWidget(bar);
    layout->addWidget(m_widgetBox);
    setLayout(layout);

}
