// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/RealSpaceWidgets/RealSpaceBuilder.h
//! @brief     Defines class RealSpaceBuilder
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
#include <QWidget>
#include <QVector3D>

class SessionItem;
class RealSpaceModel;
class Shape3D;

class SceneGeometry;

class BA_CORE_API_ RealSpaceBuilder : public QWidget
{
    Q_OBJECT

public:
    RealSpaceBuilder(QWidget* parent = 0);

    ~RealSpaceBuilder();

    void populate(RealSpaceModel* model, const SessionItem& item,
                  const SceneGeometry& sceneGeometry);

    void populateMultiLayer(RealSpaceModel* model, const SessionItem& item,
                            const SceneGeometry& sceneGeometry,
                            const QVector3D& origin = QVector3D());

    void populateLayer(RealSpaceModel* model, const SessionItem& layerItem,
                       const SceneGeometry& sceneGeometry, const QVector3D& origin = QVector3D());

    void populateLayout(RealSpaceModel* model, const SessionItem& layoutItem,
                        const SceneGeometry& sceneGeometry, const QVector3D& origin = QVector3D());

    void populateInterference(RealSpaceModel* model, const SessionItem& layoutItem,
                              const SceneGeometry& sceneGeometry);

    void populateParticle(RealSpaceModel* model, const SessionItem& particleItem,
                          const QVector3D& origin = QVector3D()) const;

};

#endif // REALSPACEBUILDER_H
