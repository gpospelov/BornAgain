#ifndef SAMPLEVIEWFACTORY_H
#define SAMPLEVIEWFACTORY_H


#include <QStringList>

class IView;

class SampleViewFactory
{
public:
    static bool isValidName(const QString &name);
    static IView *createSampleView(const QString &name);

private:
    static QStringList m_all_sample_names;
};


#endif
