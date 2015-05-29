// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/TestView.h
//! @brief     Defines class TestView
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //
#include <QWidget>
#include <QGraphicsProxyWidget>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include "DistributionEditor.h"
#include <QGraphicsView>
#include <QPainterPath>

#ifndef TESTVIEW_H
#define TESTVIEW_H

class ParameterizedItem;
class AwesomePropertyEditor;

class TestView : public QGraphicsView
{
    Q_OBJECT
public:
    TestView(QWidget *parent = 0);
    virtual ~TestView()
    {
    }

    void setItem(ParameterizedItem *item);

    void plotItem(ParameterizedItem *item);

private slots:
    //    void onPropertyChanged(const QString &property_name);
    //    void onSubItemChanged(const QString &property_name);
    //    void onSubItemPropertyChanged(const QString &property_group, const QString
    //    &property_name);

private:
    AwesomePropertyEditor *m_propertyEditor;
    ParameterizedItem *m_item;
};

#endif
