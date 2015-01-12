#ifndef IVIEW_H
#define IVIEW_H

#include <QGraphicsObject>

#include "DesignerHelper.h"
class ParameterizedItem;

//! parent class for graphic representation of all ISample's
class BA_CORE_API_ IView : public QGraphicsObject
{
    Q_OBJECT
public:
    enum { TYPE = DesignerHelper::IVIEW };

    IView(QGraphicsItem *parent = 0);
    virtual ~IView(){}

    int type() const { return TYPE; }

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
