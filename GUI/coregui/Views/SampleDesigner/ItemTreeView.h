// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/SampleDesigner/ItemTreeView.h
//! @brief     Defines class ItemTreeView
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef ITEMTREEVIEW_H
#define ITEMTREEVIEW_H

#include "WinDllMacros.h"
#include <QTreeView>

class BA_CORE_API_ ItemTreeView : public QTreeView
{
    Q_OBJECT
public:
    explicit ItemTreeView(QWidget *parent=0);
    virtual ~ItemTreeView();

protected:
#ifndef QT_NO_DRAGANDDROP
    virtual void dragMoveEvent(QDragMoveEvent *event);
#endif
};


#endif // ITEMTREEVIEW_H
