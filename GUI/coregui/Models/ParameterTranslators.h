// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/ParameterTranslators.h
//! @brief     Declares interface IParameterTranslator and subclasses
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

#include <string>
#include <QStringList>

class IParameterTranslator {
public:
    virtual ~IParameterTranslator() {}

    virtual IParameterTranslator *clone() const=0;

    virtual QStringList split(const QString &par_name) const=0;
    virtual std::string translate(const QString &name) const=0;
};

class PositionTranslator : public IParameterTranslator {
public:
    PositionTranslator();
    virtual ~PositionTranslator() {}

    virtual PositionTranslator *clone() const;

    virtual QStringList split(const QString &par_name) const;
    virtual std::string translate(const QString &name) const;
};

class RotationTranslator : public IParameterTranslator {
public:
    RotationTranslator();
    virtual ~RotationTranslator() {}

    virtual RotationTranslator *clone() const;

    virtual QStringList split(const QString &par_name) const;
    virtual std::string translate(const QString &name) const;
};

#endif // PARAMETERTRANSLATORS_H

