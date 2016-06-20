// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/CommonWidgets/ItemComboWidget.h
//! @brief     Declares class ItemComboWidget
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef ITEMCOMBOWIDGET_H
#define ITEMCOMBOWIDGET_H

#include "WinDllMacros.h"
#include "IFactory.h"
#include <QWidget>
#include <QString>

class SessionItem;

//! The ItemComboWidget class combines stack of widgets with QComboBox controller to switch between
//! widgets. It is used in the case when one SessionItem can be presented with different widgets.

//! For example, in JobOutputDataWidget the results of the job can be presented with either
//! IntensityDataWidget or FitDataWidget, depending from the JobView's activity type.

class BA_CORE_API_ ItemComboWidget : public QWidget {
    Q_OBJECT

public:

    typedef QMap<QString, QWidget *(*)()> WidgetMap_t;

    explicit ItemComboWidget(QWidget *parent = 0);

    virtual void setItem(SessionItem *item);

//    void addWidget(const QString &presentationType, std::function<void(SessionItem*)> f);

    void add(const QString &presentationType, std::function<QWidget*()>);

private:
    class QStackedWidget *m_stackedWidget;
    SessionItem *m_currentItem;
    static WidgetMap_t m_widget_map;
    IFactory<QString, QWidget> m_factory;
};

#endif
