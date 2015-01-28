// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/Components/SampleDesigner/ItemTreeView.h
//! @brief     Defines class ItemTreeView
//!
//! @homepage  http://bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
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
    ~ItemTreeView();

protected:
#ifndef QT_NO_DRAGANDDROP
    void dragMoveEvent(QDragMoveEvent *event);
#endif
};


#endif // ITEMTREEVIEW_H
