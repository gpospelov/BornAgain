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
#include "InterferenceFunctions.h"
#include <cmath>
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

Lattice1DPositionBuilder::Lattice1DPositionBuilder(const InterferenceFunction1DLattice* p_iff)
    : mp_iff(p_iff)
{
}

Lattice1DPositionBuilder::~Lattice1DPositionBuilder() = default;

std::vector<std::vector<double>> Lattice1DPositionBuilder::generatePositions(double layer_size,
                                                                             double) const
{
    std::vector<std::vector<double>> lattice_positions;
    std::vector<double> position;

    auto lattice_pars = mp_iff->getLatticeParameters();
    double length = lattice_pars.m_length;
    double xi = lattice_pars.m_xi;

    // Take the maximum possible integer multiple of the lattice vector required
    // for populating particles correctly within the 3D model's boundaries
    int n1 = length == 0.0 ? 2 : static_cast<int>(layer_size * std::sqrt(2.0) / length);

    for (int i = -n1; i <= n1; ++i) {
        // For calculating lattice position vector v, we use: v = i*l1
        // where l1 is the lattice vector
        position.push_back(i * length * std::cos(xi));
        position.push_back(i * length * std::sin(xi));

        lattice_positions.push_back(position);
        position.clear();
    }
    return lattice_positions;
}
