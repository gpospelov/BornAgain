#ifndef ISAMPLETOSCENE_H
#define ISAMPLETOSCENE_H

#include "ISampleVisitor.h"

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

    void enter();
    void leave();

private:
    std::string get_indent();
    int m_level;
};

#endif // ISAMPLETOSCENE_H
