#ifndef TESTVIEW_H
#define TESTVIEW_H

#include <QWidget>
class MaterialEditorView;

//! TestView window to try things in mainwindow
class TestView : public QWidget
{
    Q_OBJECT

public:
    TestView(QWidget *parent = 0);
};


#endif
