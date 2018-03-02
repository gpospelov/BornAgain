// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/InstrumentWidgets/SpecularBeamEditor.h
//! @brief     Defines class SpecularBeamEditor
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef SPECULARBEAMEDITOR_H_
#define SPECULARBEAMEDITOR_H_

#include "SessionItemWidget.h"

class ComponentEditor;
class QGridLayout;
class SpecularInstrumentItem;
class BeamItem;
class ColumnResizer;

//! Specular beam editor. Operates on SpecularInstrumentItem.

class BA_CORE_API_ SpecularBeamEditor : public SessionItemWidget
{
    Q_OBJECT

public:
    explicit SpecularBeamEditor(ColumnResizer* columnResizer, QWidget* parent = nullptr);

protected:
    void subscribeToItem();
    void unsubscribeFromItem();

private:
    SpecularInstrumentItem* instrumentItem();
    BeamItem* beamItem();
    void onDialogRequest(SessionItem* item, const QString& name);

    ColumnResizer* m_columnResizer;
    ComponentEditor* m_intensityEditor;
    ComponentEditor* m_wavelengthEditor;
    ComponentEditor* m_inclinationEditor;
    QGridLayout* m_gridLayout;
};

#endif /* SPECULARBEAMEDITOR_H_ */
