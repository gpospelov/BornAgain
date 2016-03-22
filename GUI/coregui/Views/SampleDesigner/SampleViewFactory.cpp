// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/SampleDesigner/SampleViewFactory.cpp
//! @brief     Implements class SampleViewFactory
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "SampleViewFactory.h"
#include "item_constants.h"
#include "MultiLayerView.h"
#include "LayerView.h"
#include "ParticleLayoutView.h"
#include "ParticleView.h"
#include "TransformationView.h"
#include "ParticleCoreShellView.h"
#include "ParticleCompositionView.h"
#include "ParticleDistributionView.h"
#include "InterferenceFunctionViews.h"
#include "GUIHelpers.h"
#include <QDebug>


QStringList SampleViewFactory::m_valid_item_names  = QStringList()
        << Constants::MultiLayerType
        << Constants::LayerType
        << Constants::ParticleLayoutType
        << Constants::ParticleType
        << Constants::TransformationType
        << Constants::ParticleCoreShellType
        << Constants::ParticleCompositionType
        << Constants::ParticleDistributionType
        << Constants::InterferenceFunctionRadialParaCrystalType
        << Constants::InterferenceFunction2DParaCrystalType
        << Constants::InterferenceFunction1DLatticeType
        << Constants::InterferenceFunction2DLatticeType;


bool SampleViewFactory::isValidItemName(const QString &name)
{
    if(name.startsWith(Constants::FormFactorType)) {
        return true;
    } else {
        return m_valid_item_names.contains(name);
    }
}


IView *SampleViewFactory::createSampleView(const QString &name)
{
    if (name==Constants::MultiLayerType) {
        return new MultiLayerView();
    }
    else if (name==Constants::LayerType) {
        return new LayerView();
    }
    else if (name==Constants::ParticleLayoutType) {
        return new ParticleLayoutView();
    }
    else if (name==Constants::ParticleType) {
        return new ParticleView();
    }
    else if (name==Constants::TransformationType) {
        return new TransformationView();
    }
    else if (name==Constants::ParticleCoreShellType) {
        return new ParticleCoreShellView();
    }
    else if (name==Constants::ParticleCompositionType) {
        return new ParticleCompositionView();
    }
    else if (name==Constants::ParticleDistributionType) {
        return new ParticleDistributionView();
    }
    else if (name==Constants::InterferenceFunctionRadialParaCrystalType) {
        return new InterferenceFunctionRadialParaCrystalView();
    }
    else if (name==Constants::InterferenceFunction2DParaCrystalType) {
        return new InterferenceFunction2DParaCrystalView();
    }
    else if (name==Constants::InterferenceFunction1DLatticeType) {
        return new InterferenceFunction1DLatticeView();
    }
    else if (name==Constants::InterferenceFunction2DLatticeType) {
        return new InterferenceFunction2DLatticeView();
    }
    else {
        //qDebug() << "SampleViewFactory::createSampleView() -> Error! Can't create a view for" << name;
//        throw GUIHelpers::Error("SampleViewFactory::createSampleView() -> Error! Can't create a view for " + name);
    }

    return 0;
}
