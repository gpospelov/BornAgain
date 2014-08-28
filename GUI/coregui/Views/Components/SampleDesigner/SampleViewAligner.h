#ifndef SAMPLEVIEWALIGNER_H
#define SAMPLEVIEWALIGNER_H

#include "WinDllMacros.h"
#include <QMap>
#include <QModelIndex>
#include <QPointF>
class DesignerScene;
class IView;
class ParameterizedItem;


//! Makes alignment of sample droped on graphics scene.
//! Implements additional algorithm for smart alignment.
class BA_CORE_API_ SampleViewAligner
{
public:
    SampleViewAligner(DesignerScene *scene);

    void alignSample(ParameterizedItem *item, QPointF reference = QPointF(), bool force_alignment = false);
    void alignSample(const QModelIndex & parentIndex, QPointF reference = QPointF(), bool force_alignment = false);

    void smartAlign();
    void updateViews(const QModelIndex & parentIndex = QModelIndex());
    void updateForces();
    void calculateForces(IView *view);
    void advance();

private:
    IView *getViewForIndex(const QModelIndex &index);
    QList<IView *> getConnectedViews(IView *view);

    DesignerScene *m_scene;
    QList<IView *> m_views; //!< list of all views which are subject to smart align
    QMap<IView *, QPointF> m_viewToPos;
};


#endif

