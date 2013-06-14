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
    void visit(Layer *);
    void visit(LayerDecorator *);
    void visit(LayerInterface *);
    void visit(ParticleDecoration *);
    void visit(ParticleInfo *);
    void visit(Particle *);
    void visit(IFormFactor *);

    void enter();
    void leave();
private:
    std::string get_indent();
    int m_level;
};

#endif // SAMPLEPRINTVISITOR_H
