#ifndef IVIEW_H
#define IVIEW_H

#include <QGraphicsObject>

#include "DesignerHelper.h"
#include "IViewVisitor.h"
class ParameterizedItem;

//! parent class for graphic representation of all ISample's
class IView : public QGraphicsObject
{
    Q_OBJECT
public:
    enum { Type = DesignerHelper::IViewType };

    IView(QGraphicsItem *parent = 0);
    virtual ~IView(){}

    //! сalls the ISampleViewVisitor's visit method
    virtual void accept(IViewVisitor *) {}

    int type() const { return Type; }

    virtual void setSessionItem(ParameterizedItem *item);

    virtual ParameterizedItem *getSessionItem() { return m_item; }

    virtual void addView(IView *childView, int row = 0);

signals:
    void aboutToBeDeleted();

public slots:
    virtual void onChangedX();
    virtual void onChangedY();
    virtual void onPropertyChange(QString propertyName);

protected:
    ParameterizedItem *m_item;

};




#endif // IVIEW_H
