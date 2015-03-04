// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/InstrumentWidgets/InstrumentEditorWidget.cpp
//! @brief     Implements class InstrumentEditorWidget
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "InstrumentEditorWidget.h"
#include "ParameterizedItem.h"
#include "BeamItem.h"
#include "DetectorItems.h"
#include "DetectorEditorWidget.h"
#include "BeamEditorWidget.h"
#include "InstrumentComponentsWidget.h"
#include "InstrumentItem.h"
#include <QBoxLayout>
#include <QGroupBox>
#include <QComboBox>
#include <QLineEdit>
#include <QScrollArea>
#include <QScrollBar>
#include <QEvent>
#include <QDebug>


class AdjustingScrollArea : public QScrollArea {
    bool eventFilter(QObject * obj, QEvent * ev) {
        if (obj == widget() && ev->type() != QEvent::Resize) {
//            setMaximumWidth(width() - viewport()->width() + widget()->width());
            widget()->setMaximumWidth(viewport()->width());
            setMaximumHeight(height() - viewport()->height() + widget()->height());
        }
        return QScrollArea::eventFilter(obj, ev);
    }

    QSize sizeHint() const {
        QScrollBar *horizontal = horizontalScrollBar();
        QSize result(viewport()->width(), widget()->height()+horizontal->height()*2);
        return result;
    }
public:
    AdjustingScrollArea(QWidget * parent = 0) : QScrollArea(parent)
    {
        setObjectName("MyScrollArea");
    }
    void setWidget(QWidget *w) {
        QScrollArea::setWidget(w);
        // It so happens that QScrollArea already filters widget events,
        // but that's an implementation detail that we shouldn't rely on.
        w->installEventFilter(this);
    }
};


InstrumentEditorWidget::InstrumentEditorWidget(QWidget *parent)
    : QWidget(parent)
    , m_nameLineEdit(new QLineEdit())
    , m_typeComboBox(new QComboBox())
    , m_currentItem(0)
    , m_block_signals(false)
    , m_instrumentComponents(new InstrumentComponentsWidget)
{
    setMinimumSize(400, 400);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    // main group box with all instrument parameters
    QGroupBox *instrumentGroup = new QGroupBox(tr("Instrument Parameters"));
    QVBoxLayout *instrumentGroupLayout = new QVBoxLayout;
    //instrumentGroupLayout->setContentsMargins(0,0,0,0);
    instrumentGroup->setLayout(instrumentGroupLayout);

    // top block with instrument name and type
    m_typeComboBox->setMinimumWidth(300);
    m_typeComboBox->addItem("Default GISAS Instrument");

    QHBoxLayout *topLayout = new QHBoxLayout;
    QGridLayout *nameAndTypeLayout = new QGridLayout;
    nameAndTypeLayout->addWidget(new QLabel("Name"), 0, 0);
    nameAndTypeLayout->addWidget(m_nameLineEdit, 0, 1);
    nameAndTypeLayout->addWidget(new QLabel("Type"), 1, 0);
    nameAndTypeLayout->addWidget(m_typeComboBox, 1, 1);
    topLayout->addLayout(nameAndTypeLayout );
    topLayout->addStretch(1);

    instrumentGroupLayout->addLayout(topLayout);

    // Scroling area with insturment components
    m_instrumentComponents->setStyleSheet("InstrumentComponentsWidget {background-color:black;}");

    AdjustingScrollArea *area = new AdjustingScrollArea;
    area->setWidgetResizable(true);
    area->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    area->setWidget(m_instrumentComponents);
    area->setContentsMargins( 0, 0, 0, 0 );
    area->setStyleSheet("QScrollArea#MyScrollArea {border: 0px; background-color:#D3D0CE;}");
    instrumentGroupLayout->addWidget(area, 1);
    instrumentGroupLayout->addStretch();

    // setting main layout
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(instrumentGroup);
    setLayout(mainLayout);

    connect(m_nameLineEdit, SIGNAL(textChanged(const QString &)), this, SLOT(onChangedEditor(const QString &)));
}




void InstrumentEditorWidget::setInstrumentItem(ParameterizedItem *instrument)
{
    Q_ASSERT(instrument);

    if(instrument != m_currentItem) {
        if(m_currentItem) {
            disconnect(m_currentItem, SIGNAL(propertyChanged(QString)), this, SLOT(onPropertyChanged(QString)));
            disconnect(m_currentItem, SIGNAL(subItemChanged(QString)), this, SLOT(onPropertyChanged(QString)));
        }

        m_currentItem = instrument;

        connect(m_currentItem, SIGNAL(propertyChanged(QString)), this, SLOT(onPropertyChanged(QString)));
        connect(m_currentItem, SIGNAL(subItemChanged(QString)), this, SLOT(onPropertyChanged(QString)));

        updateWidgets();
    }

    InstrumentItem *instrumentItem = dynamic_cast<InstrumentItem *>(instrument);

    m_instrumentComponents->setBeamItem(instrumentItem->getBeamItem());
    m_instrumentComponents->setDetectorItem(instrumentItem->getDetectorItem());
}


void InstrumentEditorWidget::onChangedEditor(const QString &)
{
    qDebug() << "InstrumentEditorWidget::onChangedEditor() ->";
    Q_ASSERT(m_currentItem);
    if(m_block_signals) return;
    qDebug() << "          InstrumentEditorWidget::onChangedEditor(): " << m_nameLineEdit->text();
    m_currentItem->setItemName(m_nameLineEdit->text());
}


void InstrumentEditorWidget::onPropertyChanged(const QString &)
{
    qDebug() << "InstrumentEditorWidget::onPropertyChanged() ->";
//    updateWidgets();
}


void InstrumentEditorWidget::updateWidgets()
{
    qDebug() << "InstrumentEditorWidget::updateWidgets() ->";
    Q_ASSERT(m_currentItem);
    m_block_signals = true;
    m_nameLineEdit->setText(m_currentItem->itemName());
    m_block_signals = false;
}





