// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/InstrumentWidgets/ComboWidget.h
//! @brief     Declares class ComboWidget
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef COMBOWIDGET_H
#define COMBOWIDGET_H

#include "WinDllMacros.h"
#include <QWidget>

class QComboBox;
class QLabel;
class QSpinBox;
class QDoubleSpinBox;
class QGridLayout;
class QPushButton;

class BA_CORE_API_ ComboWidget : public QWidget
{
    Q_OBJECT

public:
    ComboWidget(QString item, QGridLayout *layout = 0, QWidget *parent = 0);
    void addItem(QString item);

public slots:
    void onDetailsButtonClicked();

private:
    bool m_collapsed;
    QGridLayout *m_detailsLayout;
    QComboBox *m_mainComboBox;
    QPushButton *m_detailsButton;
    QIcon *m_icon_collapse, *m_icon_expand;

    void setCollapse(bool);
};

#endif
