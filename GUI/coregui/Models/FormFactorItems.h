// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Models/FormFactorItems.h
//! @brief     Defines FormFactorItem classes.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef FORMFACTORITEMS_H
#define FORMFACTORITEMS_H

#include "ParameterizedItem.h"
class IFormFactor;

class FormFactorItem : public ParameterizedItem
{
    Q_OBJECT
public:
    explicit FormFactorItem(const QString name, ParameterizedItem *parent) : ParameterizedItem(name, parent){}
    virtual IFormFactor *createFormFactor() const{ return 0;}
    virtual ~FormFactorItem(){}
};


class AnisoPyramidItem : public FormFactorItem
{
    Q_OBJECT
public:
    explicit AnisoPyramidItem(ParameterizedItem *parent=0);
    IFormFactor *createFormFactor() const;
};


class BoxItem : public FormFactorItem
{
    Q_OBJECT
public:
    explicit BoxItem(ParameterizedItem *parent=0);
    IFormFactor *createFormFactor() const;
};


class ConeItem : public FormFactorItem
{
    Q_OBJECT
public:
    explicit ConeItem(ParameterizedItem *parent=0);
    IFormFactor *createFormFactor() const;
};


class Cone6Item : public FormFactorItem
{
    Q_OBJECT
public:
    explicit Cone6Item(ParameterizedItem *parent=0);
    IFormFactor *createFormFactor() const;
};


class CuboctahedronItem : public FormFactorItem
{
    Q_OBJECT
public:
    explicit CuboctahedronItem(ParameterizedItem *parent=0);
    IFormFactor *createFormFactor() const;
};


class CylinderItem : public FormFactorItem
{
    Q_OBJECT
public:
    explicit CylinderItem(ParameterizedItem *parent=0);
    IFormFactor *createFormFactor() const;
};


class EllipsoidalCylinderItem : public FormFactorItem
{
    Q_OBJECT
public:
    explicit EllipsoidalCylinderItem(ParameterizedItem *parent=0);
    IFormFactor *createFormFactor() const;
};


class FullSphereItem : public FormFactorItem
{
    Q_OBJECT
public:
    explicit FullSphereItem(ParameterizedItem *parent=0);
    IFormFactor *createFormFactor() const;
};


class FullSpheroidItem : public FormFactorItem
{
    Q_OBJECT
public:
    explicit FullSpheroidItem(ParameterizedItem *parent=0);
    IFormFactor *createFormFactor() const;
};


class HemiEllipsoidItem : public FormFactorItem
{
    Q_OBJECT
public:
    explicit HemiEllipsoidItem(ParameterizedItem *parent=0);
    IFormFactor *createFormFactor() const;
};


class Prism3Item : public FormFactorItem
{
    Q_OBJECT
public:
    explicit Prism3Item(ParameterizedItem *parent=0);
    IFormFactor *createFormFactor() const;
};


class Prism6Item : public FormFactorItem
{
    Q_OBJECT
public:
    explicit Prism6Item(ParameterizedItem *parent=0);
    IFormFactor *createFormFactor() const;
};


class PyramidItem : public FormFactorItem
{
    Q_OBJECT
public:
    explicit PyramidItem(ParameterizedItem *parent=0);
    IFormFactor *createFormFactor() const;
};


class Ripple1Item : public FormFactorItem
{
    Q_OBJECT
public:
    explicit Ripple1Item(ParameterizedItem *parent=0);
    IFormFactor *createFormFactor() const;
};


class Ripple2Item : public FormFactorItem
{
    Q_OBJECT
public:
    explicit Ripple2Item(ParameterizedItem *parent=0);
    IFormFactor *createFormFactor() const;
};


class TetrahedronItem : public FormFactorItem
{
    Q_OBJECT
public:
    explicit TetrahedronItem(ParameterizedItem *parent=0);
    IFormFactor *createFormFactor() const;
};


class TruncatedSphereItem : public FormFactorItem
{
    Q_OBJECT
public:
    explicit TruncatedSphereItem(ParameterizedItem *parent=0);
    IFormFactor *createFormFactor() const;
};


class TruncatedSpheroidItem : public FormFactorItem
{
    Q_OBJECT
public:
    explicit TruncatedSpheroidItem(ParameterizedItem *parent=0);
    IFormFactor *createFormFactor() const;
};


#endif // FORMFACTORITEMS_H

