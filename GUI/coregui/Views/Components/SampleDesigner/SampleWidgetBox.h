// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/Components/SampleDesigner/SampleWidgetBox.h
//! @brief     Defines class SampleWidgetBox
//!
//! @homepage  http://bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef SAMPLEWIDGETBOX_H
#define SAMPLEWIDGETBOX_H

#include "WinDllMacros.h"
#include <QWidget>

class QDesignerWidgetBoxInterface;
class SampleDesignerInterface;

//! widget box and tool window on the left side of SampleView
class BA_CORE_API_ SampleWidgetBox : public QWidget
{
public:
    explicit SampleWidgetBox(SampleDesignerInterface *core, QWidget *parent);

private:
    SampleDesignerInterface *m_core;
    QDesignerWidgetBoxInterface *m_widgetBox;
};

#endif // SAMPLEWIDGETBOX_H
