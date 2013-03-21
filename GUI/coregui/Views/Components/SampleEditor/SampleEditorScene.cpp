#include "SampleEditorScene.h"
#include "LayerView.h"
#include "InterfaceView.h"
#include "ParticleView.h"
#include "SampleFactory.h"

// examples:
// chip, diagramscene, dragdroprobot, simpleandchorlayout
SampleEditorScene::SampleEditorScene(QObject *parent)
    : ISampleEditorScene(parent)
{

    setSceneRect(QRectF(0, 0, 1280, 1280));
    setBackgroundBrush(QPixmap(":/SampleEditor/images/background3.png"));

    LayerView *layer = new LayerView();
    addItem(layer);
    layer->setPos(100,100);
    layer->setBrush(QColor(0, 0, 255, 127));

    ParticleView *particle = new ParticleView();
    particle->setPos(500, 500);
    addItem(particle);

//    ISample *sample
//    draw_sample

    ISample *sample = SampleFactory::createSample("SampleIsGISAXS9_Rotated");

    std::cout << *sample << std::endl;


}



//{
//    QGraphicsScene *scene = new CustomScene;
//    QGraphicsView *view = new QGraphicsView(this);
//    scene->setSceneRect(-180, -90, 360, 180);
//    view->setScene(scene);
//    view->scale(1, -1);
//    setCentralWidget(view);
//}


//ISample *StandardSamples::IsGISAXS1_CylinderAndPrism()
//{
//    MultiLayer *p_multi_layer = new MultiLayer();
//    complex_t n_air(1.0, 0.0);
//    complex_t n_substrate(1.0-6e-6, 2e-8);
//    complex_t n_particle(1.0-6e-4, 2e-8);
//    const IMaterial *p_air_material = MaterialManager::getHomogeneousMaterial("Air", n_air);
//    const IMaterial *p_substrate_material = MaterialManager::getHomogeneousMaterial("Substrate", n_substrate);
//    Layer air_layer;
//    air_layer.setMaterial(p_air_material);
//    Layer substrate_layer;
//    substrate_layer.setMaterial(p_substrate_material);
//    ParticleDecoration particle_decoration;
//    particle_decoration.addParticle(new Particle(n_particle, new FormFactorCylinder(5*Units::nanometer, 5*Units::nanometer)),0.0, 0.5);
//    particle_decoration.addParticle(new Particle(n_particle, new FormFactorPrism3(5*Units::nanometer, 5*Units::nanometer)), 0.0, 0.5);
//    particle_decoration.addInterferenceFunction(new InterferenceFunctionNone());
//    LayerDecorator air_layer_decorator(air_layer, particle_decoration);

//    p_multi_layer->addLayer(air_layer_decorator);
//    p_multi_layer->addLayer(substrate_layer);
//    return p_multi_layer;
//}
