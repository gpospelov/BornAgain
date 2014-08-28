#ifndef INTERFERENCEFUNCTIONVIEWS_H
#define INTERFERENCEFUNCTIONVIEWS_H


#include "ConnectableView.h"

class BA_CORE_API_ InterferenceFunction1DParaCrystalView : public ConnectableView
{
    Q_OBJECT

public:
    enum { Type = DesignerHelper::InterferenceFunction1DParaType };

    InterferenceFunction1DParaCrystalView(QGraphicsItem *parent = 0);

    int type() const { return Type; }
};


class BA_CORE_API_ InterferenceFunction2DParaCrystalView : public ConnectableView
{
    Q_OBJECT

public:
    enum { Type = DesignerHelper::InterferenceFunction2DParaType };

    InterferenceFunction2DParaCrystalView(QGraphicsItem *parent = 0);

    int type() const { return Type; }
};

class BA_CORE_API_ InterferenceFunction2DLatticeView : public ConnectableView
{
    Q_OBJECT

public:
    enum { Type = DesignerHelper::InterferenceFunction2DLatticeType };

    InterferenceFunction2DLatticeView(QGraphicsItem *parent = 0);

    int type() const { return Type; }
};

#endif // INTERFERENCEFUNCTIONVIEWS_H
