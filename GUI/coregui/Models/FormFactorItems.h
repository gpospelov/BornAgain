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

class BA_CORE_API_ FormFactorItem : public ParameterizedItem
{
    Q_OBJECT
public:
    explicit FormFactorItem(const QString name, ParameterizedItem *parent) : ParameterizedItem(name, parent){}
    virtual IFormFactor *createFormFactor() const{ return 0;}
    virtual ~FormFactorItem(){}
};


class BA_CORE_API_ AnisoPyramidItem : public FormFactorItem
{
    Q_OBJECT
public:
    static const QString P_LENGTH, P_WIDTH, P_HEIGHT, P_ALPHA;
    explicit AnisoPyramidItem(ParameterizedItem *parent=0);
    IFormFactor *createFormFactor() const;
};


class BA_CORE_API_ BoxItem : public FormFactorItem
{
    Q_OBJECT
public:
    static const QString P_LENGTH, P_WIDTH, P_HEIGHT;
    explicit BoxItem(ParameterizedItem *parent=0);
    IFormFactor *createFormFactor() const;
};


class BA_CORE_API_ ConeItem : public FormFactorItem
{
    Q_OBJECT
public:
    static const QString P_RADIUS, P_HEIGHT, P_ALPHA;
    explicit ConeItem(ParameterizedItem *parent=0);
    IFormFactor *createFormFactor() const;
};


class BA_CORE_API_ Cone6Item : public FormFactorItem
{
    Q_OBJECT
public:
    static const QString P_RADIUS, P_HEIGHT, P_ALPHA;
    explicit Cone6Item(ParameterizedItem *parent=0);
    IFormFactor *createFormFactor() const;
};


class BA_CORE_API_ CuboctahedronItem : public FormFactorItem
{
    Q_OBJECT
public:
    static const QString P_LENGTH, P_HEIGHT, P_HEIGHT_RATIO, P_ALPHA;
    explicit CuboctahedronItem(ParameterizedItem *parent=0);
    IFormFactor *createFormFactor() const;
};


class BA_CORE_API_ CylinderItem : public FormFactorItem
{
    Q_OBJECT
public:
    static const QString P_RADIUS, P_HEIGHT;
    explicit CylinderItem(ParameterizedItem *parent=0);
    IFormFactor *createFormFactor() const;
};


class BA_CORE_API_ EllipsoidalCylinderItem : public FormFactorItem
{
    Q_OBJECT
public:
    static const QString P_RADIUS_A, P_RADIUS_B, P_HEIGHT;
    explicit EllipsoidalCylinderItem(ParameterizedItem *parent=0);
    IFormFactor *createFormFactor() const;
};


class BA_CORE_API_ FullSphereItem : public FormFactorItem
{
    Q_OBJECT
public:
    static const QString P_RADIUS;
    explicit FullSphereItem(ParameterizedItem *parent=0);
    IFormFactor *createFormFactor() const;
};


class BA_CORE_API_ FullSpheroidItem : public FormFactorItem
{
    Q_OBJECT
public:
    static const QString P_RADIUS, P_HEIGHT;
    explicit FullSpheroidItem(ParameterizedItem *parent=0);
    IFormFactor *createFormFactor() const;
};


class BA_CORE_API_ HemiEllipsoidItem : public FormFactorItem
{
    Q_OBJECT
public:
    static const QString P_RADIUS_A, P_RADIUS_B, P_HEIGHT;
    explicit HemiEllipsoidItem(ParameterizedItem *parent=0);
    IFormFactor *createFormFactor() const;
};


class BA_CORE_API_ Prism3Item : public FormFactorItem
{
    Q_OBJECT
public:
    static const QString P_LENGTH, P_HEIGHT;
    explicit Prism3Item(ParameterizedItem *parent=0);
    IFormFactor *createFormFactor() const;
};


class BA_CORE_API_ Prism6Item : public FormFactorItem
{
    Q_OBJECT
public:
    static const QString P_RADIUS, P_HEIGHT;
    explicit Prism6Item(ParameterizedItem *parent=0);
    IFormFactor *createFormFactor() const;
};


class BA_CORE_API_ PyramidItem : public FormFactorItem
{
    Q_OBJECT
public:
    static const QString P_LENGTH, P_HEIGHT, P_ALPHA;
    explicit PyramidItem(ParameterizedItem *parent=0);
    IFormFactor *createFormFactor() const;
};


class BA_CORE_API_ Ripple1Item : public FormFactorItem
{
    Q_OBJECT
public:
    static const QString P_LENGTH, P_WIDTH, P_HEIGHT;
    explicit Ripple1Item(ParameterizedItem *parent=0);
    IFormFactor *createFormFactor() const;
};


class BA_CORE_API_ Ripple2Item : public FormFactorItem
{
    Q_OBJECT
public:
    static const QString P_LENGTH, P_WIDTH, P_HEIGHT, P_ASYMMETRY;
    explicit Ripple2Item(ParameterizedItem *parent=0);
    IFormFactor *createFormFactor() const;
};


class BA_CORE_API_ TetrahedronItem : public FormFactorItem
{
    Q_OBJECT
public:
    static const QString P_LENGTH, P_HEIGHT, P_ALPHA;
    explicit TetrahedronItem(ParameterizedItem *parent=0);
    IFormFactor *createFormFactor() const;
};


class BA_CORE_API_ TruncatedSphereItem : public FormFactorItem
{
    Q_OBJECT
public:
    static const QString P_RADIUS, P_HEIGHT;
    explicit TruncatedSphereItem(ParameterizedItem *parent=0);
    IFormFactor *createFormFactor() const;
};


class BA_CORE_API_ TruncatedSpheroidItem : public FormFactorItem
{
    Q_OBJECT
public:
    static const QString P_RADIUS, P_HEIGHT, P_HFC;
    explicit TruncatedSpheroidItem(ParameterizedItem *parent=0);
    IFormFactor *createFormFactor() const;
};


#endif // FORMFACTORITEMS_H

