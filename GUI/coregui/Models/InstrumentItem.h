// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/InstrumentItem.h
//! @brief     Defines class InstrumentItem
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef INSTRUMENTITEM_H
#define INSTRUMENTITEM_H

#include "SessionItem.h"

class BeamItem;
class DetectorContainerItem;
class DetectorItem;
class MaskContainerItem;
class GroupItem;

class BA_CORE_API_ InstrumentItem : public SessionItem
{
public:    
    static const QString P_IDENTIFIER;
    static const QString P_BEAM;
    static const QString P_DETECTOR;
    InstrumentItem();

    BeamItem *beamItem() const;
    DetectorContainerItem *detectorContainerItem() const;
    DetectorItem *detectorItem() const;
    GroupItem* detectorGroup();

    void setDetectorGroup(const QString& modelType);

    void clearMasks();

    void importMasks(MaskContainerItem* maskContainer);
};

#endif // INSTRUMENTITEM_H
