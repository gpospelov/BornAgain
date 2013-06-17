#ifndef SAMPLEPRINTVISITOR_H
#define SAMPLEPRINTVISITOR_H

#include "ISampleVisitor.h"
#include <string>

//! The SamplePrintVisitor
class SamplePrintVisitor : public ISampleVisitor
{
public:
    SamplePrintVisitor();
    void visit(ISample *sample);
    void visit(MultiLayer *sample);
    void visit(Layer *sample);
    void visit(LayerDecorator *sample);
    void visit(LayerInterface *sample);
    void visit(ParticleDecoration *sample);
    void visit(ParticleInfo *sample);
    void visit(Particle *sample);
    void visit(IFormFactor *sample);
    void visit(IInterferenceFunction *sample);

    void enter();
    void leave();
private:
    std::string get_indent();
    int m_level;
};

#endif // SAMPLEPRINTVISITOR_H
