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

namespace {
    // defining layer size and thickness (taken from namespace in TransformTo3D)
    const double layer_size = 50.0;
    const double layer_thickness = 25.0;
}

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

        populateLayer(model, *layer, QVector3D(0, 0, static_cast<float>(-total_height)));
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

    // If there is interference
    if (auto interference = layoutItem.getItem(ParticleLayoutItem::T_INTERFERENCE))
    {
        // If interference type is 2D Lattice
        if (interference->modelType() == Constants::InterferenceFunction2DLatticeType)
        {
            auto interference2DLatticeItem =
                    interference->getGroupItem(InterferenceFunction2DLatticeItem::P_LATTICE_TYPE);

            // If 2D Lattice interference type is Basic
            if (interference2DLatticeItem->modelType() == Constants::BasicLatticeType)
            {
                // lattice vector 1
                double l1 = interference2DLatticeItem->
                        getItemValue(BasicLatticeItem::P_LATTICE_LENGTH1).toDouble();

                // lattice vector 2
                double l2 = interference2DLatticeItem->
                        getItemValue(BasicLatticeItem::P_LATTICE_LENGTH2).toDouble();

                // lattice angle
                double l_alpha = interference2DLatticeItem->
                        getItemValue(BasicLatticeItem::P_LATTICE_ANGLE).toDouble();

                // lattice rotation angle
                double l_xi = interference2DLatticeItem->
                        getItemValue(BasicLatticeItem::P_LATTICE_ROTATION_ANGLE).toDouble();

                populateInterference2DBasic(model, layoutItem, l1, l2, l_alpha, l_xi);
            }

            // If 2D Lattice interference type is Hexagonal
            else if (interference2DLatticeItem->modelType() == Constants::HexagonalLatticeType)
            {
                double l = interference2DLatticeItem->
                        getItemValue(HexagonalLatticeItem::P_LATTICE_LENGTH).toDouble();

                double l_alpha = 120.0; // 120 degrees for a Hexagonal lattice

                double l_xi = interference2DLatticeItem->
                        getItemValue(HexagonalLatticeItem::P_LATTICE_ROTATION_ANGLE).toDouble();

                // l1 = l2 = l (lattice vectors are of equal length)
                populateInterference2DBasic(model, layoutItem, l, l, l_alpha, l_xi);
            }

            // If 2D Lattice interference type is Square
            else if (interference2DLatticeItem->modelType() == Constants::SquareLatticeType)
            {
                double l = interference2DLatticeItem->
                        getItemValue(SquareLatticeItem::P_LATTICE_LENGTH).toDouble();

                double l_alpha = 90.0; // 90 degrees for a Square lattice

                double l_xi = interference2DLatticeItem->
                        getItemValue(SquareLatticeItem::P_LATTICE_ROTATION_ANGLE).toDouble();

                // l1 = l2 = l (lattice vectors are of equal length)
                populateInterference2DBasic(model, layoutItem, l, l, l_alpha, l_xi);
            }
        }

        /*
        // The following segment is yet to be implemented

        // If interference type is 1D Lattice
        else if (interference->modelType() == Constants::InterferenceFunction1DLatticeType)
        {
            QMessageBox box;
            box.setText(interference->displayName());
            box.exec();
        }

        // If interference type is 2D ParaCrystal
        else if (interference->modelType() == Constants::InterferenceFunction2DParaCrystalType)
        {
            QMessageBox box;
            box.setText(interference->displayName());
            box.exec();
        }

        // If interference type is Radial ParaCrystal
        else if (interference->modelType() == Constants::InterferenceFunctionRadialParaCrystalType)
        {
            QMessageBox box;
            box.setText(interference->displayName();
            box.exec();
        }

        */

    }

    // If there is NO interference
    else
    {
        populateRandomDistribution(model, layoutItem);
    }
}

