// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/MaskWidgets/LineViews.h
//! @brief     Defines classes VerticalLineView and HorizontalLineView
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
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
