// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/InstrumentWidgets/InstrumentPresenter.cpp
//! @brief     Implements class InstrumentPresenter
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "InstrumentPresenter.h"
#include "DepthProbeInstrumentEditor.h"
#include "GISASInstrumentEditor.h"
#include "GUIHelpers.h"
#include "OffSpecInstrumentEditor.h"
#include "SessionItem.h"
#include "SpecularInstrumentEditor.h"
#include "item_constants.h"

namespace
{
const QString GISASPresentation = "GISAS";
const QString OffSpecPresentation = "OffSpec";
const QString SpecularPresentation = "Specular";
const QString DepthProbePresentation = "DepthProbe";
} // namespace

InstrumentPresenter::InstrumentPresenter(QWidget* parent) : ItemComboWidget(parent)
{
    registerWidget(GISASPresentation, create_new<GISASInstrumentEditor>);
    registerWidget(OffSpecPresentation, create_new<OffSpecInstrumentEditor>);
    registerWidget(SpecularPresentation, create_new<SpecularInstrumentEditor>);
    registerWidget(DepthProbePresentation, create_new<DepthProbeInstrumentEditor>);
    setToolBarVisible(false);
}

QString InstrumentPresenter::itemPresentation() const
{
    if (!currentItem())
        return {};

    if (currentItem()->modelType() == Constants::GISASInstrumentType)
        return GISASPresentation;
    else if (currentItem()->modelType() == Constants::OffSpecInstrumentType)
        return OffSpecPresentation;
    else if (currentItem()->modelType() == Constants::SpecularInstrumentType)
        return SpecularPresentation;
    else if (currentItem()->modelType() == Constants::DepthProbeInstrumentType)
        return DepthProbePresentation;
    else
        throw GUIHelpers::Error("InstrumentPresenter::itemPresentation() -> Error. Wrong item "
                                "type '"
                                + currentItem()->modelType() + "'");
}

QStringList InstrumentPresenter::activePresentationList(SessionItem* item)
{
    Q_UNUSED(item);
    return QStringList() << GISASPresentation << OffSpecPresentation << SpecularPresentation
                         << DepthProbePresentation;
}
