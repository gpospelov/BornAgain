// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/MaskWidgets/ISceneAdaptor.h
//! @brief     Defines interface class ISceneAdaptor
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef ISCENEADAPTOR_H
#define ISCENEADAPTOR_H

#include "WinDllMacros.h"
#include <QObject>
#include <QRectF>

//! Interface to adapt MaskItems coordinates (expressed in units of IntensityDataItem)
//! to/from scene coordinates.

class BA_CORE_API_ ISceneAdaptor : public QObject
{
    Q_OBJECT
public:
    virtual ~ISceneAdaptor(){}

    //! convert native mask x-coordinate to scene coordinate
    virtual qreal toSceneX(qreal) const = 0;
    //! convert native mask y-coordinate to scene coordinate
    virtual qreal toSceneY(qreal) const = 0;
    //! convert scene x-coordinate to native mask coordinate
    virtual qreal fromSceneX(qreal) const = 0;
    //! convert scene y-coordinate to native mask coordinate
    virtual qreal fromSceneY(qreal) const = 0;

    //! returns viewport rectangle in scene coordinates
    virtual const QRectF& getViewportRectangle() const { return m_viewport_rectangle; }

signals:
    void update_request();

protected:
    QRectF m_viewport_rectangle;
};

class BA_CORE_API_ DefaultSceneAdaptor : public ISceneAdaptor
{
    Q_OBJECT
public:
    DefaultSceneAdaptor(){}
    qreal toSceneX(qreal value) const { return value; }
    qreal toSceneY(qreal value) const { return value; }
    qreal fromSceneX(qreal value) const { return value; }
    qreal fromSceneY(qreal value) const { return value; }
};


#endif // ISCENEADAPTOR_H
