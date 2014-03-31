#ifndef ITEMTREEVIEW_H
#define ITEMTREEVIEW_H

#include <QTreeView>

class ItemTreeView : public QTreeView
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
