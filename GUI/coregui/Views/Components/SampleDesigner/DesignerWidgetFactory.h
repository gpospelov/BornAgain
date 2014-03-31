#ifndef DESIGNERWIDGETFACTORY_H
#define DESIGNERWIDGETFACTORY_H

#include <QList>
#include "IFactory.h"
#include "ConnectableView.h"

class QString;

//! The DesignerWidgetFactory class creates views of ISample type objects
//! DesignerWidgetFactory is created/deleted in SampleView, used by others
//! via instance() method.
class DesignerWidgetFactory : public IFactory<std::string, IView>
{
public:
    DesignerWidgetFactory();
    virtual ~DesignerWidgetFactory();

    static DesignerWidgetFactory *instance();

    static QList<QGraphicsItem *> createViews(const QString &name);
    static IView * createView(const QString &name);

private:
    QList<QGraphicsItem *> this_createViews(const QString &name);
    IView  *this_createView(const QString &name);

    static DesignerWidgetFactory *m_instance;
};


#endif // DESIGNERWIDGETFACTORY_H

