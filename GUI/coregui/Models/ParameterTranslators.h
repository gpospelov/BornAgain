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

class IParameterTranslator {
public:
    virtual ~IParameterTranslator()=default;

    virtual IParameterTranslator* clone() const=0;

    virtual QStringList split(const QString &par_name) const;
    virtual std::string translate(const QString &name) const=0;
};


class PositionTranslator final : public IParameterTranslator {
public:
    ~PositionTranslator() override {}

    PositionTranslator* clone() const override { return new PositionTranslator {}; }

    std::string translate(const QString &name) const override;
};


class RotationTranslator final : public IParameterTranslator {
public:
    ~RotationTranslator() override {}

    RotationTranslator* clone() const override { return new RotationTranslator {}; }

    std::string translate(const QString &name) const override;
};

class IPathTranslator {
public:
//    IPathTranslator(const IPathTranslator&) = delete;
//    IPathTranslator& operator=(const IPathTranslator&) = delete;
    virtual ~IPathTranslator()=default;

    virtual IPathTranslator* clone() const=0;

    virtual QStringList translate(const QStringList& list) const=0;
};

class NewPositionTranslator : public IPathTranslator {
public:
    ~NewPositionTranslator() override {}

    NewPositionTranslator* clone() const override { return new NewPositionTranslator; }

    virtual QStringList translate(const QStringList& list) const;
};

class NewRotationTranslator : public IPathTranslator {
public:
    ~NewRotationTranslator() override {}

    NewRotationTranslator* clone() const override { return new NewRotationTranslator; }

    virtual QStringList translate(const QStringList& list) const;
};

class DistributionNoneTranslator : public IPathTranslator {
public:
    ~DistributionNoneTranslator() override {}

    DistributionNoneTranslator* clone() const override { return new DistributionNoneTranslator; }

    virtual QStringList translate(const QStringList& list) const;
};

class RoughnessTranslator : public IPathTranslator {
public:
    ~RoughnessTranslator() override {}

    RoughnessTranslator* clone() const override { return new RoughnessTranslator; }

    virtual QStringList translate(const QStringList& list) const;
private:
    int getLayerIndex(QString layerName) const;
};


#endif // PARAMETERTRANSLATORS_H
