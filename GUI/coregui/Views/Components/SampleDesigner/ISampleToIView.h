#ifndef ISAMPLETOSCENE_H
#define ISAMPLETOSCENE_H

#include "ISampleVisitor.h"
#include "DesignerScene.h"
#include <QMap>
#include <QList>
#include <QSet>


class ConnectableView;

//! The ISampleToScene class provide view of ISample object for graphics scene
class ISampleToIView : public ISampleVisitor
{
public:
    ISampleToIView() : m_level(0), m_multiLayer(0) {}

    void visit(const ISample *sample);
    void visit(const MultiLayer *sample);
    void visit(const Layer *sample);
    void visit(const LayerInterface *sample);
    void visit(const ParticleDecoration *sample);
    void visit(const ParticleInfo *sample);
    void visit(const Particle *sample);
    //void visit(const ParticleCoreShell *sample);
    //void visit(const MesoCrystal *sample);
    //void visit(const Crystal *sample);
    //void visit(const LatticeBasis *sample);
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

    //! returns list of created views representing ISample object
    QList<QGraphicsItem *> getItems();

    MultiLayerView *getMultiLayerView() { return m_multiLayer; }

private:
    std::string get_indent();

    int m_level;
    MultiLayerView *m_multiLayer;
    QMap<const ISample *, ConnectableView *> m_sample_to_view;
    QList<QGraphicsItem *> m_connections;
};


inline bool ISampleToIView::goForward()
{
    ++m_level;
    return true;
}

inline bool ISampleToIView::goBack()
{
    --m_level;
    return true;
}

inline std::string ISampleToIView::get_indent()
{
    std::string result;
    result.resize(m_level*4, '.');
    return result;
}


#endif // ISAMPLETOSCENE_H
