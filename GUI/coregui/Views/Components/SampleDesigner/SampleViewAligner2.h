#ifndef SAMPLEVIEWALIGNER2_H
#define SAMPLEVIEWALIGNER2_H

#include <QMap>
#include <QModelIndex>
#include <QPointF>
class DesignerScene;
class IView;
class ConnectableView;
class ParameterizedItem;

class SampleViewAligner2
{
public:
    SampleViewAligner2(DesignerScene *scene);
    void align();

    void updateViews(const QModelIndex & parentIndex = QModelIndex(), QPointF reference = QPointF());

    void alignSample(ParameterizedItem *item, QPointF reference);

    void updateForces();
    void calculateForces(ConnectableView *view);
    void advance();


private:

    QList<ConnectableView *> getConnectedViews(ConnectableView *view);

    DesignerScene *m_scene;
    QList<ConnectableView *> m_views; //!< list of all views which are subject to align
    QMap<ConnectableView *, QPointF> m_viewToPos;

    static QMap<QString, int> m_typeToArea; //!< correspondance of ParameterizedItem's type and area on the screen,

    QMap<ConnectableView *, QList<ConnectableView *> > m_connectedViews;
};


#endif

