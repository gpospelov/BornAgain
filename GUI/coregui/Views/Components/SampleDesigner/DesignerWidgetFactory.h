#ifndef DESIGNERWIDGETFACTORY_H
#define DESIGNERWIDGETFACTORY_H

#include "IFactory.h"
#include "ISampleView.h"

class QString;

class DesignerWidgetFactory : public IFactory<std::string, ISampleView>
{
public:
    DesignerWidgetFactory();

    ISampleView *create(const QString &name);

};


#endif // DESIGNERWIDGETFACTORY_H

