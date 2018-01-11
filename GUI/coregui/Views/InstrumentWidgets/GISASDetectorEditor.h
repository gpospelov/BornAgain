// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/InstrumentWidgets/GISASDetectorEditor.h
//! @brief     Defines class GISASDetectorEditor
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef GISASDETECTOREDITOR_H
#define GISASDETECTOREDITOR_H

#include "SessionItem.h"
#include "WinDllMacros.h"
#include <QWidget>

class ComponentEditor;
class DetectorPresenter;

class BA_CORE_API_ GISASDetectorEditor : public QWidget
{
    Q_OBJECT
public:
    GISASDetectorEditor(QWidget* parent = nullptr);

private:
    ComponentEditor* m_detectorTypeEditor;
    DetectorPresenter* m_detectorPresenter;
};

#endif  // GISASDETECTOREDITOR_H
