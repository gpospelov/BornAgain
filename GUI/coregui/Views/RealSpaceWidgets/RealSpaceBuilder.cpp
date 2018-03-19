// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/RealSpaceWidgets/RealSpaceBuilder.cpp
//! @brief     Implements RealSpaceBuilder namespace
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "RealSpaceBuilder.h"
#include "RealSpaceModel.h"
#include "SessionItem.h"
#include "LayerItem.h"
#include "ExternalProperty.h"
#include "MultiLayerItem.h"
#include "TransformTo3D.h"
#include "ParticleLayoutItem.h"
#include <ba3d/model/layer.h>
#include <QDebug>

#include "ParticleItem.h"
#include "VectorItem.h"
#include "InterferenceFunctionItems.h"
#include "Lattice2DItems.h"
#include "Units.h"

#include <QMessageBox>

void RealSpaceBuilder::populate(RealSpaceModel* model, const SessionItem& item)
{
    model->defCamPos = RealSpace::Camera::Position(
        RealSpace::Vector3D(0, -140, 90),   // eye
        RealSpace::Vector3D(0, 0, 0),       // center
        RealSpace::Vector3D::_z);             // up vector

    if (item.modelType() == Constants::MultiLayerType)
        populateMultiLayer(model, item);

    else if (item.modelType() == Constants::LayerType)
        populateLayer(model, item);

    else if (item.modelType() == Constants::ParticleLayoutType)
        populateLayout(model, item);

    else if (item.modelType() == Constants::ParticleType)
        populateParticle(model, item);
}

void RealSpaceBuilder::populateMultiLayer(RealSpaceModel* model, const SessionItem& item,
                                          const QVector3D&)
{
    double total_height(0.0);
    int index(0);
    for (auto layer : item.getItems(MultiLayerItem::T_LAYERS)) {

        if(index != 0)
            total_height += TransformTo3D::visualLayerThickness(*layer);

        populateLayer(model, *layer, QVector3D(0, 0, -total_height));
        ++index;
    }

}

void RealSpaceBuilder::populateLayer(RealSpaceModel* model, const SessionItem& layerItem,
                                     const QVector3D& origin)
{
    auto layer = TransformTo3D::createLayer(layerItem, origin);
    model->addBlend(layer.release());

    for (auto layout : layerItem.getItems(LayerItem::T_LAYOUTS))
        populateLayout(model, *layout, origin);
}

