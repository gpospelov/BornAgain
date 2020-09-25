// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/StandardSamples/FeNiBiLayerBuilder.h
//! @brief     Defines various sample builder classes to
//!            test polarized specular computations
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2020
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_CORE_STANDARDSAMPLES_FENIBILAYERBUILDER_H
#define BORNAGAIN_CORE_STANDARDSAMPLES_FENIBILAYERBUILDER_H

#include "Core/Basics/Complex.h"
#include "Core/Basics/Units.h"
#include "Core/Multilayer/ISampleBuilder.h"
#include "Core/Multilayer/MultiLayer.h"
#include "Core/Multilayer/RoughnessModels.h"

//! Creates the sample demonstrating an Fe-Ni Bilayer with and without roughness
//! @ingroup standard_samples
class FeNiBiLayer
{
    static constexpr auto sldFe = complex_t{8.02e-06, 0};
    static constexpr auto sldAu = complex_t{4.6665e-6, 0};
    static constexpr auto sldNi = complex_t{9.4245e-06, 0};

    int NBiLayers;
    double angle;
    double magnetizationMagnitude;
    double thicknessFe;
    double thicknessNi;
    double sigmaRoughness;
    int effectiveSLD;
    RoughnessModel roughnessModel;

    kvector_t magnetizationVector;

    std::unique_ptr<MultiLayer> sample;

    std::unique_ptr<MultiLayer> constructSample();

public:
    class Options
    {
        friend class FeNiBiLayer;

    public:
        int _NBiLayers = 4;
        double _angle = 0.;
        double _magnetizationMagnitude = 1.e7;
        double _thicknessFe = 100. * Units::angstrom;
        double _thicknessNi = 40. * Units::angstrom;
        double _sigmaRoughness = 0.;
        int _effectiveSLD = 0;
        RoughnessModel _roughnessModel = RoughnessModel::TANH;

        Options() {}
        Options NBiLayers(int n)
        {
            _NBiLayers = n;
            return *this;
        }
        Options angle(double angle)
        {
            _angle = angle;
            return *this;
        }
        Options magnetizationMagnitude(double M)
        {
            _magnetizationMagnitude = M;
            return *this;
        }
        Options thicknessFe(double t)
        {
            _thicknessFe = t;
            return *this;
        }
        Options thicknessNi(double t)
        {
            _thicknessNi = t;
            return *this;
        }
        Options sigmaRoughness(double r)
        {
            _sigmaRoughness = r;
            return *this;
        }
        Options effectiveSLD(int i)
        {
            _effectiveSLD = i;
            return *this;
        }
        Options roughnessModel(RoughnessModel rm)
        {
            _roughnessModel = rm;
            return *this;
        }
    };

    FeNiBiLayer() : FeNiBiLayer(Options()) {}

    FeNiBiLayer(Options opt)
        : NBiLayers(opt._NBiLayers), angle(opt._angle),
          magnetizationMagnitude(opt._magnetizationMagnitude), thicknessFe(opt._thicknessFe),
          thicknessNi(opt._thicknessNi), sigmaRoughness(opt._sigmaRoughness),
          effectiveSLD(opt._effectiveSLD), roughnessModel(opt._roughnessModel)
    {
        if (angle != 0. && effectiveSLD != 0.)
            throw std::runtime_error("Cannot perform scalar computation "
                                     "for non-colinear magnetization");

        magnetizationVector = kvector_t(magnetizationMagnitude * std::sin(angle),
                                        magnetizationMagnitude * std::cos(angle), 0);
        sample = constructSample();
    }

    MultiLayer* release() { return sample.release(); }
};

class FeNiBiLayerBuilder : public ISampleBuilder
{
public:
    FeNiBiLayerBuilder() {}
    MultiLayer* buildSample() const;
};

class FeNiBiLayerTanhBuilder : public ISampleBuilder
{
public:
    FeNiBiLayerTanhBuilder() {}
    MultiLayer* buildSample() const;
};

class FeNiBiLayerNCBuilder : public ISampleBuilder
{
public:
    FeNiBiLayerNCBuilder() {}
    MultiLayer* buildSample() const;
};

class FeNiBiLayerSpinFlipBuilder : public ISampleBuilder
{
public:
    FeNiBiLayerSpinFlipBuilder() {}
    MultiLayer* buildSample() const;
};

class FeNiBiLayerSpinFlipTanhBuilder : public ISampleBuilder
{
public:
    FeNiBiLayerSpinFlipTanhBuilder() {}
    MultiLayer* buildSample() const;
};

class FeNiBiLayerSpinFlipNCBuilder : public ISampleBuilder
{
public:
    FeNiBiLayerSpinFlipNCBuilder() {}
    MultiLayer* buildSample() const;
};

#endif // BORNAGAIN_CORE_STANDARDSAMPLES_FENIBILAYERBUILDER_H
