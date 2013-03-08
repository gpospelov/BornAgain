#include "SampleEditorScene.h"
#include "LayerView.h"

SampleEditorScene::SampleEditorScene(QObject *parent)
    : ISampleEditorScene(parent)
{

    setSceneRect(QRectF(0, 0, 1280, 1280));
    setBackgroundBrush(QPixmap(":/SampleEditor/images/background3.png"));


    LayerView *a = new LayerView(Qt::blue, Qt::white, "a");
    a->setPreferredSize(100, 100);
    addItem(a);

}
