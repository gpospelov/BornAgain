// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/InstrumentWidgets/PolarizationAnalysisEditor.h
//! @brief     Defines class PolarizationAnalysisEditor
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef POLARIZATIONANALYSISEDITOR_H
#define POLARIZATIONANALYSISEDITOR_H

#include "SessionItem.h"
#include "WinDllMacros.h"
#include <QWidget>

class BA_CORE_API_ PolarizationAnalysisEditor : public QWidget
{
    Q_OBJECT
public:
    PolarizationAnalysisEditor(QWidget* parent = nullptr);

};

#endif  // POLARIZATIONANALYSISEDITOR_H
