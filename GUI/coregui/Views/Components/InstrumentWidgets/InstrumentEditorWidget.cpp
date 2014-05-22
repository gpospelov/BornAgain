#include "InstrumentEditorWidget.h"


InstrumentEditorWidget::InstrumentEditorWidget(SessionModel *model, QWidget *parent)
    : QWidget(parent)
    , m_instrumentModel(model)
{

    setMinimumSize(400, 400);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

}

