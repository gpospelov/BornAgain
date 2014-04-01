#include "SampleViewFactory.h"
#include "MultiLayerView.h"
#include "LayerView.h"
#include "ParticleLayoutView.h"



QStringList SampleViewFactory::m_all_sample_names  = QStringList()
        << QString("MultiLayer")
        << QString("Layer")
        << QString("ParticleLayout");


bool SampleViewFactory::isValidName(const QString &name)
{
    return m_all_sample_names.contains(name);
}


IView *SampleViewFactory::createSampleView(const QString &name)
{
    if (name==QString("MultiLayer")) {
        return new MultiLayerView2();
    }

    if (name==QString("Layer")) {
        return new LayerView2();
    }

    if (name==QString("ParticleLayout")) {
        return new ParticleLayoutView();
    }

    return 0;
}
