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

class IParameterTranslator {
public:
    virtual ~IParameterTranslator() {}

    virtual IParameterTranslator* clone() const=0;

    virtual QStringList split(const QString &par_name) const=0;
    virtual std::string translate(const QString &name) const=0;
};


class PositionTranslator : public IParameterTranslator {
public:
    ~PositionTranslator() final {}

    virtual PositionTranslator* clone() const { return new PositionTranslator(); }

    virtual QStringList split(const QString &par_name) const;
    virtual std::string translate(const QString &name) const;
};


class RotationTranslator : public IParameterTranslator {
public:
    ~RotationTranslator() final {}

    virtual RotationTranslator* clone() const { return new RotationTranslator(); }

    virtual QStringList split(const QString &par_name) const;
    virtual std::string translate(const QString &name) const;
};

#endif // PARAMETERTRANSLATORS_H
