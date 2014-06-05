#include "SampleViewFactory.h"
#include "MultiLayerView.h"
#include "LayerView.h"
#include "ParticleLayoutView.h"
#include "ParticleView.h"
#include "ParaCrystalViews.h"
#include <QDebug>


QStringList SampleViewFactory::m_valid_item_names  = QStringList()
        << QString("MultiLayer")
        << QString("Layer")
        << QString("ParticleLayout")
        << QString("Particle")
        << QString("InterferenceFunction1DParaCrystal")
        << QString("InterferenceFunction2DParaCrystal");


bool SampleViewFactory::isValidItemName(const QString &name)
{
    if(name.startsWith("FormFactor")) {
        return true;
    } else {
        return m_valid_item_names.contains(name);
    }
}


IView *SampleViewFactory::createSampleView(const QString &name)
{
    if (name==QString("MultiLayer")) {
        return new MultiLayerView();
    }
    else if (name==QString("Layer")) {
        return new LayerView();
    }
    else if (name==QString("ParticleLayout")) {
        return new ParticleLayoutView();
    }
    else if (name==QString("Particle")) {
        return new ParticleView();
    }
    else if (name==QString("InterferenceFunction1DParaCrystal")) {
        return new InterferenceFunction1DParaCrystalView();
    }
    else if (name==QString("InterferenceFunction2DParaCrystal")) {
        return new InterferenceFunction2DParaCrystalView();
    }

    qDebug() << "SampleViewFactory::createSampleView() -> Error! Can't create a view for" << name;

    return 0;
}
