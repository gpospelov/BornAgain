#ifndef SAMPLEVIEWFACTORY_H
#define SAMPLEVIEWFACTORY_H


#include <QStringList>
#include <QMap>

class IView;

class SampleViewFactory
{
public:
    static bool isValidItemName(const QString &name);
    static IView *createSampleView(const QString &name);

    static bool isValidExampleName();

private:
    static QStringList m_valid_item_names;
};


#endif
