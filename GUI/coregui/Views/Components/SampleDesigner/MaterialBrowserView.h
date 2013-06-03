#ifndef MATERIALBROWSERVIEW_H
#define MATERIALBROWSERVIEW_H

#include <QDialog>

class QTableView;
class MaterialBrowserModel;

class MaterialBrowserView : public QDialog
{
public:
    explicit MaterialBrowserView(QWidget *parent = 0);
private:
    QTableView *m_tableView;
    MaterialBrowserModel *m_tableModel;
};

#endif // MATERIALBROWSERVIEW_H

