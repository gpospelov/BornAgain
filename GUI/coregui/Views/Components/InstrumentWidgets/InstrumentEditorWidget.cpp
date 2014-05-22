#include "InstrumentEditorWidget.h"
#include "ParameterizedItem.h"
#include <QBoxLayout>

InstrumentEditorWidget::InstrumentEditorWidget(QWidget *parent)
    : QWidget(parent)
    , m_label(new QLabel)
{

    setMinimumSize(400, 400);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    QVBoxLayout *verticalLayout = new QVBoxLayout;
    verticalLayout->addWidget(m_label);

    setLayout(verticalLayout);

}

void InstrumentEditorWidget::setInstrumentItem(ParameterizedItem *instrument)
{
    m_label->setText(instrument->itemName());
}

