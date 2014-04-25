#include "SampleViewFactory.h"
#include "MultiLayerView.h"
#include "LayerView.h"
#include "ParticleLayoutView.h"
#include "ParticleView.h"
#include <QDebug>


QStringList SampleViewFactory::m_all_sample_names  = QStringList()
        << QString("MultiLayer")
        << QString("Layer")
        << QString("ParticleLayout")
        << QString("Particle");


bool SampleViewFactory::isValidName(const QString &name)
{
    if(name.startsWith("FormFactor")) {
        return true;
    } else {
        return m_all_sample_names.contains(name);
    }
}


IView *SampleViewFactory::createSampleView(const QString &name)
{
    if (name==QString("MultiLayer")) {
        return new MultiLayerView();
    }

    if (name==QString("Layer")) {
        return new LayerView();
    }

    if (name==QString("ParticleLayout")) {
        return new ParticleLayoutView();
    }

    if (name==QString("Particle")) {
        return new ParticleView();
    }

    qDebug() << "SampleViewFactory::createSampleView() -> Error! Can't create a view for" << name;

    return 0;
}
