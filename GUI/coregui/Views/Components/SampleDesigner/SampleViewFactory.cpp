#include "SampleViewFactory.h"
#include "item_constants.h"
#include "MultiLayerView.h"
#include "LayerView.h"
#include "ParticleLayoutView.h"
#include "ParticleView.h"
#include "ParticleCoreShellView.h"
#include "ParaCrystalViews.h"
#include "GUIHelpers.h"
#include <QDebug>


QStringList SampleViewFactory::m_valid_item_names  = QStringList()
        << Constants::MultiLayerType
        << Constants::LayerType
        << Constants::ParticleLayoutType
        << Constants::ParticleType
        << Constants::ParticleCoreShellType
        << Constants::InterferenceFunction1DParaCrystalType
        << Constants::InterferenceFunction2DParaCrystalType;


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
    else if (name==Constants::ParticleCoreShellType) {
        return new ParticleCoreShellView();
    }
    else if (name==Constants::InterferenceFunction1DParaCrystalType) {
        return new InterferenceFunction1DParaCrystalView();
    }
    else if (name==Constants::InterferenceFunction2DParaCrystalType) {
        return new InterferenceFunction2DParaCrystalView();
    }
    else {
        //qDebug() << "SampleViewFactory::createSampleView() -> Error! Can't create a view for" << name;
        throw GUIHelpers::Error("SampleViewFactory::createSampleView() -> Error! Can't create a view for " + name);
    }

    return 0;
}
