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
