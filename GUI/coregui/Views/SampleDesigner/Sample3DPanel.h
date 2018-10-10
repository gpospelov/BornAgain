// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/SampleDesigner/Sample3DPanel.h
//! @brief     Defines class Sample3DPanel
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef SAMPLE3DPANEL_H
#define SAMPLE3DPANEL_H

#include "WinDllMacros.h"
#include <QWidget>

//! Place for RealSpaceWidget in the context of SampleView docks.

class BA_CORE_API_ Sample3DPanel : public QWidget
{
Q_OBJECT
public:
    Sample3DPanel(QWidget* parent = nullptr);

    QSize minimumSizeHint() const override;

    QSize sizeHint() const override;

};

#endif
