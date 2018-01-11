// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/InstrumentWidgets/GISASBeamEditor.h
//! @brief     Defines class GISASBeamEditor
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef GISASBEAMEDITOR_H
#define GISASBEAMEDITOR_H

#include "SessionItem.h"
#include "WinDllMacros.h"
#include <QWidget>

class BA_CORE_API_ GISASBeamEditor : public QWidget
{
    Q_OBJECT
public:
    explicit GISASBeamEditor(QWidget* parent = nullptr);

};

#endif  // GISASBEAMEDITOR_H
