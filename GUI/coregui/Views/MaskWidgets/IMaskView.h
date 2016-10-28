// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/MaskWidgets/IMaskView.h
//! @brief     Defines interface class IMaskView for all masks on graphics scene
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef IMASKVIEW_H
#define IMASKVIEW_H

#include "MaskEditorHelper.h"
#include "WinDllMacros.h"
#include <QGraphicsObject>
#include <memory>

class SessionItem;
class ISceneAdaptor;
class QPainter;

//! Main interface class for views representing MaskItems on graphics scene

class BA_CORE_API_ IMaskView : public QGraphicsObject
{
    Q_OBJECT
public:
    virtual int type() const { return MaskEditorHelper::IMASKVIEW; }

    IMaskView();
    virtual ~IMaskView();

    QRectF boundingRect() const;

    virtual void setParameterizedItem(SessionItem *item);
    virtual SessionItem *getParameterizedItem();

    const ISceneAdaptor *getAdaptor();
    virtual void setSceneAdaptor(const ISceneAdaptor *adaptor);

    double par(const QString &property_name) const;

    qreal toSceneX(const QString &property_name) const;
    qreal toSceneX(qreal value) const;
    qreal toSceneY(const QString &property_name) const;
    qreal toSceneY(qreal value) const;

    //! convert scene coordinates to ColorMap plot coordinates
    qreal fromSceneX(qreal value) const;
    qreal fromSceneY(qreal value) const;

    virtual void addView(IMaskView *childView, int row = 0);

signals:
    void propertyChanged();

public slots:
    //! update visual appearance of view (triggered by ISceneAdaptor)
    virtual void update_view() = 0;
    virtual void onChangedX();
    virtual void onChangedY();
    virtual void onPropertyChange(const QString &propertyName);

protected:
    SessionItem *m_item;
    const ISceneAdaptor *m_adaptor;
    QRectF m_bounding_rect;
};

#endif // IMASKVIEW_H

