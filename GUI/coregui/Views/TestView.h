#ifndef TESTVIEW_H
#define TESTVIEW_H

#include <QWidget>
#include <QTreeView>
#include <QAction>
#include <QSignalMapper>

#include "qstandarditemmodel.h"

class MaterialEditorView;
class TestViewDelegate;

//! TestView window to try things in mainwindow
class TestView : public QWidget
{
    Q_OBJECT

public:
    TestView(QWidget *parent = 0);

private:
    QTreeView *m_treeView;
    TestViewDelegate *m_delegate;
};


#endif
