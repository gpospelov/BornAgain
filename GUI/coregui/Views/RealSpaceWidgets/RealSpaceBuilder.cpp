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

            QMessageBox box;
            box.setText(interference->displayName());
            box.setDetailedText(interference2DLatticeItem->modelType());
            box.exec();

            // Check if 2D Lattice interference type is Basic
            if (interference2DLatticeItem->modelType() == Constants::BasicLatticeType)
            {

                double lattice_length1 = interference2DLatticeItem->
                        getItemValue(BasicLatticeItem::P_LATTICE_LENGTH1).toDouble();

                double lattice_length2 = interference2DLatticeItem->
                        getItemValue(BasicLatticeItem::P_LATTICE_LENGTH2).toDouble();

                QMessageBox box;
                box.setText(interference2DLatticeItem->displayName());
                box.setDetailedText(QString::number(lattice_length1+lattice_length2));
                box.exec();

                // Retrieving abundances of particles

                float total_abundance = 0;

                QVector<float> abundances;

                //int iter=0; // for QMessageBox

                for (auto particle : layoutItem.getItems(ParticleLayoutItem::T_PARTICLES))
                {
                    total_abundance = total_abundance +
                            particle->getItemValue(ParticleItem::P_ABUNDANCE).toFloat();

                    abundances.append(total_abundance);

                    /*
                    QMessageBox box;
                    float r = (rand()/static_cast<float>(RAND_MAX));
                    box.setText("Random number = "+QString::number(r));
                    box.setDetailedText(particle->displayName()+" abundance = "+
                      QString::number(particle->getItemValue(ParticleItem::P_ABUNDANCE).toFloat())+
                      "\nCumulative abundance = "+QString::number(abundances.at(iter)));
                    box.exec();
                    ++iter;
                    */

                }

                // defining layer_size here again as namespace is unnamed in TransformTo3D
                double layer_size = 50.0;
                double layer_thickness = 25.0;
                int quot1, quot2;
                float result1 = static_cast<float>(remquo(layer_size,lattice_length1,&quot1));
                float result2 = static_cast<float>(remquo(layer_size,lattice_length2,&quot2));

                Q_UNUSED(result1);
                Q_UNUSED(result2);

                for (int i = -quot1; i <= quot1; ++i)
                {
                    for (int j = -quot2; j <= quot2; ++j)
                    {
                        float rand_num = (rand()/static_cast<float>(RAND_MAX));
                        int k = 0;

                        for (auto particle : layoutItem.getItems(ParticleLayoutItem::T_PARTICLES))
                        {
                            // Retrieving x,y,z coordinates of the current particle
                            SessionItem* particle_position =
                                    particle->getItem(ParticleItem::P_POSITION);
                            float x = particle_position->getItemValue(VectorItem::P_X).toFloat();
                            float y = particle_position->getItemValue(VectorItem::P_Y).toFloat();
                            float z = particle_position->getItemValue(VectorItem::P_Z).toFloat();

                            float pos_x = static_cast<float>(lattice_length1*i) + x;
                            float pos_y = static_cast<float>(lattice_length2*j) + y;
                            float pos_z = z;

                            // Check if the position is inside the 3D model display coordinates
                            if(abs(pos_x) <= layer_size && abs(pos_y) <= layer_size
                                    && abs(pos_z) <= layer_thickness)
                            {
                                // Randomly display a particle at the position given its abundance
                                if (rand_num <= abundances.at(k)/total_abundance)
                                {
                                    populateParticle(model, *particle,
                                                     QVector3D(pos_x,pos_y,pos_z));
                                    break;
                                }
                                else
                                    ++k;
                            }
                        }
                    }
                }
            }

            /* // To be done!
            // Check if 2D Lattice interference type is Hexagonal
            else if (interference2DLatticeItem->modelType() == Constants::HexagonalLatticeType)
            {
                QMessageBox box;
                box.setText(interferenceItem->displayName());
                box.exec();
            }
            // Check if 2D Lattice interference type is Square
            else if (interference2DLatticeItem->modelType() == Constants::SquareLatticeType)
            {
                QMessageBox box;
                box.setText(interferenceItem->displayName());
                box.exec();
            }
            */
        }

        /* // To be done!
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
            float x = particle_position->getItemValue(VectorItem::P_X).toFloat();
            float y = particle_position->getItemValue(VectorItem::P_Y).toFloat();
            float z = particle_position->getItemValue(VectorItem::P_Z).toFloat();

            // Retrieving abundance of the current particle
            float abundance = particle->getItemValue(ParticleItem::P_ABUNDANCE).toFloat();

            QMessageBox box;
            box.setText("Values: "+QString::number(x)+" "+QString::number(y)+" "+QString::number(z));
            box.setDetailedText("Abundance: "+QString::number(abundance));
            box.exec();

            populateParticle(model, *particle, QVector3D(x,y,z));
        }
    }

    // Used to be
    //for (auto particle : layoutItem.getItems(ParticleLayoutItem::T_PARTICLES))
    //    populateParticle(model, *particle, origin);
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
