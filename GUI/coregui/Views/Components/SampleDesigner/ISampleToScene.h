#ifndef ISAMPLETOSCENE_H
#define ISAMPLETOSCENE_H

#include "ISampleVisitor.h"
#include "DesignerScene.h"

class ISampleRectView;

//! The ISampleToScene class provide view of ISample object for graphics scene
class ISampleToScene : public ISampleVisitor
{
public:
    ISampleToScene();
//    void visit(ISample *sample);
//    void visit(MultiLayer *sample);
//    void visit(Layer *sample);
//    void visit(LayerDecorator *sample);
//    void visit(LayerInterface *sample);
//    void visit(ParticleDecoration *sample);
//    void visit(ParticleInfo *sample);
//    void visit(Particle *sample);
//    void visit(IFormFactor *sample);
//    void visit(IInterferenceFunction *sample);
    void visit(const ISample *sample);
    void visit(const MultiLayer *sample);
    void visit(const Layer *sample);
    void visit(const LayerDecorator *sample);
    void visit(const LayerInterface *sample);
    void visit(const ParticleDecoration *sample);
    void visit(const ParticleInfo *sample);
    void visit(const Particle *sample);
    void visit(const IFormFactor *sample);
    void visit(const IInterferenceFunction *sample);

    bool goForward();
    bool goBack();

    void setScene(DesignerScene *scene) { m_scene = scene; }
private:
    std::string get_indent();
    int m_level;
    bool m_can_i_go;
    DesignerScene *m_scene;
    ISampleRectView *m_context;
};

#endif // ISAMPLETOSCENE_H
