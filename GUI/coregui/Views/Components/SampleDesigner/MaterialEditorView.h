#ifndef MATERIALEDITORVIEW_H
#define MATERIALEDITORVIEW_H

#include <QWidget>
class MaterialModel;
class QTableView;
class QSplitter;

class MaterialEditorView : public QWidget
{
    Q_OBJECT

public:
    explicit MaterialEditorView(MaterialModel *model, QWidget *parent = 0);
    virtual ~MaterialEditorView(){}

    void setModel(MaterialModel *model);

private:
    MaterialModel *m_materialModel;
    QTableView *m_tableView;
    QSplitter *m_splitter;


};

#endif

