// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/SampleDesigner/IView.h
//! @brief     Defines class IView
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

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
    virtual ~IView() {}

    int type() const;

    virtual void setParameterizedItem(ParameterizedItem *item);

    virtual ParameterizedItem *getParameterizedItem();

    virtual void addView(IView *childView, int row = 0);

signals:
    void aboutToBeDeleted();

public slots:
    virtual void onChangedX();
    virtual void onChangedY();

protected:
    ParameterizedItem *m_item;
};

inline int IView::type() const
{
    return TYPE;
}

inline ParameterizedItem *IView::getParameterizedItem()
{
    return m_item;
}




#endif // IVIEW_H
