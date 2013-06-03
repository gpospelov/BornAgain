#ifndef SAMPLETOOLBAR_H
#define SAMPLETOOLBAR_H

#include <QToolBar>

class QAction;
class QToolButton;
class QToolBar;

//! main tool bar on top of SampleView window
class SampleToolBar : public QToolBar
{
    Q_OBJECT
public:
    explicit SampleToolBar(QWidget *parent = 0);

public slots:
    void materialEditorCall();

private:
    QAction *m_goBackAction;
};


#endif // SAMPLETOOLBAR_H
