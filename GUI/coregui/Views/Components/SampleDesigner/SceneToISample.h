#ifndef SCENETOISAMPLE_H
#define SCENETOISAMPLE_H

#include "ISampleViewVisitor.h"
#include <QMap>

class SceneToISample : public ISampleViewVisitor
{
public:
    SceneToISample() : m_level(0) {}

    void visit(ISampleView *view);
    void visit(ISampleRectView *view);
    void visit(LayerView *view);
    void visit(MultiLayerView *view);
    void visit(FormFactorView *view);
    void visit(FormFactorFullSphereView *view);
    void visit(FormFactorPyramidView *view);
    void visit(FormFactorPrism3View *view);
    void visit(FormFactorCylinderView *view);
    void visit(InterferenceFunctionView *view);
    void visit(InterferenceFunction1DParaCrystalView *view);
    void visit(ParticleDecorationView *view);

    bool goForward();
    bool goBack();

private:
    std::string get_indent();
    int m_level;
    QMap<int, ISampleView * > m_views; // level to views
};


inline bool SceneToISample::goForward()
{
    ++m_level;
    return true;
}


inline bool SceneToISample::goBack()
{
    --m_level;
    return true;
}


inline std::string SceneToISample::get_indent()
{
    std::string result;
    result.resize(m_level*4, '.');
    return result;
}

#endif // SCENETOISAMPLE_H