void RealSpaceBuilder::populateLayout(RealSpaceModel* model, const SessionItem& layoutItem,
                                      const QVector3D& origin)
{
    Q_ASSERT(layoutItem.modelType() == Constants::ParticleLayoutType);

    Q_UNUSED(origin);

    // Check if there is interference
    if (auto interference = layoutItem.getItem(ParticleLayoutItem::T_INTERFERENCE))
    {
        // Check if interference type is 2D Lattice
        if (interference->modelType() == Constants::InterferenceFunction2DLatticeType)
        {

            auto interference2DLatticeItem =
                    interference->getGroupItem(InterferenceFunction2DLatticeItem::P_LATTICE_TYPE);

            /*
            QMessageBox box;
            box.setText(interference->displayName());
            box.setDetailedText(interference2DLatticeItem->modelType());
            box.exec();
            */

            // Check if 2D Lattice interference type is Basic
            if (interference2DLatticeItem->modelType() == Constants::BasicLatticeType)
            {
                // lattice length 1
                double l1 = interference2DLatticeItem->
                        getItemValue(BasicLatticeItem::P_LATTICE_LENGTH1).toDouble();

                // lattice length 2
                double l2 = interference2DLatticeItem->
                        getItemValue(BasicLatticeItem::P_LATTICE_LENGTH2).toDouble();

                // lattice angle
                double l_angle = interference2DLatticeItem->
                        getItemValue(BasicLatticeItem::P_LATTICE_ANGLE).toDouble();

                // lattice rotation angle
                double l_rot_angle = interference2DLatticeItem->
                        getItemValue(BasicLatticeItem::P_LATTICE_ROTATION_ANGLE).toDouble();

                /*
                QMessageBox box;
                box.setText(interference2DLatticeItem->displayName());
                box.setDetailedText(QString::number(l1+l2));
                box.exec();
                */

                populateInterference2DBasic(model, layoutItem, l1, l2, l_angle, l_rot_angle);
            }

            // Check if 2D Lattice interference type is Hexagonal
            else if (interference2DLatticeItem->modelType() == Constants::HexagonalLatticeType)
            {
                // lattice length
                double l = interference2DLatticeItem->
                        getItemValue(HexagonalLatticeItem::P_LATTICE_LENGTH).toDouble();

                // lattice angle
                double l_alpha = 60.0; // 60 degrees for a Hexagonal lattice

                // lattice rotation angle
                double l_xi = interference2DLatticeItem->
                        getItemValue(HexagonalLatticeItem::P_LATTICE_ROTATION_ANGLE).toDouble();

                /*
                QMessageBox box;
                box.setText(interference2DLatticeItem->displayName());
                box.setDetailedText(QString::number(l1+l2));
                box.exec();
                */

                // l1 = l2 = l (lattice vectors are of equal length)
                populateInterference2DBasic(model, layoutItem, l, l, l_alpha, l_xi);
            }


            // Check if 2D Lattice interference type is Square
            else if (interference2DLatticeItem->modelType() == Constants::SquareLatticeType)
            {
                // lattice length
                double l = interference2DLatticeItem->
                        getItemValue(SquareLatticeItem::P_LATTICE_LENGTH).toDouble();

                // lattice angle
                double l_alpha = 90.0; // 90 degrees for a Square lattice

                // lattice rotation angle
                double l_xi = interference2DLatticeItem->
                        getItemValue(SquareLatticeItem::P_LATTICE_ROTATION_ANGLE).toDouble();

                /*
                QMessageBox box;
                box.setText(interference2DLatticeItem->displayName());
                box.setDetailedText(QString::number(l1+l2));
                box.exec();
                */

                // l1 = l2 = l (lattice vectors are of equal length)
                populateInterference2DBasic(model, layoutItem, l, l, l_alpha, l_xi);
            }

        }

        /* // To be done
        // Check if interference type is 1D Lattice
        else if (interference->modelType() == Constants::InterferenceFunction1DLatticeType)
        {
            QMessageBox box;
            box.setText(interference->displayName());
            box.exec();
        }
        // Check if interference type is 2D ParaCrystal
        else if (interference->modelType() == Constants::InterferenceFunction2DParaCrystalType)
        {
            QMessageBox box;
            box.setText(interference->displayName());
            box.exec();
        }
        // Check if interference type is Radial ParaCrystal
        else if (interference->modelType() == Constants::InterferenceFunctionRadialParaCrystalType)
        {
            QMessageBox box;
            box.setText(interference->displayName();
            box.exec();
        }
        */
    }
    // Check if there is NO interference
    else
    {
        for (auto particle : layoutItem.getItems(ParticleLayoutItem::T_PARTICLES))
        {

            //auto particle_position_str = particle->getItemValue(ParticleItem::P_POSITION);

            // Retrieving x,y,z coordinates of the current particle
            SessionItem* particle_position = particle->getItem(ParticleItem::P_POSITION);
            double x = particle_position->getItemValue(VectorItem::P_X).toDouble();
            double y = particle_position->getItemValue(VectorItem::P_Y).toDouble();
            double z = particle_position->getItemValue(VectorItem::P_Z).toDouble();

            QMessageBox box;
            box.setText("Values: "+QString::number(x)+" "+QString::number(y)+" "+QString::number(z));
            box.exec();

            populateParticle(model, *particle, QVector3D(x,y,z));
        }
    }

    // Used to be
    //for (auto particle : layoutItem.getItems(ParticleLayoutItem::T_PARTICLES))
    //    populateParticle(model, *particle, origin);
}

