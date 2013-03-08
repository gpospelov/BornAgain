#include "SampleEditorView.h"
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QVBoxLayout>


SampleEditorView::SampleEditorView(QWidget *parent, QGraphicsScene *scene)
    : QWidget(parent)
    , m_graphicsView(0)
{
    setMinimumSize(128, 128);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    QVBoxLayout *layout = new QVBoxLayout;
    m_graphicsView = new QGraphicsView(scene);
    layout->addWidget(m_graphicsView);
    setLayout(layout);
}
