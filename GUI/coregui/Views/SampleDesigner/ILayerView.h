// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/SampleDesigner/ILayerView.h
//! @brief     Declares class ILayerView
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef ILAYERVIEW_H
#define ILAYERVIEW_H

#include "ConnectableView.h" // inheriting from

class MultiLayerView;
class MultiLayerCandidate;

//! Base class for LayerView and MultiLayerView
//! Provides functionality for moving view on top of MultiLayer.
class BA_CORE_API_ ILayerView : public ConnectableView
{
    Q_OBJECT

public:
    ILayerView(QGraphicsItem *parent = 0);

    enum { TYPE = DesignerHelper::LAYER };

    int type() const { return TYPE; }

    virtual QString getLabel() const { return QString(); }

protected:
    QVariant itemChange(GraphicsItemChange change, const QVariant &value);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void update_appearance();

public slots:
    void onPropertyChange(const QString &propertyName);

private:
    void updateHeight();
    void updateColor();

    MultiLayerCandidate getMultiLayerCandidate();
    QPointF m_drag_start_position;
};


//! Class to hold MultiLayer candidate for dropping LayerView.
class MultiLayerCandidate
{
public:
    MultiLayerCandidate() : multilayer(0), row(-1), distance(0){}
    MultiLayerView *multilayer; //!< pointer to the candidate
    int row; //!< requested row number to drop in
    int distance; //!< distance from given ILayerView and drop area
    bool operator< (const MultiLayerCandidate& cmp) const;
    operator bool() const { return bool(multilayer); }
    //! returns line representing interface of multilayer in scene coordinates
    QLineF getInterfaceToScene();
};


#endif // ILAYERVIEW_H
