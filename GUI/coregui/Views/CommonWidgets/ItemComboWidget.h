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

#include "IFactory.h"
#include "WinDllMacros.h"
#include <QMap>
#include <QString>
#include <QWidget>

class SessionItem;
class SessionItemWidget;
class ItemComboToolBar;

//! The ItemComboWidget class combines stack of widgets with QComboBox controller to switch between
//! widgets. It is used in the case when one SessionItem can be presented with different widgets.

//! For example, in JobOutputDataWidget the results of the job can be presented with either
//! IntensityDataWidget or FitDataWidget, depending from the JobView's activity type.

class BA_CORE_API_ ItemComboWidget : public QWidget {
    Q_OBJECT

public:
    typedef std::function<SessionItemWidget*()> factory_function_t;

    explicit ItemComboWidget(QWidget *parent = 0);

    virtual void setItem(SessionItem *item);

    void registerWidget(const QString &presentationType, factory_function_t);

    void setPresentation(const QString &presentationType);


protected:
//    virtual void showEvent(class QShowEvent *);
//    virtual void hideEvent(class QHideEvent *);
    virtual QStringList getValidPresentationList(SessionItem *item);

private slots:
    void onComboChanged(const QString &name);

private:
    QString currentPresentation() const;

    ItemComboToolBar *m_toolBar;
    class QStackedWidget *m_stackedWidget;
    SessionItem *m_currentItem;
    IFactory<QString, SessionItemWidget> m_widgetFactory;
    QMap<QString, SessionItemWidget *> m_presentationTypeToWidget;

};

#endif // ITEMCOMBOWIDGET_H
