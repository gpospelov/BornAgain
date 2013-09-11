#ifndef SAMPLEPRINTVISITOR_H
#define SAMPLEPRINTVISITOR_H

#include "ISampleVisitor.h"
#include <string>

//! The SamplePrintVisitor
class SamplePrintVisitor : public ISampleVisitor
{
public:
    SamplePrintVisitor() : m_level(0){}

    void visit(const ISample *sample);
    void visit(const MultiLayer *sample);
    void visit(const Layer *sample);
    void visit(const LayerInterface *sample);
    void visit(const ParticleDecoration *sample);
    void visit(const ParticleInfo *sample);
    void visit(const Particle *sample);
    void visit(const ParticleCoreShell *sample);
    void visit(const IFormFactor *sample);

    void visit(const FormFactorFullSphere *sample);
    void visit(const FormFactorPyramid *sample);
    void visit(const FormFactorCylinder *sample);
    void visit(const FormFactorPrism3 *sample);

    void visit(const IInterferenceFunction *sample);
    void visit(const InterferenceFunction1DParaCrystal  *);
    void visit(const InterferenceFunction2DParaCrystal  *);

    bool goForward();
    bool goBack();
private:
    std::string get_indent();
    int m_level;
};


inline bool SamplePrintVisitor::goForward()
{
    ++m_level;
    return true;
}

inline bool SamplePrintVisitor::goBack()
{
    --m_level;
    return true;
}

inline std::string SamplePrintVisitor::get_indent()
{
    std::string result;
    result.resize(m_level*4, '.');
    return result;
}


#endif // SAMPLEPRINTVISITOR_H
