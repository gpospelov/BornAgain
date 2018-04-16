// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/IntensityDataWidgets/DescriptedPlot.h
//! @brief     Declares class DescriptedPlot
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef DESCRIPTEDPLOT_H
#define DESCRIPTEDPLOT_H

#include "SessionItemWidget.h"

//! Common interface for plot-descriptor interaction

class BA_CORE_API_ DescriptedPlot : public SessionItemWidget
{
    Q_OBJECT

public:
    explicit DescriptedPlot(QWidget* parent);
    ~DescriptedPlot() override;

signals:
    void statusString(const QString& text);
};

#endif // DESCRIPTEDPLOT_H
