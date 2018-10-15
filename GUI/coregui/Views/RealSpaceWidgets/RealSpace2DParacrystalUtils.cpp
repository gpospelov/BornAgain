// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/RealSpaceWidgets/RealSpaceBuilderUtils.h
//! @brief     Defines RealSpaceBuilderUtils namespace
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Lattice2D.h"
#include "InterferenceFunction2DParaCrystal.h"
#include "RealSpace2DParacrystalUtils.h"
#include "RealSpaceCanvas.h"

RealSpace2DParacrystalUtils::RealSpace2DParacrystalUtils()
    : m_interference2DParacrystal(nullptr)
    , m_sceneGeometry(nullptr)
{

}

RealSpace2DParacrystalUtils::~RealSpace2DParacrystalUtils()
{

}

RealSpace2DParacrystalUtils::RealSpace2DParacrystalUtils(
        const InterferenceFunction2DParaCrystal *interference2DParacrystal,
        const SceneGeometry* sceneGeometry)
{
    m_interference2DParacrystal = interference2DParacrystal;
    m_sceneGeometry = sceneGeometry;

}

std::vector<std::vector<double> > RealSpace2DParacrystalUtils::compute2DParacrystalLatticePositions()
{
    double l1 = m_interference2DParacrystal->lattice().length1();
    double l2 = m_interference2DParacrystal->lattice().length2();
    double l_alpha = m_interference2DParacrystal->lattice().latticeAngle();
    double l_xi =  m_interference2DParacrystal->lattice().rotationAngle();
    double layer_size = m_sceneGeometry->layer_size();

    // Estimate the limit n1 and n2 of the integer multiple j and i of the lattice vectors required
    // for populating particles correctly within the 3D model's boundaries
    int n1 = 0, n2 = 0;
    n1 = l1 == 0.0 ? 2 : static_cast<int>(layer_size * 2 / l1);
    n2 = l2 == 0.0 ? 2 : static_cast<int>(layer_size * 2 / l2);

    n1 = std::max(n1, n2);
    n2 = std::max(n1, n2);

    std::vector<std::vector<double>> lattice_positions;
    lattice_positions.resize(static_cast<size_t>((2 * n1 + 1)*(2 * n2 + 1)));
    for (auto& it : lattice_positions) {
        it.resize(2);
    }

    lattice_positions[0][0] = 0.0; // x coordinate of reference particle - at the origin
    lattice_positions[0][1] = 0.0; // y coordinate of reference particle - at the origin

    // random x-y pair to be drawn from correspondonding pdf
    std::pair<double, double> sampleXYpdf1, sampleXYpdf2;

    double offset_x_pdf1 = 0, offset_y_pdf1 = 0;
    double gamma_pdf1 = m_interference2DParacrystal->gammaPdf1();

    double offset_x_pdf2 = 0, offset_y_pdf2 = 0;
    double gamma_pdf2 = m_interference2DParacrystal->gammaPdf2();

    size_t index_pl1 = 0; // index for particles along +l1
    size_t index_ml1 = 0; // index for particles along -l1
    size_t index_pl2 = 0; // index for particles along +l2
    size_t index_ml2 = 0; // index for particles along -l2

    // positions of 2*n1+1 particles situated ONLY along the l1 lattice vector axis (both +/- axes)
    // wrt origin (reference particle) are stored in j = 1...2*n1 indices of lattice_positions
    for (int j = 1; j <= 2*n1; ++j) {
        // particles located along +l1 (store every odd i index of lattice_positions)
        index_pl1 = 0;
        if (j - 2 > 0)
            index_pl1 = static_cast<size_t>(j - 2);

        sampleXYpdf1 = m_interference2DParacrystal->randomSampleXYpdf1();
        offset_x_pdf1 = sampleXYpdf1.first;
        offset_y_pdf1 = sampleXYpdf1.second;

        lattice_positions[static_cast<size_t>(j)][0] =
                lattice_positions[index_pl1][0] + l1 * std::cos(l_xi) +
                offset_x_pdf1*std::cos(gamma_pdf1) +
                offset_y_pdf1*std::cos(M_PI_2 + gamma_pdf1); // x coordinate
        lattice_positions[static_cast<size_t>(j)][1] =
                lattice_positions[index_pl1][1] + l1 * std::sin(l_xi) +
                offset_x_pdf1*std::sin(gamma_pdf1) +
                offset_y_pdf1*std::sin(M_PI_2 + gamma_pdf1); // y coordinate

        // particles located along -l1 (store every even i index of lattice_positions)
        ++j;

        index_ml1 = 0;
        if (j - 2 > 0)
            index_ml1 = static_cast<size_t>(j - 2);

        sampleXYpdf1 = m_interference2DParacrystal->randomSampleXYpdf1();
        offset_x_pdf1 = sampleXYpdf1.first;
        offset_y_pdf1 = sampleXYpdf1.second;

        lattice_positions[static_cast<size_t>(j)][0] =
                lattice_positions[index_ml1][0] - l1 * std::cos(l_xi) +
                offset_x_pdf1*std::cos(gamma_pdf1) +
                offset_y_pdf1*std::cos(M_PI_2 + gamma_pdf1); // x coordinate
        lattice_positions[static_cast<size_t>(j)][1] =
                lattice_positions[index_ml1][1] - l1 * std::sin(l_xi) +
                offset_x_pdf1*std::sin(gamma_pdf1) +
                offset_y_pdf1*std::sin(M_PI_2 + gamma_pdf1); // y coordinate
    }

    // positions of 2*n2+1 particles situated ONLY along the l2 lattice vector axis (both +/- axes)
    // wrt origin (reference particle) are stored every i*(2*n1+1) index of lattice_positions
    for (int i = 1; i <= 2*n2; ++i) {
        // particles located along +l2 (store every (odd i)*(2*n1+1) index of lattice_positions)
        index_pl2 = 0;
        if (i - 2 > 0)
            index_pl2 = static_cast<size_t>(i*(2*n1+1) - 2*(2*n1+1));

        sampleXYpdf2 = m_interference2DParacrystal->randomSampleXYpdf2();
        offset_x_pdf2 = sampleXYpdf2.first;
        offset_y_pdf2 = sampleXYpdf2.second;

        lattice_positions[static_cast<size_t>(i*(2*n1+1))][0] =
                lattice_positions[index_pl2][0] + l2 * std::cos(l_alpha + l_xi) +
                offset_x_pdf2*std::cos(gamma_pdf2) +
                offset_y_pdf2*std::cos(M_PI_2 + gamma_pdf2); // x coordinate
        lattice_positions[static_cast<size_t>(i*(2*n1+1))][1] =
                lattice_positions[index_pl2][1] + l2 * std::sin(l_alpha + l_xi) +
                offset_x_pdf2*std::sin(gamma_pdf2) +
                offset_y_pdf2*std::sin(M_PI_2 + gamma_pdf2); // y coordinate

        // particles located along -l2 (store every (even i)*(2*n1+1) index of lattice_positions)
        ++i;

        index_ml2 = 0;
        if (i - 2 > 0)
            index_ml2 = static_cast<size_t>(i*(2*n1+1) - 2*(2*n1+1));

        sampleXYpdf2 = m_interference2DParacrystal->randomSampleXYpdf2();
        offset_x_pdf2 = sampleXYpdf2.first;
        offset_y_pdf2 = sampleXYpdf2.second;

        lattice_positions[static_cast<size_t>(i*(2*n1+1))][0] =
                lattice_positions[index_ml2][0] - l2 * std::cos(l_alpha + l_xi) +
                offset_x_pdf2*std::cos(gamma_pdf2) +
                offset_y_pdf2*std::cos(M_PI_2 + gamma_pdf2); // x coordinate
        lattice_positions[static_cast<size_t>(i*(2*n1+1))][1] =
                lattice_positions[index_ml2][1] - l2 * std::sin(l_alpha + l_xi) +
                offset_x_pdf2*std::sin(gamma_pdf2) +
                offset_y_pdf2*std::sin(M_PI_2 + gamma_pdf2); // y coordinate
    }


    double x_pl1 = 0, x_pl2 = 0, y_pl1 = 0, y_pl2 = 0;
    double x_ml1 = 0, x_ml2 = 0, y_ml1 = 0, y_ml2 = 0;

    // positions of the rest of the particles situated in the quadrants spanned by l1 and l2 axes
    for (int i = 1; i <= 2*n2 ; ++i) {
        for (int j = 1; j <= 2*n1 ; ++j) {
            if (i % 2 != 0) // particles located in the two +l2 quadrants
            {
                // 1st quadrant : particles located along +l1 and +l2
                index_pl1 = static_cast<size_t>(i*(2*n1+1));
                if (j - 2 > 0)
                    index_pl1 = static_cast<size_t>(i*(2*n1+1) + j - 2);

                sampleXYpdf1 = m_interference2DParacrystal->randomSampleXYpdf1();
                offset_x_pdf1 = sampleXYpdf1.first;
                offset_y_pdf1 = sampleXYpdf1.second;

                x_pl1 = lattice_positions[index_pl1][0] + l1 * std::cos(l_xi) +
                        offset_x_pdf1*std::cos(gamma_pdf1) +
                        offset_y_pdf1*std::cos(M_PI_2 + gamma_pdf1); // x coordinate
                y_pl1 = lattice_positions[index_pl1][1] + l1 * std::sin(l_xi) +
                        offset_x_pdf1*std::sin(gamma_pdf1) +
                        offset_y_pdf1*std::sin(M_PI_2 + gamma_pdf1); // y coordinate

                index_pl2 = static_cast<size_t>(j);
                if (i - 2 > 0)
                    index_pl2 = static_cast<size_t>(i*(2*n1+1) + j - 2*(2*n1+1));

                sampleXYpdf2 = m_interference2DParacrystal->randomSampleXYpdf2();
                offset_x_pdf2 = sampleXYpdf2.first;
                offset_y_pdf2 = sampleXYpdf2.second;

                x_pl2 = lattice_positions[index_pl2][0] + l2 * std::cos(l_alpha + l_xi) +
                        offset_x_pdf2*std::cos(gamma_pdf2) +
                        offset_y_pdf2*std::cos(M_PI_2 + gamma_pdf2); // x coordinate
                y_pl2 = lattice_positions[index_pl2][1] + l2 * std::sin(l_alpha + l_xi) +
                        offset_x_pdf2*std::sin(gamma_pdf2) +
                        offset_y_pdf2*std::sin(M_PI_2 + gamma_pdf2); // y coordinate

                lattice_positions[static_cast<size_t>(i*(2*n1+1)+j)][0] = (x_pl1 + x_pl2) / 2;
                lattice_positions[static_cast<size_t>(i*(2*n1+1)+j)][1] = (y_pl1 + y_pl2) / 2;

                // 2nd quadrant : particles located along -l1 and +l2
                ++j;

                index_ml1 = static_cast<size_t>(i*(2*n1+1));
                if (j - 2 > 0)
                    index_ml1 = static_cast<size_t>(i*(2*n1+1) + j - 2);

                sampleXYpdf1 = m_interference2DParacrystal->randomSampleXYpdf1();
                offset_x_pdf1 = sampleXYpdf1.first;
                offset_y_pdf1 = sampleXYpdf1.second;

                x_ml1 = lattice_positions[index_ml1][0] - l1 * std::cos(l_xi) +
                        offset_x_pdf1*std::cos(gamma_pdf1) +
                        offset_y_pdf1*std::cos(M_PI_2 + gamma_pdf1); // x coordinate
                y_ml1 = lattice_positions[index_ml1][1] - l1 * std::sin(l_xi) +
                        offset_x_pdf1*std::sin(gamma_pdf1) +
                        offset_y_pdf1*std::sin(M_PI_2 + gamma_pdf1); // y coordinate


                index_pl2 = static_cast<size_t>(j); // index for particles along +l2
                if (i - 2 > 0)
                    index_pl2 = static_cast<size_t>(i*(2*n1+1) + j - 2*(2*n1+1));

                sampleXYpdf2 = m_interference2DParacrystal->randomSampleXYpdf2();
                offset_x_pdf2 = sampleXYpdf2.first;
                offset_y_pdf2 = sampleXYpdf2.second;

                x_pl2 = lattice_positions[index_pl2][0] + l2 * std::cos(l_alpha + l_xi) +
                        offset_x_pdf2*std::cos(gamma_pdf2) +
                        offset_y_pdf2*std::cos(M_PI_2 + gamma_pdf2); // x coordinate
                y_pl2 = lattice_positions[index_pl2][1] + l2 * std::sin(l_alpha + l_xi) +
                        offset_x_pdf2*std::sin(gamma_pdf2) +
                        offset_y_pdf2*std::sin(M_PI_2 + gamma_pdf2); // y coordinate

                lattice_positions[static_cast<size_t>(i*(2*n1+1)+j)][0] = (x_ml1 + x_pl2) / 2;
                lattice_positions[static_cast<size_t>(i*(2*n1+1)+j)][1] = (y_ml1 + y_pl2) / 2;
            }
            else // particles located in the two -l2 quadrants
            {
                // 4th quadrant : particles located along +l1 and -l2
                index_pl1 = static_cast<size_t>(i*(2*n1+1));
                if (j - 2 > 0)
                    index_pl1 = static_cast<size_t>(i*(2*n1+1) + j - 2);

                sampleXYpdf1 = m_interference2DParacrystal->randomSampleXYpdf1();
                offset_x_pdf1 = sampleXYpdf1.first;
                offset_y_pdf1 = sampleXYpdf1.second;

                x_pl1 = lattice_positions[index_pl1][0] + l1 * std::cos(l_xi) +
                        offset_x_pdf1*std::cos(gamma_pdf1) +
                        offset_y_pdf1*std::cos(M_PI_2 + gamma_pdf1); // x coordinate
                y_pl1 = lattice_positions[index_pl1][1] + l1 * std::sin(l_xi) +
                        offset_x_pdf1*std::sin(gamma_pdf1) +
                        offset_y_pdf1*std::sin(M_PI_2 + gamma_pdf1); // y coordinate

                index_ml2 = static_cast<size_t>(j);
                if (i - 2 > 0)
                    index_ml2 = static_cast<size_t>(i*(2*n1+1) + j - 2*(2*n1+1));

                sampleXYpdf2 = m_interference2DParacrystal->randomSampleXYpdf2();
                offset_x_pdf2 = sampleXYpdf2.first;
                offset_y_pdf2 = sampleXYpdf2.second;

                x_ml2 = lattice_positions[index_ml2][0] - l2 * std::cos(l_alpha + l_xi) +
                        offset_x_pdf2*std::cos(gamma_pdf2) +
                        offset_y_pdf2*std::cos(M_PI_2 + gamma_pdf2); // x coordinate
                y_ml2 = lattice_positions[index_ml2][1] - l2 * std::sin(l_alpha + l_xi) +
                        offset_x_pdf2*std::sin(gamma_pdf2) +
                        offset_y_pdf2*std::sin(M_PI_2 + gamma_pdf2); // y coordinate

                lattice_positions[static_cast<size_t>(i*(2*n1+1)+j)][0] = (x_pl1 + x_ml2) / 2;
                lattice_positions[static_cast<size_t>(i*(2*n1+1)+j)][1] = (y_pl1 + y_ml2) / 2;

                // 3rd quadrant : particles located along -l1 and -l2
                ++j;

                index_ml1 = static_cast<size_t>(i*(2*n1+1));
                if (j - 2 > 0)
                    index_ml1 = static_cast<size_t>(i*(2*n1+1) + j - 2);

                sampleXYpdf1 = m_interference2DParacrystal->randomSampleXYpdf1();
                offset_x_pdf1 = sampleXYpdf1.first;
                offset_y_pdf1 = sampleXYpdf1.second;

                x_ml1 = lattice_positions[index_ml1][0] - l1 * std::cos(l_xi) +
                        offset_x_pdf1*std::cos(gamma_pdf1) +
                        offset_y_pdf1*std::cos(M_PI_2 + gamma_pdf1); // x coordinate
                y_ml1 = lattice_positions[index_ml1][1] - l1 * std::sin(l_xi) +
                        offset_x_pdf1*std::sin(gamma_pdf1) +
                        offset_y_pdf1*std::sin(M_PI_2 + gamma_pdf1); // y coordinate


                index_ml2 = static_cast<size_t>(j); // index for particles along +l2
                if (i - 2 > 0)
                    index_ml2 = static_cast<size_t>(i*(2*n1+1) + j - 2*(2*n1+1));

                sampleXYpdf2 = m_interference2DParacrystal->randomSampleXYpdf2();
                offset_x_pdf2 = sampleXYpdf2.first;
                offset_y_pdf2 = sampleXYpdf2.second;

                x_ml2 = lattice_positions[index_ml2][0] - l2 * std::cos(l_alpha + l_xi) +
                        offset_x_pdf2*std::cos(gamma_pdf2) +
                        offset_y_pdf2*std::cos(M_PI_2 + gamma_pdf2); // x coordinate
                y_ml2 = lattice_positions[index_ml2][1] - l2 * std::sin(l_alpha + l_xi) +
                        offset_x_pdf2*std::sin(gamma_pdf2) +
                        offset_y_pdf2*std::sin(M_PI_2 + gamma_pdf2); // y coordinate

                lattice_positions[static_cast<size_t>(i*(2*n1+1)+j)][0] = (x_ml1 + x_ml2) / 2;
                lattice_positions[static_cast<size_t>(i*(2*n1+1)+j)][1] = (y_ml1 + y_ml2) / 2;
            }
        }
    }
    return lattice_positions;
}
