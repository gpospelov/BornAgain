#ifndef INTERFERENCEFUNCTIONVIEWS_H
#define INTERFERENCEFUNCTIONVIEWS_H


#include "ConnectableView.h"

class BA_CORE_API_ InterferenceFunction1DParaCrystalView : public ConnectableView
{
    Q_OBJECT

public:
    enum { TYPE = DesignerHelper::INTERFERENCE_FUNCTION_1D_PARA };

    InterferenceFunction1DParaCrystalView(QGraphicsItem *parent = 0);

    int type() const { return TYPE; }
};


class BA_CORE_API_ InterferenceFunction2DParaCrystalView : public ConnectableView
{
    Q_OBJECT

public:
    enum { TYPE = DesignerHelper::INTERFERENCE_FUNCTION_2D_PARA };

    InterferenceFunction2DParaCrystalView(QGraphicsItem *parent = 0);

    int type() const { return TYPE; }
};

class BA_CORE_API_ InterferenceFunction2DLatticeView : public ConnectableView
{
    Q_OBJECT

public:
    enum { TYPE = DesignerHelper::INTERFERENCE_FUNCTION_2D_LATTICE };

    InterferenceFunction2DLatticeView(QGraphicsItem *parent = 0);

    int type() const { return TYPE; }
};

#endif // INTERFERENCEFUNCTIONVIEWS_H
