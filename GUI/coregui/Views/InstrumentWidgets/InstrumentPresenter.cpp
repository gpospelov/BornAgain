//  ************************************************************************************************
//
//  BornAgain: simulate and fit reflection and scattering
//
//! @file      GUI/coregui/Views/InstrumentWidgets/InstrumentPresenter.cpp
//! @brief     Implements class InstrumentPresenter
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#include "GUI/coregui/Views/InstrumentWidgets/InstrumentPresenter.h"
#include "GUI/coregui/Models/SessionItem.h"
#include "GUI/coregui/Views/InstrumentWidgets/DepthProbeInstrumentEditor.h"
#include "GUI/coregui/Views/InstrumentWidgets/GISASInstrumentEditor.h"
#include "GUI/coregui/Views/InstrumentWidgets/OffSpecularInstrumentEditor.h"
#include "GUI/coregui/Views/InstrumentWidgets/SpecularInstrumentEditor.h"
#include "GUI/coregui/utils/GUIHelpers.h"

namespace {
const QString GISASPresentation = "GISAS";
const QString OffSpecularPresentation = "OffSpecular";
const QString SpecularPresentation = "Specular";
const QString DepthProbePresentation = "DepthProbe";
} // namespace

InstrumentPresenter::InstrumentPresenter(QWidget* parent) : ItemComboWidget(parent)
{
    registerWidget(GISASPresentation, create_new<GISASInstrumentEditor>);
    registerWidget(OffSpecularPresentation, create_new<OffSpecularInstrumentEditor>);
    registerWidget(SpecularPresentation, create_new<SpecularInstrumentEditor>);
    registerWidget(DepthProbePresentation, create_new<DepthProbeInstrumentEditor>);
    setToolBarVisible(false);
}

QString InstrumentPresenter::itemPresentation() const
{
    if (!currentItem())
        return {};

    if (currentItem()->modelType() == "GISASInstrument")
        return GISASPresentation;
    else if (currentItem()->modelType() == "OffSpecularInstrument")
        return OffSpecularPresentation;
    else if (currentItem()->modelType() == "SpecularInstrument")
        return SpecularPresentation;
    else if (currentItem()->modelType() == "DepthProbeInstrument")
        return DepthProbePresentation;
    else
        throw GUIHelpers::Error("InstrumentPresenter::itemPresentation() -> Error. Wrong item "
                                "type '"
                                + currentItem()->modelType() + "'");
}

QStringList InstrumentPresenter::activePresentationList(SessionItem* item)
{
    Q_UNUSED(item);
    return QStringList() << GISASPresentation << OffSpecularPresentation << SpecularPresentation
                         << DepthProbePresentation;
}
