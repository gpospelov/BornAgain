// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Models/ObsoleteFitParameterItems.cpp
//! @brief     Implements class ObsoleteFitParameterItems
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "ObsoleteFitParameterItems.h"
#include "ComboProperty.h"

ObsoleteFitParameterContainer::ObsoleteFitParameterContainer()
    : SessionItem(Constants::ObsoleteFitParameterContainerType)
{
    const QString T_DATA = "Data tag";
    registerTag(T_DATA, 0, -1, QStringList() << Constants::ObsoleteFitParameterType);
    setDefaultTag(T_DATA);
}


const QString ObsoleteFitParameterItem::P_USE = "Use";
const QString ObsoleteFitParameterItem::P_INIT = "Starting Value";
const QString ObsoleteFitParameterItem::P_MIN = "Min";
const QString ObsoleteFitParameterItem::P_MAX = "Max";

ObsoleteFitParameterItem::ObsoleteFitParameterItem()
    : SessionItem(Constants::ObsoleteFitParameterType)
{
    addProperty(P_USE, true);
    addProperty(P_INIT, 0.0);
    addProperty(P_MIN, 0.0);
    addProperty(P_MAX, 0.0);
    const QString T_LINK = "Link tag";
    registerTag(T_LINK, 0, -1, QStringList() << Constants::ObsoleteFitParameterLinkType);
    setDefaultTag(T_LINK);
}



const QString ObsoleteFitParameterLinkItem::P_LINK = "Link";

ObsoleteFitParameterLinkItem::ObsoleteFitParameterLinkItem()
    : SessionItem(Constants::ObsoleteFitParameterLinkType)
{
    addProperty(P_LINK, "");
}


const QString ObsoleteFitSelectionItem::P_SAMPLE = "Sample";
const QString ObsoleteFitSelectionItem::P_INSTRUMENT = "Instrument";

ObsoleteFitSelectionItem::ObsoleteFitSelectionItem()
    : SessionItem(Constants::ObsoleteFitSelectionType)
{
    addProperty(P_SAMPLE, "");
    addProperty(P_INSTRUMENT, "");
}

const QString ObsoleteMinimizerSettingsItem::P_ALGO = "Algorithm";

ObsoleteMinimizerSettingsItem::ObsoleteMinimizerSettingsItem()
    : SessionItem(Constants::ObsoleteMinimizerSettingsType)
{
    ComboProperty algo;
    algo << "Migrad" << "Simplex" << "Combined" << "Scan" << "Fumili";
    addProperty(P_ALGO, algo.getVariant());
}

const QString ObsoleteInputDataItem::P_PATH = "Path";

ObsoleteInputDataItem::ObsoleteInputDataItem()
    : SessionItem(Constants::ObsoleteInputDataType)
{
    addProperty(P_PATH, "");
}


