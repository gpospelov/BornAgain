// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/MaskWidgets/IMaskView.h
//! @brief     Defines interface class IMaskView for all masks on graphics scene
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef IMASKVIEW_H
#define IMASKVIEW_H

#include "WinDllMacros.h"
#include <QGraphicsObject>

class ParameterizedItem;
class ISceneAdaptor;

//! Main interface class for views representing MaskItems on graphics scene

class BA_CORE_API_ IMaskView : public QGraphicsObject
{
    Q_OBJECT
public:
    IMaskView();
    virtual ~IMaskView(){}

    QRectF boundingRect() const;

    virtual void setParameterizedItem(ParameterizedItem *item);
    virtual ParameterizedItem *getParameterizedItem();

    virtual void setSceneAdaptor(ISceneAdaptor *adaptor);

    qreal toSceneX(const QString &property_name) const;
    qreal toSceneX(qreal value) const;
    qreal toSceneY(const QString &property_name) const;
    qreal toSceneY(qreal value) const;

    //! convert scene coordinates to ColorMap plot coordinates
    qreal fromSceneX(qreal value) const;
    qreal fromSceneY(qreal value) const;

signals:
    void aboutToBeDeleted();

public slots:
    virtual void update_view() = 0;
    virtual void onChangedX();
    virtual void onChangedY();
    virtual void onPropertyChange(const QString &propertyName);

protected:
    //! update visual appearance triggered by adapter
    ParameterizedItem *m_item;
    ISceneAdaptor *m_adaptor;
    QRectF m_bounding_rect;
};



#endif

