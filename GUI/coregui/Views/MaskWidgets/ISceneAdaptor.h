// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/MaskWidgets/ISceneAdaptor.h
//! @brief     Defines interface class ISceneAdaptor
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef ISCENEADAPTOR_H
#define ISCENEADAPTOR_H

#include "WinDllMacros.h"
#include <QObject>

//! Interface to adapt MaskItems coordinates to/from scene coordinates.
//! MaskItems coordinates are expressed in units of IntensityDataItem.

class BA_CORE_API_ ISceneAdaptor : public QObject
{
    Q_OBJECT
public:
    ISceneAdaptor();
    virtual ~ISceneAdaptor(){}

    virtual qreal toSceneX(qreal) const = 0;
    virtual qreal toSceneY(qreal) const = 0;
    virtual qreal fromSceneX(qreal) const = 0;
    virtual qreal fromSceneY(qreal) const = 0;
};

class BA_CORE_API_ DefaultSceneAdaptor : public ISceneAdaptor
{
    qreal toSceneX(qreal value) const { return value; }
    qreal toSceneY(qreal value) const { return value; }
    qreal fromSceneX(qreal value) const { return value; }
    qreal fromSceneY(qreal value) const { return value; }
};


#endif
