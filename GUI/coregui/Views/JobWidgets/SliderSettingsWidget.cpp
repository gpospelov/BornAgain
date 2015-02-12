// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/JobWidgets/SliderSettingsWidget.cpp
//! @brief     Implements class SliderSettingsWidget
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "SliderSettingsWidget.h"

#include <QDebug>
#include <QGroupBox>
#include <QRadioButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>


SliderSettingsWidget::SliderSettingsWidget(QWidget *parent)
    : QWidget(parent)
    , m_currentSliderRange(100.0)
{
    QString tooltip("Allows to tune sample parameters within +/- of given range \nwith the help of the slider.");

    QLabel *label = new QLabel("Tuning:");
    label->setToolTip(tooltip);

    m_radio1 = new QRadioButton(tr("10%"));
    m_radio1->setAutoExclusive(true);
    m_radio1->setToolTip(tooltip);
    connect(m_radio1,SIGNAL(clicked(bool)),this,SLOT(rangeChanged()));

    m_radio2 = new QRadioButton(tr("100%"));
    m_radio2->setChecked(true);
    m_radio2->setAutoExclusive(true);
    m_radio2->setToolTip(tooltip);
    connect(m_radio2,SIGNAL(clicked(bool)),this,SLOT(rangeChanged()));

    m_radio3 = new QRadioButton(tr("1000%"));
    m_radio3->setAutoExclusive(true);
    m_radio3->setToolTip(tooltip);
    connect(m_radio3,SIGNAL(clicked(bool)),this,SLOT(rangeChanged()));

    QHBoxLayout *hbox = new QHBoxLayout;

    hbox->addWidget(label);
    hbox->addWidget(m_radio1);
    hbox->addWidget(m_radio2);
    hbox->addWidget(m_radio3);
    hbox->addStretch(1);

    setLayout(hbox);
}


void SliderSettingsWidget::rangeChanged()
{
    if(m_radio1->isChecked())
    {
        m_currentSliderRange = 10.0;
    }
    else if(m_radio2->isChecked())
    {
        m_currentSliderRange = 100.0;
    }
    else if(m_radio3->isChecked())
    {
        m_currentSliderRange = 1000.0;
    }
    emit sliderRangeFactorChanged(m_currentSliderRange);
}
