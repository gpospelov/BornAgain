// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/RealSpaceWidgets/RealSpaceBuilderUtils.cpp
//! @brief     Implements RealSpaceBuilderUtils namespace
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "RealSpaceBuilderUtils.h"
#include "RealSpaceBuilder.h"
#include "RealSpaceModel.h"
#include "RealSpaceCanvas.h"
#include "SessionItem.h"

#include "LayerItem.h"
#include "MultiLayerItem.h"
#include "ParticleLayoutItem.h"
#include "ParticleItem.h"
#include "VectorItem.h"
#include "InterferenceFunctionItems.h"
#include "Lattice2DItems.h"
#include "Units.h"

#include "TransformationItem.h"
#include "RotationItems.h"

// compute cumulative abundances of particles
QVector<double> RealSpaceBuilderUtils::computeCumulativeAbundances(const SessionItem &layoutItem)
{
    // Retrieving abundances of particles
    double total_abundance = 0.0;
    QVector<double> cumulative_abundances;

    for (auto particle : layoutItem.getItems(ParticleLayoutItem::T_PARTICLES))
    {
        total_abundance = total_abundance +
                particle->getItemValue(ParticleItem::P_ABUNDANCE).toDouble();

        cumulative_abundances.append(total_abundance);
    }

    return cumulative_abundances;
}

