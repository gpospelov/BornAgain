// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Models/NJobModel.cpp
//! @brief     Implements class NJobModel
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "FitParameterItems.h"
#include "ComboProperty.h"

FitParameterContainer::FitParameterContainer()
    : SessionItem(Constants::FitParameterContainerType)
{
    const QString T_DATA = "Data tag";
    registerTag(T_DATA, 0, -1, QStringList() << Constants::FitParameterType);
    setDefaultTag(T_DATA);
}


const QString FitParameterItem::P_USE = "Use";
const QString FitParameterItem::P_INIT = "Starting Value";
const QString FitParameterItem::P_MIN = "Min";
const QString FitParameterItem::P_MAX = "Max";

FitParameterItem::FitParameterItem()
    : SessionItem(Constants::FitParameterType)
{
    addProperty(P_USE, true);
    addProperty(P_INIT, 0.0);
    addProperty(P_MIN, 0.0);
    addProperty(P_MAX, 0.0);
    const QString T_LINK = "Link tag";
    registerTag(T_LINK, 0, -1, QStringList() << Constants::FitParameterLinkType);
    setDefaultTag(T_LINK);
}



const QString FitParameterLinkItem::P_LINK = "Link";

FitParameterLinkItem::FitParameterLinkItem()
    : SessionItem(Constants::FitParameterLinkType)
{
    addProperty(P_LINK, "");
}


const QString FitSelectionItem::P_SAMPLE = "Sample";
const QString FitSelectionItem::P_INSTRUMENT = "Instrument";

FitSelectionItem::FitSelectionItem()
    : SessionItem(Constants::FitSelectionType)
{
    addProperty(P_SAMPLE, "");
    addProperty(P_INSTRUMENT, "");
}

const QString MinimizerSettingsItem::P_ALGO = "Algorithm";

MinimizerSettingsItem::MinimizerSettingsItem()
    : SessionItem(Constants::MinimizerSettingsType)
{
    ComboProperty algo;
    algo << "Migrad" << "Simplex" << "Combined" << "Scan" << "Fumili";
    addProperty(P_ALGO, algo.getVariant());
}

const QString InputDataItem::P_PATH = "Path";

InputDataItem::InputDataItem()
    : SessionItem(Constants::InputDataType)
{
    addProperty(P_PATH, "");
}


