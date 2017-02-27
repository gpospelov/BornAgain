// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/MaskWidgets/MaskAllView.h
//! @brief     Defines MaskAllView class
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef MASKALLVIEW_H
#define MASKALLVIEW_H

#include "IShape2DView.h"

//! This is a view of MaskAllItem which covers whole detector plane with mask value=true.

class BA_CORE_API_ MaskAllView : public IShape2DView
{
    Q_OBJECT

public:
    int type() const { return MaskEditorHelper::MASKALL; }

    MaskAllView();

protected slots:
    virtual void update_view();

protected:
    void paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*);
};

#endif // MASKALLVIEW_H
