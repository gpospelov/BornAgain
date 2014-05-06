#ifndef SAMPLEVIEWALIGNER2_H
#define SAMPLEVIEWALIGNER2_H

#include <QMap>
#include <QModelIndex>
#include <QPointF>
class DesignerScene;
class IView;
class ParameterizedItem;

class SampleViewAligner2
{
public:
    SampleViewAligner2(DesignerScene *scene);

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
    static QMap<QString, int> m_typeToArea; //!< correspondance of ParameterizedItem's type and area on the screen,
};


#endif

