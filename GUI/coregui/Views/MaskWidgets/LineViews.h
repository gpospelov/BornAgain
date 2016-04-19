// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/MaskWidgets/LineViews.h
//! @brief     Declares classes VerticalLineView and HorizontalLineView
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef LINEVIEWS_H
#define LINEVIEWS_H

#include "IMaskView.h"

//! This is a view of VerticalLineItem mask

class BA_CORE_API_ VerticalLineView : public IMaskView
{
    Q_OBJECT

public:
    int type() const { return MaskEditorHelper::VERTICALLINE; }

    VerticalLineView();

public slots:
    virtual void update_view();
    virtual void onChangedX();
    virtual void onPropertyChange(const QString &propertyName);

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *);
    QVariant itemChange(GraphicsItemChange change, const QVariant &value);
private:
    bool m_block_on_property_change;
};

//! This is a view of HorizontalLineItem mask

class BA_CORE_API_ HorizontalLineView : public IMaskView
{
    Q_OBJECT

public:
    int type() const { return MaskEditorHelper::HORIZONTALLINE; }

    HorizontalLineView();

public slots:
    virtual void update_view();
    virtual void onChangedY();
    virtual void onPropertyChange(const QString &propertyName);

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *);
    QVariant itemChange(GraphicsItemChange change, const QVariant &value);
private:
    bool m_block_on_property_change;
};


#endif
