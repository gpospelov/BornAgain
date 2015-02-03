// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Models/NJobItem.cpp
//! @brief     Implements class NJobItem
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "NJobItem.h"
#include "ComboProperty.h"

const QString NJobItem::P_BEGIN_TYPE = "Begin Time";
const QString NJobItem::P_END_TYPE = "End Time";
const QString NJobItem::P_COMMENTS = "Comments";
const QString NJobItem::P_STATUS = "Status";
const QString NJobItem::P_PROGRESS = "Progress";
const QString NJobItem::P_NTHREADS = "Number of Threads";
const QString NJobItem::P_RUN_POLICY = "Run Policy";

NJobItem::NJobItem(ParameterizedItem *parent)
    : ParameterizedItem(Constants::JobItemType, parent)
{
    setItemName(Constants::JobItemType);
    registerProperty(P_BEGIN_TYPE, QString());
    registerProperty(P_END_TYPE, QString());
    registerProperty(P_COMMENTS, QString());

    ComboProperty status;
    status << QString("Idle") << QString("Running") << QString("Completed")
          << QString("Canceled") << QString("Failed");
    registerProperty(P_STATUS, status.getVariant());

    registerProperty(P_PROGRESS, 0);
    registerProperty(P_NTHREADS, -1);

    ComboProperty policy;
    policy << QString("Immediately") << QString("In background") << QString("Submit only");
    registerProperty(P_RUN_POLICY, policy.getVariant());

    addToValidChildren(Constants::IntensityDataType, PortInfo::PORT_0);

}