// No interference - random distribution of particles
void RealSpaceBuilderUtils::populateRandomDistribution(
        RealSpaceModel *model, const SessionItem &layoutItem, const SceneGeometry &sceneGeometry,
        const RealSpaceBuilder *builder3D)
{
    // If there is no particle to populate
    if(!layoutItem.getItem(ParticleLayoutItem::T_PARTICLES))
        return;

    double layer_size = sceneGeometry.layer_size();
    double layer_thickness = std::max(sceneGeometry.layer_top_thickness(),
                                      sceneGeometry.layer_bottom_thickness());

    QVector<double> cumulative_abundances = computeCumulativeAbundances(layoutItem);

    // get the lattice positions at which to populate the particles
    QVector<QVector<double>> lattice_positions =
            computeRandomDistributionLatticePositions(layoutItem, sceneGeometry);

    srand(static_cast<unsigned int>(time(0)));

    for (QVector<double> position : lattice_positions)
    {
        // for random selection of particles based on their abundances
        double rand_num = (rand()/static_cast<double>(RAND_MAX)); // (between 0 and 1)

        int k = 0;

        for (auto particle : layoutItem.getItems(ParticleLayoutItem::T_PARTICLES))
        {
            // Retrieving local x,y,z offset from the lattice point for the current particle
            SessionItem* particle_position = particle->getItem(ParticleItem::P_POSITION);
            double x = particle_position->getItemValue(VectorItem::P_X).toDouble();
            double y = particle_position->getItemValue(VectorItem::P_Y).toDouble();
            double z = particle_position->getItemValue(VectorItem::P_Z).toDouble();

            // lattice position + offset
            double pos_x = position[0] + x;
            double pos_y = position[1] + y;
            double pos_z = z;

            // Check if the position lies within the boundaries of the 3D model
            if (std::abs(pos_x) <= layer_size && std::abs(pos_y) <= layer_size
                    && std::abs(pos_z) <= layer_thickness)
            {
                // Randomly display a particle at the position, given its normalized abundance
                if (rand_num <= cumulative_abundances.at(k)/cumulative_abundances.last())
                {
                    builder3D->populateParticle(model, *particle,
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

QVector<QVector<double> > RealSpaceBuilderUtils::computeRandomDistributionLatticePositions(
        const SessionItem &layoutItem, const SceneGeometry& sceneGeometry)
{
    double layer_size = sceneGeometry.layer_size();

    QVector<QVector<double>> lattice_positions;

    QVector<double> position;

    // to compute total number of particles we use the total particle density
    // and multiply by the area of the layer
    double total_density = layoutItem.getItemValue(ParticleLayoutItem::P_TOTAL_DENSITY).toDouble();
    int num_particles = static_cast<int>(total_density * (2*layer_size) * (2*layer_size));

    for (int i = 1; i <= num_particles; ++i)
    {
        // For calculating lattice coordinates we use random x and y coordinates
        position.push_back((rand()/static_cast<double>(RAND_MAX))*2*layer_size - layer_size); // x
        position.push_back((rand()/static_cast<double>(RAND_MAX))*2*layer_size - layer_size); // y

        // no need for z coordinate as all lattice positions are calculated in the xy plane

        lattice_positions.push_back(position);

        position.clear();
    }

    return lattice_positions;
}


// InterferenceFunction2DLatticeType
void RealSpaceBuilderUtils::populateInterference2DLatticeType(
        RealSpaceModel *model, const SessionItem& layoutItem, const SceneGeometry& sceneGeometry,
        const RealSpaceBuilder *builder3D)
{
    double layer_size = sceneGeometry.layer_size();
    double layer_thickness = std::max(sceneGeometry.layer_top_thickness(),
                                      sceneGeometry.layer_bottom_thickness());

    auto interference = layoutItem.getItem(ParticleLayoutItem::T_INTERFERENCE);

    auto interference2DLatticeItem =
            interference->getGroupItem(InterferenceFunction2DLatticeItem::P_LATTICE_TYPE);

    QVector<double> cumulative_abundances = computeCumulativeAbundances(layoutItem);

    srand(static_cast<unsigned int>(time(0)));

    // get the lattice positions at which to populate the particles
    QVector<QVector<double>> lattice_positions =
            getInterference2DLatticePositions(*interference2DLatticeItem, sceneGeometry);

    for (QVector<double> position : lattice_positions)
    {
        // for random selection of particles based on their abundances
        double rand_num = (rand()/static_cast<double>(RAND_MAX)); // (between 0 and 1)

        int k = 0;

        for (auto particle : layoutItem.getItems(ParticleLayoutItem::T_PARTICLES))
        {
            // Retrieving local x,y,z offset from the lattice point for the current particle
            SessionItem* particle_position = particle->getItem(ParticleItem::P_POSITION);
            double x = particle_position->getItemValue(VectorItem::P_X).toDouble();
            double y = particle_position->getItemValue(VectorItem::P_Y).toDouble();
            double z = particle_position->getItemValue(VectorItem::P_Z).toDouble();

            // lattice position + offset
            double pos_x = position[0] + x;
            double pos_y = position[1] + y;
            double pos_z = z;

            // Check if the position lies within the boundaries of the 3D model
            if (std::abs(pos_x) <= layer_size && std::abs(pos_y) <= layer_size
                    && std::abs(pos_z) <= layer_thickness)
            {
                // Randomly display a particle at the position, given its normalized abundance
                if (rand_num <= cumulative_abundances.at(k)/cumulative_abundances.last())
                {
                    builder3D->populateParticle(model, *particle,
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

    cumulative_abundances.clear();
}

QVector<QVector<double>> RealSpaceBuilderUtils::getInterference2DLatticePositions(
        const SessionItem &interference2DLatticeItem, const SceneGeometry &sceneGeometry)
{
    double l1 = 0.0, l2 = 0.0, l_alpha = 0.0, l_xi = 0.0;

    // If 2D Lattice interference type is Basic
    if (interference2DLatticeItem.modelType() == Constants::BasicLatticeType)
    {
        // lattice vector 1
        l1 = interference2DLatticeItem.getItemValue(BasicLatticeItem::P_LATTICE_LENGTH1).toDouble();

        // lattice vector 2
        l2 = interference2DLatticeItem.getItemValue(BasicLatticeItem::P_LATTICE_LENGTH2).toDouble();

        // lattice angle (between l1 and l2)
        l_alpha = interference2DLatticeItem.getItemValue(
                    BasicLatticeItem::P_LATTICE_ANGLE).toDouble();

        // lattice rotation angle (between x axis and l1)
        l_xi = interference2DLatticeItem.getItemValue(
                    BasicLatticeItem::P_LATTICE_ROTATION_ANGLE).toDouble();
    }

    // If 2D Lattice interference type is Hexagonal
    else if (interference2DLatticeItem.modelType() == Constants::HexagonalLatticeType)
    {
        l1 = interference2DLatticeItem.getItemValue(
                    HexagonalLatticeItem::P_LATTICE_LENGTH).toDouble();

        l2 = l1;

        l_alpha = 120.0; // 120 degrees for a Hexagonal lattice

        l_xi = interference2DLatticeItem.getItemValue(
                    HexagonalLatticeItem::P_LATTICE_ROTATION_ANGLE).toDouble();
    }

    // If 2D Lattice interference type is Square
    else if (interference2DLatticeItem.modelType() == Constants::SquareLatticeType)
    {
        l1 = interference2DLatticeItem.getItemValue(
                    SquareLatticeItem::P_LATTICE_LENGTH).toDouble();

        l2 = l1;

        l_alpha = 90.0; // 90 degrees for a Square lattice

        l_xi = interference2DLatticeItem.getItemValue(
                    SquareLatticeItem::P_LATTICE_ROTATION_ANGLE).toDouble();
    }

    return computeInterference2DLatticePositions(l1, l2, l_alpha, l_xi, sceneGeometry);
}

QVector<QVector<double>> RealSpaceBuilderUtils::computeInterference2DLatticePositions(
        double l1, double l2, double l_alpha, double l_xi, const SceneGeometry &sceneGeometry)
{
    double layer_size = sceneGeometry.layer_size();

    QVector<QVector<double>> lattice_positions;

    QVector<double> position;

    // Estimate the limit 'n' of the integer multiple i and j of the lattice vectors required in
    // order to populate particles correctly within the 3D model's boundaries
    int n1 = static_cast<int>(layer_size*2)/
            static_cast<int>(l1*std::cos(Units::deg2rad(l_xi)));

    int n2 = static_cast<int>(layer_size*2)/
            static_cast<int>(l2*std::sin(Units::deg2rad(l_alpha+l_xi)));

    // Choosing the larger between n1 and n2
    int n = std::max(n1,n2);

    for (int i = -n; i <= n; ++i)
    {
        for (int j = -n; j <= n; ++j)
        {
            // For calculating lattice position vector v, we use: v = i*l1 + j*l2
            // where l1 and l2 are the lattice vectors,
            // i and j are the integer multiples of l1 and l2 respectively

            position.push_back(i*l1*std::cos(Units::deg2rad(l_xi))+
                               j*l2*std::cos(Units::deg2rad(l_alpha + l_xi))); // x coordinate
            position.push_back(i*l1*std::sin(Units::deg2rad(l_xi))+
                               j*l2*std::sin(Units::deg2rad(l_alpha + l_xi))); // y coordinate

            // no need for z coordinate as all lattice positions are calculated in the xy plane

            lattice_positions.push_back(position);

            position.clear();
        }
    }

    return lattice_positions;
}

QVector3D RealSpaceBuilderUtils::implementParticleRotation(const SessionItem &particleItem)
{
    // defined in accordance with QQuaternion::fromEulerAngles function parameters
    float x_angle = 0.0f;
    float y_angle = 0.0f;
    float z_angle = 0.0f;

    auto transformationItem = particleItem.getItem(ParticleItem::T_TRANSFORMATION);

    auto rotItem = transformationItem->getGroupItem(TransformationItem::P_ROT);

    if(rotItem->modelType() == Constants::ZRotationType)
        z_angle = rotItem->getItemValue(ZRotationItem::P_ANGLE).toFloat(); // about z-axis
    else if(rotItem->modelType() == Constants::XRotationType)
        x_angle = rotItem->getItemValue(XRotationItem::P_ANGLE).toFloat(); // about x-axis
    else if(rotItem->modelType() == Constants::YRotationType)
        y_angle = rotItem->getItemValue(YRotationItem::P_ANGLE).toFloat(); // about y-axis
    else if(rotItem->modelType() == Constants::EulerRotationType)
    {
        z_angle = rotItem->getItemValue(EulerRotationItem::P_ALPHA).toFloat();
        y_angle = rotItem->getItemValue(EulerRotationItem::P_BETA).toFloat();
        x_angle = rotItem->getItemValue(EulerRotationItem::P_GAMMA).toFloat();
    }

    return QVector3D(x_angle, y_angle, z_angle);
}
