#ifndef IVIEWTOISAMPLE_H
#define IVIEWTOISAMPLE_H

#include "IViewVisitor.h"
#include <QMap>

class ISample;
class MultiLayer;

class IViewToISample : public IViewVisitor
{
public:
    IViewToISample() : m_multiLayer(0), m_level(0) {}

    void visit(IView *view);
    void visit(ConnectableView *view);
    void visit(MultiLayerView *view);
    void visit(LayerView *view);
    void visit(ParticleDecorationView *view);
    void visit(FormFactorView *view);
    void visit(FormFactorFullSphereView *view);
    void visit(FormFactorPyramidView *view);
    void visit(FormFactorPrism3View *view);
    void visit(FormFactorCylinderView *view);
    void visit(InterferenceFunctionView *view);
    void visit(InterferenceFunction1DParaCrystalView *view);

    bool goForward();
    bool goBack();

    ISample *makeISample(IView *view);

    MultiLayer *m_multiLayer;
private:
    std::string get_indent();
    int m_level;
    QMap<int, IView * > m_views; // level to views

    QMap<IView *, ISample *> m_view_to_sample;

};


inline bool IViewToISample::goForward()
{
    ++m_level;
    return true;
}


inline bool IViewToISample::goBack()
{
    --m_level;
    return true;
}


inline std::string IViewToISample::get_indent()
{
    std::string result;
    result.resize(m_level*4, '.');
    return result;
}

#endif // IVIEWTOISAMPLE_H
