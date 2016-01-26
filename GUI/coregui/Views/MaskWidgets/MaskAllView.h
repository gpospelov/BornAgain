// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/MaskWidgets/MaskAllView.h
//! @brief     Defines MaskAllView class
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef MASKALLVIEW_H
#define MASKALLVIEW_H

#include "IMaskView.h"

//! This is a view of MaskAllItem which covers whole detector plane with mask value=true.

class BA_CORE_API_ MaskAllView : public IMaskView
{
    Q_OBJECT

public:
    int type() const { return MaskEditorHelper::MASKALL; }

    MaskAllView();

public slots:
    virtual void update_view();

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *);
};

#endif
