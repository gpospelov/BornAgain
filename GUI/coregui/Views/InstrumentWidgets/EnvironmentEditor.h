// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/InstrumentWidgets/EnvironmentEditor.h
//! @brief     Defines class EnvironmentEditor
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef ENVIRONMENTEDITOR_H
#define ENVIRONMENTEDITOR_H

#include "SessionItem.h"
#include "WinDllMacros.h"
#include <QWidget>

class BA_CORE_API_ EnvironmentEditor : public QWidget
{
    Q_OBJECT
public:
    EnvironmentEditor(QWidget* parent = nullptr);

};

#endif  // ENVIRONMENTEDITOR_H
