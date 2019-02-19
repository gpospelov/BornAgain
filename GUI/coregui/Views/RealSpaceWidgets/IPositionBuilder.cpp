// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/RealSpaceWidgets/IPositionBuilder.cpp
//! @brief     Implements subclasses of IPositionBuilder
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "IPositionBuilder.h"
#include <random>

IPositionBuilder::~IPositionBuilder() = default;

RandomPositionBuilder::RandomPositionBuilder() = default;

RandomPositionBuilder::~RandomPositionBuilder() = default;

std::vector<std::vector<double>> RandomPositionBuilder::generatePositions(double layer_size,
                                                                          double density) const
{
    std::vector<std::vector<double>> lattice_positions;
    std::vector<double> position;

    // to compute total number of particles we use the total particle density
    // and multiply by the area of the layer
    int num_particles = static_cast<int>(density * (2 * layer_size) * (2 * layer_size));

    // random generator and distribution
    std::random_device rd;  // Will be used to obtain a seed for the random number engine
    std::mt19937 gen(rd()); // Standard mersenne_twister_engine seeded with rd()
    std::uniform_real_distribution<> dis(0.0, 1.0);

    for (int i = 1; i <= num_particles; ++i) {
        // generate random x and y coordinates
        position.push_back(dis(gen) * 2 * layer_size - layer_size); // x
        position.push_back(dis(gen) * 2 * layer_size - layer_size); // y

        lattice_positions.push_back(position);
        position.clear();
    }
    return lattice_positions;
}
