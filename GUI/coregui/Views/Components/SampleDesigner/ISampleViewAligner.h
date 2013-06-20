#ifndef ISAMPLEVIEWALIGNER_H
#define ISAMPLEVIEWALIGNER_H

#include "ISampleViewVisitor.h"
#include <QMap>
#include <QList>
#include <QPointF>


//! The ISampleViewAligner class aligns items of ISampleView
class ISampleViewAligner : public ISampleViewVisitor
{
public:
    ISampleViewAligner() : m_level(0) {}

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

    //! makes alignment of MultiLayer wil all nodes connected
    void makeAlign(MultiLayerView *multi_layer);

private:
    //! calculates total vertical space required by given items
    qreal getTotalVerticalSpace(const QList<ISampleView *> &items);

    //! calculates maximum horizontal space needed for given items)
    qreal getMaximumHorizontalSpace(const QList<ISampleView *> &items);

    //! place given items using given reference point
    QPointF placeItems(const QList<ISampleView *> &items, QPointF reference);

    //! returns maximum level number
    int getMaximumLevelNumber();

    std::string get_indent();
    int m_level;
    QMap<int, ISampleView * > m_views; // level to views
};


inline bool ISampleViewAligner::goForward()
{
    ++m_level;
    return true;
}


inline bool ISampleViewAligner::goBack()
{
    --m_level;
    return true;
}


inline std::string ISampleViewAligner::get_indent()
{
    std::string result;
    result.resize(m_level*4, '.');
    return result;
}


#endif // ISAMPLEVIEWALIGNER_H
