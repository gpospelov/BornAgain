#ifndef IVIEW_H
#define IVIEW_H

#include <QGraphicsObject>

#include "DesignerHelper.h"
class ParameterizedItem;

//! parent class for graphic representation of all ISample's
class IView : public QGraphicsObject
{
    Q_OBJECT
public:
    enum { Type = DesignerHelper::IViewType };

    IView(QGraphicsItem *parent = 0);
    virtual ~IView(){}

    int type() const { return Type; }

    virtual void setParameterizedItem(ParameterizedItem *item);

    virtual ParameterizedItem *getParameterizedItem() { return m_item; }

    virtual void addView(IView *childView, int row = 0);

signals:
    void aboutToBeDeleted();

public slots:
    virtual void onChangedX();
    virtual void onChangedY();
    virtual void onPropertyChange(const QString &propertyName);

protected:
    ParameterizedItem *m_item;
};




#endif // IVIEW_H
