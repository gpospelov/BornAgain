#ifndef ISAMPLETOSCENE_H
#define ISAMPLETOSCENE_H

#include "ISampleVisitor.h"
#include "DesignerScene.h"
#include <QMap>

class ISampleRectView;

//! The ISampleToScene class provide view of ISample object for graphics scene
class ISampleToScene : public ISampleVisitor
{
public:
    ISampleToScene();

    void visit(const ISample *sample);
    void visit(const MultiLayer *sample);
    void visit(const Layer *sample);
    void visit(const LayerDecorator *sample);
    void visit(const LayerInterface *sample);
    void visit(const ParticleDecoration *sample);
    void visit(const ParticleInfo *sample);
    void visit(const Particle *sample);
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

    void setScene(DesignerScene *scene) { m_scene = scene; }
private:
    std::string get_indent();
    int m_level;
    bool m_can_i_go;
    DesignerScene *m_scene;

    QMap<const ISample *, ISampleRectView *> m_object_to_view;
};

#endif // ISAMPLETOSCENE_H