void RealSpaceBuilder::populateInterference2DBasic(RealSpaceModel* model,
                                                   const SessionItem& layoutItem, double l1,
                                                   double l2, double l_alpha, double l_xi)
{
    // Retrieving abundances of particles
    double total_abundance = 0;
    QVector<double> cumulative_abundances;

    for (auto particle : layoutItem.getItems(ParticleLayoutItem::T_PARTICLES))
    {
        total_abundance = total_abundance +
                particle->getItemValue(ParticleItem::P_ABUNDANCE).toDouble();

        cumulative_abundances.append(total_abundance);
    }

    // Estimate the limit 'n' of the integer multiple i and j of the lattice vectors required in
    // order to populate particles correctly within the 3D model's boundaries
    int n1 = static_cast<int>(layer_size*2)/
            static_cast<int>(l1*std::cos(Units::deg2rad(l_xi)));

    int n2 = static_cast<int>(layer_size*2)/
            static_cast<int>(l2*std::sin(Units::deg2rad(l_alpha+l_xi)));

    // Choosing the larger between n1 and n2
    int n = std::max(n1,n2);

    srand(static_cast<unsigned int>(time(0)));

    for (int i = -n; i <= n; ++i)
    {
        for (int j = -n; j <= n; ++j)
        {
            // for random selection of particles based on their abundances
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

                // For calculating lattice coordinates we use:
                // v = i*l1 + j*l2
                // where v is the position vector of the lattice point
                // l1 and l2 are the lattice vectors
                // i and j are the integer multiples of l1 and l2 respectively

                double pos_x = i*l1*std::cos(Units::deg2rad(l_xi))+
                        j*l2*std::cos(Units::deg2rad(l_alpha + l_xi)) + x;

                double pos_y = i*l1*std::sin(Units::deg2rad(l_xi))+
                        j*l2*std::sin(Units::deg2rad(l_alpha + l_xi)) + y;

                double pos_z = z;

                // Check if the position lies within the boundaries of the 3D model
                if (std::abs(pos_x) <= layer_size && std::abs(pos_y) <= layer_size
                        && std::abs(pos_z) <= layer_thickness)
                {
                    // Randomly display a particle at the position, given its abundance
                    if (rand_num <= cumulative_abundances.at(k)/total_abundance)
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

    cumulative_abundances.clear();
}

void RealSpaceBuilder::populateRandomDistribution(RealSpaceModel *model, const SessionItem &layoutItem)
{
    // Retrieving abundances of particles
    double total_abundance = 0;
    QVector<double> cumulative_abundances;

    for (auto particle : layoutItem.getItems(ParticleLayoutItem::T_PARTICLES))
    {
        total_abundance = total_abundance +
                particle->getItemValue(ParticleItem::P_ABUNDANCE).toDouble();

        cumulative_abundances.append(total_abundance);
    }

    // to compute total number of particles we use the total particle density
    // and multiply by the area of the layer
    double total_density = layoutItem.getItemValue(ParticleLayoutItem::P_TOTAL_DENSITY).toDouble();
    int num_particles = static_cast<int>(total_density * (2*layer_size) * (2*layer_size));

    srand(static_cast<unsigned int>(time(0)));

    for (int i = 1; i <= num_particles; ++i)
    {
        // for random selection of particles based on their abundances
        double rand_num = (rand()/static_cast<double>(RAND_MAX));

        // for random x, y coordinates of the particle on the layer
        double rand_x = (rand()/static_cast<double>(RAND_MAX))*2*layer_size - layer_size;
        double rand_y = (rand()/static_cast<double>(RAND_MAX))*2*layer_size - layer_size;

        int k = 0;

        for (auto particle : layoutItem.getItems(ParticleLayoutItem::T_PARTICLES))
        {
            // Retrieving local x,y,z offset from the lattice point for the current particle
            SessionItem* particle_position =
                    particle->getItem(ParticleItem::P_POSITION);
            double x = particle_position->getItemValue(VectorItem::P_X).toDouble();
            double y = particle_position->getItemValue(VectorItem::P_Y).toDouble();
            double z = particle_position->getItemValue(VectorItem::P_Z).toDouble();

            // For calculating lattice coordinates we use random x and y coordinates
            double pos_x = rand_x + x;
            double pos_y = rand_y + y;
            double pos_z = z;

            // Check if the position lies within the boundaries of the 3D model
            if (std::abs(pos_x) <= layer_size && std::abs(pos_y) <= layer_size
                    && std::abs(pos_z) <= layer_thickness)
            {
                // Randomly display a particle at the position, given its abundance
                if (rand_num <= cumulative_abundances.at(k)/total_abundance)
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

void RealSpaceBuilder::populateParticle(RealSpaceModel* model, const SessionItem& particleItem,
                                        const QVector3D& origin)
{
    Q_ASSERT(particleItem.modelType() == Constants::ParticleType);

    auto particle = TransformTo3D::createParticle(particleItem);

    if (particle) {
        particle->transform(RealSpace::Vector3D::_0, RealSpace::Vector3D(origin.x(),
                                                                         origin.y(),
                                                                         origin.z()));
        model->add(particle.release());
    }
}
