// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/ParameterTranslators.h
//! @brief     Defines interface IParameterTranslator and subclasses
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef PARAMETERTRANSLATORS_H
#define PARAMETERTRANSLATORS_H

#include <QStringList>

class SessionItem;

class IPathTranslator {
public:
    virtual ~IPathTranslator()=default;

    virtual IPathTranslator* clone() const=0;

    virtual QStringList translate(const QStringList& list) const=0;
};

class PositionTranslator : public IPathTranslator {
public:
    ~PositionTranslator() override {}

    PositionTranslator* clone() const override { return new PositionTranslator; }

    virtual QStringList translate(const QStringList& list) const override;
};

class RotationTranslator : public IPathTranslator {
public:
    ~RotationTranslator() override {}

    RotationTranslator* clone() const override { return new RotationTranslator; }

    virtual QStringList translate(const QStringList& list) const override;
};

class DistributionNoneTranslator : public IPathTranslator {
public:
    ~DistributionNoneTranslator() override {}

    DistributionNoneTranslator* clone() const override { return new DistributionNoneTranslator; }

    virtual QStringList translate(const QStringList& list) const override;
};

class RoughnessTranslator : public IPathTranslator {
public:
    RoughnessTranslator(const SessionItem* p_parent);
    ~RoughnessTranslator() override {}

    RoughnessTranslator* clone() const override;

    virtual QStringList translate(const QStringList& list) const override;
private:
    int getLayerIndex(QString layerName) const;
    int numberOfLayers() const;
    const SessionItem* mp_parent;
};

#endif // PARAMETERTRANSLATORS_H
