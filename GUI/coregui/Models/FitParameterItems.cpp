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

FitParameterContainer::FitParameterContainer(ParameterizedItem *parent)
    : ParameterizedItem(Constants::FitParameterContainerType, parent)
{
    addToValidChildren(Constants::FitParameterType);
}


const QString FitParameterItem::P_USE = "Use";
const QString FitParameterItem::P_INIT = "Starting Value";
const QString FitParameterItem::P_MIN = "Min";
const QString FitParameterItem::P_MAX = "Max";

FitParameterItem::FitParameterItem(ParameterizedItem *parent)
    : ParameterizedItem(Constants::FitParameterType, parent)
{
    registerProperty(P_USE, true);
    registerProperty(P_INIT, 0.0);
    registerProperty(P_MIN, 0.0);
    registerProperty(P_MAX, 0.0);
    addToValidChildren(Constants::FitParameterLinkType);
}



const QString FitParameterLinkItem::P_LINK = "Link";

FitParameterLinkItem::FitParameterLinkItem(ParameterizedItem *parent)
    : ParameterizedItem(Constants::FitParameterLinkType, parent)
{
    registerProperty(P_LINK, "");
}


const QString FitSelectionItem::P_SAMPLE = "Sample";
const QString FitSelectionItem::P_INSTRUMENT = "Instrument";

FitSelectionItem::FitSelectionItem(ParameterizedItem *parent)
    : ParameterizedItem(Constants::FitSelectionType, parent)
{
    registerProperty(P_SAMPLE, "");
    registerProperty(P_INSTRUMENT, "");
}

const QString MinimizerSettingsItem::P_ALGO = "Algorithm";

MinimizerSettingsItem::MinimizerSettingsItem(ParameterizedItem *parent)
    : ParameterizedItem(Constants::MinimizerSettingsType, parent)
{
    ComboProperty algo;
    algo << "Migrad" << "Simplex" << "Combined" << "Scan" << "Fumili";
    registerProperty(P_ALGO, algo.getVariant());
}

const QString InputDataItem::P_PATH = "Path";

InputDataItem::InputDataItem(ParameterizedItem *parent)
    : ParameterizedItem(Constants::InputDataType, parent)
{
    registerProperty(P_PATH, "");
}


