// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/InstrumentWidgets/GISASInstrumentEditorV2.h
//! @brief     Defines class GISASInstrumentEditorV2
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef GISASINSTRUMENTEDITORV2_H
#define GISASINSTRUMENTEDITORV2_H

#include "SessionItemWidget.h"

class GISASInstrumentItem;
class GISASBeamEditor;
class GISASDetectorEditor;
class EnvironmentEditor;
class PolarizationAnalysisEditor;
class QVBoxLayout;

class BA_CORE_API_ GISASInstrumentEditorV2 : public SessionItemWidget
{
    Q_OBJECT
public:
    GISASInstrumentEditorV2(QWidget* parent = 0);

protected:
    void subscribeToItem();
    void unsubscribeFromItem();

private:
    void addEditor(QVBoxLayout* layout, QWidget* widget, const QString& name, bool expanded=true);

    GISASInstrumentItem* instrumentItem();
    GISASBeamEditor* m_beamEditor;
    GISASDetectorEditor* m_detectorEditor;
    EnvironmentEditor* m_environmentEditor;
    PolarizationAnalysisEditor* m_polarizationAnalysisEditor;
};

#endif  // GISASINSTRUMENTEDITORV2_H
