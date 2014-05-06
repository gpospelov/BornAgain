#include "GUIExamplesFactory.h"
#include "GUIObjectBuilder.h"
#include "SampleBuilderFactory.h"


QMap<QString, QString > init_NameToRegistry()
{
    QMap<QString, QString > result;
    result["example01"] = "isgisaxs01";
    result["example02"] = "isgisaxs04_1DDL";
    return result;
}

QMap<QString, QString> GUIExamplesFactory::m_name_to_registry = init_NameToRegistry();

bool GUIExamplesFactory::isValidExampleName(const QString &name)
{
    return m_name_to_registry.contains(name);
}


ParameterizedItem *GUIExamplesFactory::createItems(const QString &name, SessionModel *model)
{
    QString exampleName = m_name_to_registry[name];

    SampleBuilderFactory factory;
    boost::scoped_ptr<ISample> sample(factory.createSample(exampleName.toAscii().data()));

    Q_ASSERT(sample.get());
    sample->setName(name.toAscii().data());
    sample->printSampleTree();

    GUIObjectBuilder guiBuilder;
    guiBuilder.populateModel(model, sample.get());

    return guiBuilder.getTopItem();
}
