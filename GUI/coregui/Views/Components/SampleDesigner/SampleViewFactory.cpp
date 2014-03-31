#include "SampleViewFactory.h"
#include "MultiLayerView.h"
#include "LayerView.h"



QStringList SampleViewFactory::m_all_sample_names  = QStringList()
        << QString("MultiLayer")
        << QString("Layer");


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
    return 0;
}
