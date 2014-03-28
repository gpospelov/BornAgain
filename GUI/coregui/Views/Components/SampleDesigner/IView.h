#ifndef IVIEW_H
#define IVIEW_H

#include <QGraphicsObject>

#include "DesignerHelper.h"
#include "IViewVisitor.h"
class ParameterizedItem;

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

    void setSessionItem(ParameterizedItem *item) { m_item = item; }

    ParameterizedItem *getSessionItem() { return m_item; }

private:
    ParameterizedItem *m_item;

};




#endif // IVIEW_H
