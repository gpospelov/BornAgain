// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/RealSpaceWidgets/RealSpaceBuilder.h
//! @brief     Defines RealSpaceBuilder namespace
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef REALSPACEBUILDER_H
#define REALSPACEBUILDER_H

#include "WinDllMacros.h"
#include <QVector3D>

class SessionItem;
class RealSpaceModel;
class Shape3D;

namespace RealSpaceBuilder
{

BA_CORE_API_ void populate(RealSpaceModel* model, const SessionItem& item);

BA_CORE_API_ void populateMultiLayer(RealSpaceModel* model, const SessionItem& item,
                                     const QVector3D& origin = QVector3D());

BA_CORE_API_ void populateLayer(RealSpaceModel* model, const SessionItem& layerItem,
                                const QVector3D& origin = QVector3D());

BA_CORE_API_ void populateLayout(RealSpaceModel* model, const SessionItem& layoutItem,
                                 const QVector3D& origin = QVector3D());

BA_CORE_API_ void populateInterference(RealSpaceModel* model, const SessionItem& layoutItem);

BA_CORE_API_ void populateParticle(RealSpaceModel* model, const SessionItem& particleItem,
                                   const QVector3D& origin = QVector3D());

// compute cumulative abundances of particles
BA_CORE_API_ QVector<double> computeCumulativeAbundances(const SessionItem& layoutItem);

// No interference - random distribution of particles
BA_CORE_API_ void populateRandomDistribution(RealSpaceModel* model, const SessionItem& layoutItem);

BA_CORE_API_ QVector<QVector<double>> computeRandomDistributionLatticePositions(
        const SessionItem& layoutItem);

// InterferenceFunction2DLatticeType
BA_CORE_API_ void populateInterference2DLatticeType(RealSpaceModel* model,
                                                    const SessionItem& layoutItem);

BA_CORE_API_ QVector<QVector<double>>  getInterference2DLatticePositions(
        const SessionItem& interference2DLatticeItem);

BA_CORE_API_ QVector<QVector<double>> computeInterference2DLatticePositions(
        double l1, double l2, double l_alpha, double l_xi);
}

#endif // REALSPACEBUILDER_H
