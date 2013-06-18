#ifndef SAMPLEPRINTVISITOR_H
#define SAMPLEPRINTVISITOR_H

#include "ISampleVisitor.h"
#include <string>

//! The SamplePrintVisitor
class SamplePrintVisitor : public ISampleVisitor
{
public:
    SamplePrintVisitor();
    void visit(const ISample *sample);
    void visit(const MultiLayer *sample);
    void visit(const Layer *sample);
    void visit(const LayerDecorator *sample);
    void visit(const LayerInterface *sample);
    void visit(const ParticleDecoration *sample);
    void visit(const ParticleInfo *sample);
    void visit(const Particle *sample);
    void visit(const IInterferenceFunction *sample);

    bool goForward();
    bool goBack();
private:
    std::string get_indent();
    int m_level;
};

#endif // SAMPLEPRINTVISITOR_H
