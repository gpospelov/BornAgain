#ifndef SAMPLEEDITORVIEW_H
#define SAMPLEEDITORVIEW_H

#include <QWidget>

class QGraphicsView;
class QGraphicsScene;

class SampleEditorView : public QWidget
{
public:

    explicit SampleEditorView(QWidget *parent = 0, QGraphicsScene *scene=0);

private:
    QGraphicsView *m_graphicsView;
};

#endif // SAMPLEEDITORVIEW_H
