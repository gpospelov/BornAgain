#ifndef ISAMPLEVIEWLAYOUTVISITOR_H
#define ISAMPLEVIEWLAYOUTVISITOR_H

#include "ISampleViewVisitor.h"
#include <QMap>
#include <QList>
#include <QPointF>

//! The ISampleViewLayoutVisitor class places views of ISample nicely on the scene
class ISampleViewLayoutVisitor : public ISampleViewVisitor
{
public:
    ISampleViewLayoutVisitor();

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

    void makeLayout(MultiLayerView *multi_layer);

private:
//    void addView(int level, ISampleView *view);

    qreal getTotalVerticalSpace(const QList<ISampleView *> &items);
    qreal getMaximumHorizontalSpace(const QList<ISampleView *> &items);
    QPointF placeItems(const QList<ISampleView *> &items, QPointF start);


    std::string get_indent();
    int m_level;
    // list of views for different levels
//    QMap<int, QList<ISampleView *> > m_views;
    QMap<int, ISampleView * > m_views;
};

#endif // ISAMPLEVIEWLAYOUTVISITOR_H
