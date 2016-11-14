// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/InstrumentWidgets/InstrumentEditorWidget.cpp
//! @brief     Implements class InstrumentEditorWidget
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "InstrumentEditorWidget.h"
#include "BeamEditorWidget.h"
#include "BeamItem.h"
#include "DetectorEditorWidget.h"
#include "DetectorItems.h"
#include "InstrumentComponentsWidget.h"
#include "InstrumentItem.h"
#include "SessionItem.h"
#include <QBoxLayout>
#include <QComboBox>
#include <QDebug>
#include <QEvent>
#include <QGroupBox>
#include <QLineEdit>
#include <QScrollArea>
#include <QScrollBar>


class AdjustingScrollArea : public QScrollArea {
    bool eventFilter(QObject * obj, QEvent * ev) {
        if (obj == widget() && ev->type() != QEvent::Resize) {
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
    QGroupBox *instrumentGroup = new QGroupBox("Instrument Parameters");
    QVBoxLayout *instrumentGroupLayout = new QVBoxLayout;
    instrumentGroupLayout->setContentsMargins(0,0,0,0);
    instrumentGroup->setLayout(instrumentGroupLayout);

    instrumentGroupLayout->addSpacing(10);
    instrumentGroupLayout->addLayout(create_NameAndTypeLayout());

    // Scroling area with insturment components
    m_instrumentComponents->setStyleSheet("InstrumentComponentsWidget {background-color:transparent;}");

    AdjustingScrollArea *area = new AdjustingScrollArea;
    area->setContentsMargins( 0, 0, 0, 0 );
    area->setWidgetResizable(true);
    area->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    area->setWidget(m_instrumentComponents);
    area->setStyleSheet("QScrollArea#MyScrollArea {border: 0px; background-color:transparent;}");
    instrumentGroupLayout->addWidget(area, 1);
    instrumentGroupLayout->addStretch();

    // setting main layout
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(instrumentGroup);
    setLayout(mainLayout);

    connect(m_nameLineEdit,
            SIGNAL(textChanged(const QString &)),
            this,
            SLOT(onChangedEditor(const QString &))
            );

    connect(m_instrumentComponents,
            SIGNAL(extendedDetectorEditorRequest(DetectorItem *)),
            this,
            SIGNAL(extendedDetectorEditorRequest(DetectorItem *))
            );
}

void InstrumentEditorWidget::setInstrumentItem(SessionItem *instrument)
{
    Q_ASSERT(instrument);
    if(instrument != m_currentItem) {
        if(m_currentItem) {
            // TODO restore logic
//            disconnect(m_currentItem,
//                       SIGNAL(propertyChanged(QString)),
//                       this,
//                       SLOT(onPropertyChanged(QString))
//                       );
//            disconnect(m_currentItem,
//                       SIGNAL(subItemChanged(QString)),
//                       this,
//                       SLOT(onPropertyChanged(QString))
//                       );
        }
        m_currentItem = instrument;
//        connect(m_currentItem,
//                   SIGNAL(propertyChanged(QString)),
//                   this,
//                   SLOT(onPropertyChanged(QString))
//                   );
//        connect(m_currentItem,
//                   SIGNAL(subItemChanged(QString)),
//                   this,
//                   SLOT(onPropertyChanged(QString))
//                   );
        updateWidgets();
    }
    InstrumentItem *instrumentItem = dynamic_cast<InstrumentItem *>(instrument);

    m_instrumentComponents->setBeamItem(instrumentItem->beamItem());
    m_instrumentComponents->setDetectorItem(instrumentItem->detectorItem());
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
}

//! top block with instrument name and type
QLayout *InstrumentEditorWidget::create_NameAndTypeLayout()
{
    QHBoxLayout *result = new QHBoxLayout;
    m_nameLineEdit->setMinimumWidth(200);
    m_typeComboBox->addItem("Default GISAS Instrument");

    result->addSpacing(17);
    result->addWidget(new QLabel("Name"));
    result->addWidget(m_nameLineEdit);
    result->addSpacing(5);
    result->addWidget(new QLabel("Type"));
    result->addWidget(m_typeComboBox);
    result->addSpacing(18);
    result->addStretch(1);

    return result;
}

void InstrumentEditorWidget::updateWidgets()
{
    qDebug() << "InstrumentEditorWidget::updateWidgets() ->";
    Q_ASSERT(m_currentItem);
    m_block_signals = true;
    m_nameLineEdit->setText(m_currentItem->itemName());
    m_block_signals = false;
}
