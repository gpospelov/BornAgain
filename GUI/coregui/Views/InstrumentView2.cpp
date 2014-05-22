#include "InstrumentView2.h"
#include "InstrumentSelectorWidget.h"
#include "InstrumentEditorWidget.h"
#include "styledbar.h"
#include "minisplitter.h"
#include <QVBoxLayout>




InstrumentView2::InstrumentView2(SessionModel *model, QWidget *parent)
    : QWidget(parent)
    , m_instrumentModel(model)
    , m_splitter(new Manhattan::MiniSplitter(this))
    , m_instrumentSelector(new InstrumentSelectorWidget(m_instrumentModel, this))
    , m_instrumentEditor(new InstrumentEditorWidget(m_instrumentModel, this))
{

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->setMargin(0);
    mainLayout->setSpacing(0);

    Manhattan::StyledBar *bar = new Manhattan::StyledBar;

    m_splitter->addWidget(m_instrumentSelector);
    m_splitter->addWidget(m_instrumentEditor);

    mainLayout->addWidget(bar);
    mainLayout->addWidget(m_splitter);
    setLayout(mainLayout);


    setLayout(mainLayout);

}


