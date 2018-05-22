// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/InstrumentItems.h
//! @brief     Defines InstrumentItems classes
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef INSTRUMENTITEMS_H
#define INSTRUMENTITEMS_H

#include "BeamItems.h"

class BackgroundItem;
class DataItem;
class DetectorItem;
class GroupItem;
class Instrument;
class MaskContainerItem;

class BA_CORE_API_ InstrumentItem : public SessionItem
{
public:
    static const QString P_IDENTIFIER;
    static const QString P_BEAM;
    static const QString P_BACKGROUND;

    QStringList translateList(const QStringList& list) const override;

    virtual BeamItem* beamItem() const;
    BackgroundItem* backgroundItem() const;
    GroupItem* backgroundGroup();

    virtual std::unique_ptr<Instrument> createInstrument() const = 0;
    virtual std::vector<int> shape() const = 0;
    virtual void setShape(const std::vector<int>& shape) = 0;

protected:
    explicit InstrumentItem(const QString& modelType);

    void initBeamGroup(const QString& beam_model);
};

class BA_CORE_API_ SpecularInstrumentItem : public InstrumentItem
{
public:
    SpecularInstrumentItem();
    virtual ~SpecularInstrumentItem();

    SpecularBeamItem* beamItem() const override;

    std::unique_ptr<Instrument> createInstrument() const override;
    std::vector<int> shape() const override;
    void setShape(const std::vector<int>& shape) override;
};

class BA_CORE_API_ Instrument2DItem : public InstrumentItem
{
public:
    static const QString P_DETECTOR;

    virtual ~Instrument2DItem();

    DetectorItem* detectorItem() const;
    GroupItem* detectorGroup();

    void setDetectorGroup(const QString& modelType);

    void clearMasks();

    void importMasks(MaskContainerItem* maskContainer);

    std::unique_ptr<Instrument> createInstrument() const override;

protected:
    explicit Instrument2DItem(const QString& modelType);
};

class BA_CORE_API_ GISASInstrumentItem : public Instrument2DItem
{
public:
    GISASInstrumentItem();
    std::vector<int> shape() const override;
    void setShape(const std::vector<int>& data_shape) override;
};

class BA_CORE_API_ OffSpecInstrumentItem : public Instrument2DItem
{
public:
    static const QString P_ALPHA_AXIS;

    OffSpecInstrumentItem();
    std::vector<int> shape() const override;
    void setShape(const std::vector<int>& data_shape) override;
};

#endif // INSTRUMENTITEMS_H
