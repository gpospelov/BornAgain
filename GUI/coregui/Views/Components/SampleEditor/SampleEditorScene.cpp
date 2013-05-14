#include "SampleEditorScene.h"
#include "LayerView.h"
#include "HomogeneousLayerView.h"
#include "InterfaceView.h"
#include "ParticleView.h"
#include "SampleFactory.h"
#include "MultiLayerItem.h"

// examples:
// chip, diagramscene, dragdroprobot, simpleandchorlayout
SampleEditorScene::SampleEditorScene(QObject *parent)
    : ISampleEditorScene(parent)
    , m_xmin(-300)
    , m_xmax(300)
    , m_ymin(-100)
    , m_ymax(500)
{
    setSceneRect(QRectF(-300, -100, 600, 600));
//    setSceneRect(QRectF(m_xmin, m_ymin, m_xmax-m_xmin, m_ymax-m_ymin));
//    setSceneRect(QRectF(0,0,600,600));
    setBackgroundBrush(getBackgroundPixmap());

//    HomogeneousLayerView *layer = new HomogeneousLayerView();
//    HomogeneousLayerView *layer = new HomogeneousLayerView();
//    layer->setPos(-layer->rect().width()/2, 0.0);
//    addItem(layer);
//    layer->setBrush(QColor(0, 0, 255, 127));

//    ParticleView *particle = new ParticleView();
//    particle->setPos(0, 100);
//    addItem(particle);

//    ISample *sample
//    draw_sample
//    ISample *sample = SampleFactory::createSample("SampleIsGISAXS9_Rotated");
//    std::cout << *sample << std::endl;


    MultiLayerItem *ml = new MultiLayerItem();
    ml->setPos(-ml->rect().width()/2, 100.0);
    addItem(ml);

}


QPixmap SampleEditorScene::getBackgroundPixmap()
{
    //QPixmap result(":/SampleEditor/images/background3.png");

//    const int checkerbordSize= 20;
//    QPixmap result(checkerbordSize * 2, checkerbordSize * 2);
//    result.fill(Qt::white);
//    QPainter tilePainter(&result);
//    QColor color(220, 220, 220);
//    tilePainter.fillRect(0, 0, checkerbordSize, checkerbordSize, color);
//    tilePainter.fillRect(checkerbordSize, checkerbordSize, checkerbordSize, checkerbordSize, color);
//    tilePainter.end();

    const int size= 10;
    QPixmap result(size, size);
    result.fill(QColor(250, 250, 250));
    QPainter tilePainter(&result);
    QColor color(220, 220, 220);
    tilePainter.fillRect(0.0, 0.0, 2, 2, color);
    tilePainter.end();

    return result;
}