void RealSpaceBuilder::populateInterference2DBasic(RealSpaceModel* model,
                                                   const SessionItem& layoutItem, double l1,
                                                   double l2, double l_alpha, double l_xi)
{
    // Retrieving abundances of particles

    double total_abundance = 0;

    QVector<double> abundances;

    for (auto particle : layoutItem.getItems(ParticleLayoutItem::T_PARTICLES))
    {
        total_abundance = total_abundance +
                particle->getItemValue(ParticleItem::P_ABUNDANCE).toDouble();

        abundances.append(total_abundance);

    }

    // defining layer_size here again as namespace is unnamed in TransformTo3D
    double layer_size = 50.0;
    double layer_thickness = 25.0;

    // The following seqment with quot is to calculate the limits of the integer multiple of the
    // lattice vectors required in order to populate correctly the 3D model's interference lattice

    //int quot1, quot2;
    //float result1 = static_cast<float>(remquo((layer_size*2),
    //                                   (l1*cos(Units::deg2rad(l_xi))),&quot1));
    //float result2 = static_cast<float>(remquo((layer_size*2),
    //                            (l2*sin(Units::deg2rad(l_alpha+l_xi))),&quot2));

    int quot1 = static_cast<int>(layer_size*2)/
            static_cast<int>(l1*cos(Units::deg2rad(l_xi)));


    int quot2 = static_cast<int>(layer_size*2)/
            static_cast<int>(l2*sin(Units::deg2rad(l_alpha+l_xi)));

    int quot = quot1 >= quot2 ? quot1: quot2;

    /*
    QMessageBox mbox;
    mbox.setText((QString::number(quot1)+" "+QString::number(quot2)));
    mbox.setDetailedText((QString::number(l1*cos(Units::deg2rad(l_xi)))+
                  " "+QString::number((layer_size*2)/(l2*sin(Units::deg2rad(l_alpha+l_xi))))));

    mbox.exec();
    */

    for (int i = -quot; i <= quot; ++i)
    {
        for (int j = -quot; j <= quot; ++j)
        {
            double rand_num = (rand()/static_cast<double>(RAND_MAX));

            int k = 0;

            for (auto particle : layoutItem.getItems(ParticleLayoutItem::T_PARTICLES))
            {
                // Retrieving local x,y,z offset from the lattice point for the current particle
                SessionItem* particle_position =
                        particle->getItem(ParticleItem::P_POSITION);
                double x = particle_position->getItemValue(VectorItem::P_X).toDouble();
                double y = particle_position->getItemValue(VectorItem::P_Y).toDouble();
                double z = particle_position->getItemValue(VectorItem::P_Z).toDouble();

                double pos_x = i*l1*cos(Units::deg2rad(l_xi))+
                        j*l2*cos(Units::deg2rad(l_alpha + l_xi)) + x;

                double pos_y = i*l1*sin(Units::deg2rad(l_xi))+
                        j*l2*sin(Units::deg2rad(l_alpha + l_xi)) + y;

                double pos_z = z;

                // Check if the position lies within the boundaries of the 3D model
                if(abs(pos_x) <= layer_size && abs(pos_y) <= layer_size
                        && abs(pos_z) <= layer_thickness)
                {
                    // Randomly display a particle at the position given its abundance
                    if (rand_num <= abundances.at(k)/total_abundance)
                    {
                        populateParticle(model, *particle,
                                         QVector3D(static_cast<float>(pos_x),
                                                   static_cast<float>(pos_y),
                                                   static_cast<float>(pos_z)));
                        break;
                    }
                    else
                        ++k;
                }
            }
        }
    }
}

void RealSpaceBuilder::populateParticle(RealSpaceModel* model, const SessionItem& particleItem,
                                        const QVector3D& origin)
{
    Q_ASSERT(particleItem.modelType() == Constants::ParticleType);

    auto particle = TransformTo3D::createParticle(particleItem);

    if (particle) {
        particle->transform(RealSpace::Vector3D::_0, RealSpace::Vector3D(origin.x(), origin.y(), origin.z()));
        model->add(particle.release());
    }
}
