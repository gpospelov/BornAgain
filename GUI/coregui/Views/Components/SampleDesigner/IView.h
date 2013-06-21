#ifndef IVIEW_H
#define IVIEW_H

#include <QGraphicsObject>

#include "DesignerHelper.h"
#include "ISampleViewVisitor.h"


//! parent class for graphic representation of all ISample's
class IView : public QGraphicsObject
{
public:
    enum { Type = DesignerHelper::IViewType };

    IView(QGraphicsItem *parent = 0) : QGraphicsObject(parent) {}
    virtual ~IView(){}

    //! сalls the ISampleViewVisitor's visit method
    virtual void accept(ISampleViewVisitor *visitor) = 0;

    int type() const { return Type; }
};


#endif // IVIEW_H
