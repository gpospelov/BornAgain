// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Models/FormFactorItems.h
//! @brief     Declares FormFactorItems classes
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef FORMFACTORITEMS_H
#define FORMFACTORITEMS_H

#include "SessionItem.h"

#include <memory>

class IFormFactor;

class BA_CORE_API_ FormFactorItem : public SessionItem
{
public:
    explicit FormFactorItem(const QString &model_type)
        : SessionItem(model_type) {}
    virtual std::unique_ptr<IFormFactor> createFormFactor() const=0;
};


class BA_CORE_API_ AnisoPyramidItem : public FormFactorItem
{
public:
    static const QString P_LENGTH;
    static const QString P_WIDTH;
    static const QString P_HEIGHT;
    static const QString P_ALPHA;
    explicit AnisoPyramidItem();
    std::unique_ptr<IFormFactor> createFormFactor() const;
};


class BA_CORE_API_ BoxItem : public FormFactorItem
{
public:
    static const QString P_LENGTH;
    static const QString P_WIDTH;
    static const QString P_HEIGHT;
    explicit BoxItem();
    std::unique_ptr<IFormFactor> createFormFactor() const;
};


class BA_CORE_API_ ConeItem : public FormFactorItem
{
public:
    static const QString P_RADIUS;
    static const QString P_HEIGHT;
    static const QString P_ALPHA;
    explicit ConeItem();
    std::unique_ptr<IFormFactor> createFormFactor() const;
};


class BA_CORE_API_ Cone6Item : public FormFactorItem
{
public:
    static const QString P_BASEEDGE;
    static const QString P_HEIGHT;
    static const QString P_ALPHA;
    explicit Cone6Item();
    std::unique_ptr<IFormFactor> createFormFactor() const;
};


class BA_CORE_API_ CuboctahedronItem : public FormFactorItem
{
public:
    static const QString P_LENGTH;
    static const QString P_HEIGHT;
    static const QString P_HEIGHT_RATIO;
    static const QString P_ALPHA;
    explicit CuboctahedronItem();
    std::unique_ptr<IFormFactor> createFormFactor() const;
};


class BA_CORE_API_ DodecahedronItem : public FormFactorItem
{public:
    static const QString P_EDGE;
    explicit DodecahedronItem();
    std::unique_ptr<IFormFactor> createFormFactor() const;
};


class BA_CORE_API_ CylinderItem : public FormFactorItem
{
public:
    static const QString P_RADIUS;
    static const QString P_HEIGHT;
    explicit CylinderItem();
    std::unique_ptr<IFormFactor> createFormFactor() const;
};


class BA_CORE_API_ EllipsoidalCylinderItem : public FormFactorItem
{
public:
    static const QString P_RADIUS_X;
    static const QString P_RADIUS_Y;
    static const QString P_HEIGHT;
    explicit EllipsoidalCylinderItem();
    std::unique_ptr<IFormFactor> createFormFactor() const;
};


class BA_CORE_API_ FullSphereItem : public FormFactorItem
{
public:
    static const QString P_RADIUS;
    explicit FullSphereItem();
    std::unique_ptr<IFormFactor> createFormFactor() const;
};


class BA_CORE_API_ FullSpheroidItem : public FormFactorItem
{
public:
    static const QString P_RADIUS;
    static const QString P_HEIGHT;
    explicit FullSpheroidItem();
    std::unique_ptr<IFormFactor> createFormFactor() const;
};


class BA_CORE_API_ HemiEllipsoidItem : public FormFactorItem
{
public:
    static const QString P_RADIUS_X;
    static const QString P_RADIUS_Y;
    static const QString P_HEIGHT;
    explicit HemiEllipsoidItem();
    std::unique_ptr<IFormFactor> createFormFactor() const;
};


class BA_CORE_API_ IcosahedronItem : public FormFactorItem
{public:
    static const QString P_EDGE;
    explicit IcosahedronItem();
    std::unique_ptr<IFormFactor> createFormFactor() const;
};


class BA_CORE_API_ Prism3Item : public FormFactorItem
{
public:
    static const QString P_BASEEDGE;
    static const QString P_HEIGHT;
    explicit Prism3Item();
    std::unique_ptr<IFormFactor> createFormFactor() const;
};


class BA_CORE_API_ Prism6Item : public FormFactorItem
{
public:
    static const QString P_BASEEDGE;
    static const QString P_HEIGHT;
    explicit Prism6Item();
    std::unique_ptr<IFormFactor> createFormFactor() const;
};


class BA_CORE_API_ PyramidItem : public FormFactorItem
{
public:
    static const QString P_BASEEDGE;
    static const QString P_HEIGHT;
    static const QString P_ALPHA;
    explicit PyramidItem();
    std::unique_ptr<IFormFactor> createFormFactor() const;
};


class BA_CORE_API_ Ripple1Item : public FormFactorItem
{
public:
    static const QString P_LENGTH;
    static const QString P_WIDTH;
    static const QString P_HEIGHT;
    explicit Ripple1Item();
    std::unique_ptr<IFormFactor> createFormFactor() const;
};


class BA_CORE_API_ Ripple2Item : public FormFactorItem
{
public:
    static const QString P_LENGTH;
    static const QString P_WIDTH;
    static const QString P_HEIGHT;
    static const QString P_ASYMMETRY;
    explicit Ripple2Item();
    std::unique_ptr<IFormFactor> createFormFactor() const;
};


class BA_CORE_API_ TetrahedronItem : public FormFactorItem
{
public:
    static const QString P_BASEEDGE;
    static const QString P_HEIGHT;
    static const QString P_ALPHA;
    explicit TetrahedronItem();
    std::unique_ptr<IFormFactor> createFormFactor() const;
};


class BA_CORE_API_ TruncatedCubeItem : public FormFactorItem
{
public:
    static const QString P_LENGTH;
    static const QString P_REMOVED_LENGTH;
    explicit TruncatedCubeItem();
    std::unique_ptr<IFormFactor> createFormFactor() const;
};


class BA_CORE_API_ TruncatedSphereItem : public FormFactorItem
{
public:
    static const QString P_RADIUS;
    static const QString P_HEIGHT;
    explicit TruncatedSphereItem();
    std::unique_ptr<IFormFactor> createFormFactor() const;
};


class BA_CORE_API_ TruncatedSpheroidItem : public FormFactorItem
{
public:
    static const QString P_RADIUS;
    static const QString P_HEIGHT;
    static const QString P_HFC;
    explicit TruncatedSpheroidItem();
    std::unique_ptr<IFormFactor> createFormFactor() const;
};


#endif // FORMFACTORITEMS_H
