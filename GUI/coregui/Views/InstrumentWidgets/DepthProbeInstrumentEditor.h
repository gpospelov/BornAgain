// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/InstrumentWidgets/DepthProbeInstrumentEditor.h
//! @brief     Defines class DepthProbeInstrumentEditor
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef DEPTHPROBEINSTRUMENTEDITOR_H
#define DEPTHPROBEINSTRUMENTEDITOR_H

#include "SessionItemWidget.h"

class BA_CORE_API_ DepthProbeInstrumentEditor : public SessionItemWidget
{
    Q_OBJECT

public:
    DepthProbeInstrumentEditor(QWidget* parent = nullptr);

protected:
    void subscribeToItem();

};


#endif
