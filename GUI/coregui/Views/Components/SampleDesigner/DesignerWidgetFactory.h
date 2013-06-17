#ifndef DESIGNERWIDGETFACTORY_H
#define DESIGNERWIDGETFACTORY_H

#include "IFactory.h"
#include "ISampleView.h"

class QString;

//! The DesignerWidgetFactory class creates views of ISample type objects
//! DesignerWidgetFactory is created/deleted in SampleView, used by others
//! via instance() method.
class DesignerWidgetFactory : public IFactory<std::string, ISampleView>
{
public:
    DesignerWidgetFactory();
    virtual ~DesignerWidgetFactory();

    static DesignerWidgetFactory *instance();

    static ISampleView *createView(const QString &name);

private:
    ISampleView *this_createView(const QString &name);

    static DesignerWidgetFactory *m_instance;
};


#endif // DESIGNERWIDGETFACTORY_H

