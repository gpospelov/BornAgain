// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/InstrumentWidgets/ComboWidget.cpp
//! @brief     Implements class ComboWidget
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "ComboWidget.h"
#include "GUIHelpers.h"
#include <QBoxLayout>
#include <QComboBox>
#include <QDoubleSpinBox>
#include <QGridLayout>
#include <QGroupBox>
#include <QLabel>
#include <QPushButton>
#include <QSpinBox>

ComboWidget::ComboWidget(QString item, QGridLayout *layout, QWidget *parent)
    : QWidget(parent)
    , m_collapsed(false)

{
    m_detailsLayout = layout;

    m_mainComboBox = new QComboBox();
    m_mainComboBox->addItem(item);

    m_icon_collapse = new QIcon(":/images/collapse_arrow.png"  );
    m_icon_expand = new QIcon(":/images/expand_arrow.png"  );

    m_detailsButton = new QPushButton("Details");
    m_detailsButton->setFixedWidth(75);
    //m_detailsButton->setLayoutDirection(Qt::RightToLeft);
    //detailsButton->setCheckable(true);
    m_detailsButton->setIcon(QIcon( m_collapsed ?
                 *m_icon_expand :
                 *m_icon_collapse));
    m_detailsButton->setIconSize(QSize(16,16));


    QGridLayout *comboLayout = new QGridLayout;
    comboLayout->addWidget(m_mainComboBox, 0, 0);
    comboLayout->addWidget(m_detailsButton, 0, 1);


    if(m_detailsLayout)
    {
        comboLayout->addLayout(m_detailsLayout, 1, 0);
    }

    connect(m_detailsButton, SIGNAL(clicked()),this, SLOT(onDetailsButtonClicked()));


    // main layout
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(comboLayout);
    setLayout(mainLayout);
}

void ComboWidget::onDetailsButtonClicked()
{
    setCollapse(!m_collapsed);
    m_detailsButton->setIcon(QIcon( m_collapsed ?
                 *m_icon_expand :
                 *m_icon_collapse));
}

void ComboWidget::setCollapse( bool collapse )
{
    for (int i = 0; i < m_detailsLayout->count(); ++i)
    {
      m_detailsLayout->itemAt(i)->widget()->setVisible(!collapse);
    }

    m_collapsed = collapse;

}

void ComboWidget::addItem(QString item)
{
    m_mainComboBox->addItem(item);
}
