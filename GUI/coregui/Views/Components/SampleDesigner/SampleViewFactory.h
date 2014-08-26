#ifndef SAMPLEVIEWFACTORY_H
#define SAMPLEVIEWFACTORY_H

#include "WinDllMacros.h"
#include <QStringList>
#include <QMap>

class IView;

class BA_CORE_API_ SampleViewFactory
{
public:
    static bool isValidItemName(const QString &name);
    static IView *createSampleView(const QString &name);

    static bool isValidExampleName();

private:
    static QStringList m_valid_item_names;
};


#endif
