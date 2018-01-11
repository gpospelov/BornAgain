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

class BeamItem;
class ComponentEditor;
class QGridLayout;

class BA_CORE_API_ GISASBeamEditor : public QWidget
{
    Q_OBJECT
public:
    explicit GISASBeamEditor(QWidget* parent = nullptr);

    void setBeamItem(BeamItem* beamItem);

    QGridLayout* gridLayout() { return m_gridLayout; }

private:
    void onDialogRequest(SessionItem* item, const QString& name);
    ComponentEditor* m_intensityEditor;
    ComponentEditor* m_wavelengthEditor;
    ComponentEditor* m_inclinationEditor;
    ComponentEditor* m_azimuthalEditor;
    QGridLayout* m_gridLayout;
    BeamItem* m_beamItem;
};

#endif  // GISASBEAMEDITOR_H
