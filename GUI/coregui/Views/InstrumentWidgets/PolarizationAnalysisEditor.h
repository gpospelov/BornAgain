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

#include "SessionItemWidget.h"
class ComponentEditor;
class GISASInstrumentItem;
class BeamItem;
class DetectorItem;
class QGridLayout;
class ColumnResizer;

//! Polarization analysis editor (beam polarization, analyzer properies) for GISASInstrumentEditor.
//! Operates on GISASInstrumentItem.

class BA_CORE_API_ PolarizationAnalysisEditor : public SessionItemWidget
{
    Q_OBJECT
public:
    PolarizationAnalysisEditor(ColumnResizer* columnResizer, QWidget* parent = nullptr);
    ~PolarizationAnalysisEditor();

protected:
    void subscribeToItem();
    void unsubscribeFromItem();

private:
    GISASInstrumentItem* instrumentItem();
    BeamItem* beamItem();
    DetectorItem* detectorItem();
    void updateAnalyserEditor();

    ColumnResizer* m_columnResizer;
    ComponentEditor* m_polarizationEditor;
    ComponentEditor* m_analyserEditor;
    QGridLayout* m_gridLayout;
};

#endif  // POLARIZATIONANALYSISEDITOR_H
