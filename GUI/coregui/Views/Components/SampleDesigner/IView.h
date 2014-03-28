#ifndef IVIEW_H
#define IVIEW_H

#include <QGraphicsObject>

#include "DesignerHelper.h"
#include "IViewVisitor.h"
class ParameterizedGraphicsItem;

//! parent class for graphic representation of all ISample's
class IView : public QGraphicsObject
{
public:
    enum { Type = DesignerHelper::IViewType };

    IView(QGraphicsItem *parent = 0) : QGraphicsObject(parent), m_item(0) {}
    virtual ~IView(){}

    //! сalls the ISampleViewVisitor's visit method
    virtual void accept(IViewVisitor *) {}

    int type() const { return Type; }

    void setSessionItem(ParameterizedGraphicsItem *item) { m_item = item; }

    ParameterizedGraphicsItem *getSessionItem() { return m_item; }

protected:
    ParameterizedGraphicsItem *m_item;

};




#endif // IVIEW_H
