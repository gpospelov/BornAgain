#include "QuickSimulationSettings.h"

#include <QDebug>
#include <QGroupBox>
#include <QRadioButton>
#include <QHBoxLayout>
#include <QVBoxLayout>


QuickSimulationSettings::QuickSimulationSettings(QWidget *parent)
    :QWidget(parent)
{
    m_currentSliderRange = 10.0;

    QGroupBox *groupBox = new QGroupBox(tr("Slider Range:"), this);
    m_radio1 = new QRadioButton(tr("10%"));
    m_radio1->setChecked(true);
    connect(m_radio1,SIGNAL(clicked(bool)),this,SLOT(rangeChanged()));
    m_radio1->setAutoExclusive(true);

    m_radio2 = new QRadioButton(tr("100%"));
    connect(m_radio2,SIGNAL(clicked(bool)),this,SLOT(rangeChanged()));
    m_radio2->setAutoExclusive(true);

    m_radio3 = new QRadioButton(tr("1000%"));
    connect(m_radio3,SIGNAL(clicked(bool)),this,SLOT(rangeChanged()));
    m_radio3->setAutoExclusive(true);


    groupBox->setAlignment(Qt::Horizontal);

    QHBoxLayout *hbox = new QHBoxLayout;
    hbox->addWidget(m_radio1);
    hbox->addWidget(m_radio2);
    hbox->addWidget(m_radio3);
    hbox->addStretch(1);
    groupBox->setLayout(hbox);
    //setLayout(hbox);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(groupBox);

    setLayout(mainLayout);

}

void QuickSimulationSettings::rangeChanged()
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
    //qDebug() << "QuickSimulationSettings::rangeChanged()" << m_currentSliderRange;
    emit sliderRangeFactorChanged(m_currentSliderRange);
}
