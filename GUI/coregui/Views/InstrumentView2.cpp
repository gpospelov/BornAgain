#include "InstrumentView2.h"
#include "SessionModel.h"
#include "InstrumentSelectorWidget.h"
#include "InstrumentEditorWidget.h"
#include "styledbar.h"
#include "minisplitter.h"
#include <QBoxLayout>
#include <QListView>
#include <QStackedWidget>
#include <QPushButton>
#include <QToolButton>
#include <QMenu>
#include <QAction>
#include <QDebug>




InstrumentView2::InstrumentView2(SessionModel *model, QWidget *parent)
    : QWidget(parent)
    , m_instrumentModel(model)
//    , m_splitter(new Manhattan::MiniSplitter(this))
    , m_instrumentSelector(new InstrumentSelectorWidget(m_instrumentModel, this))
//    , m_instrumentEditor(new InstrumentEditorWidget(m_instrumentModel, this))
{

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->setMargin(0);
    mainLayout->setSpacing(0);

    Manhattan::StyledBar *bar = new Manhattan::StyledBar;

    m_stackWidget = new QStackedWidget;

    QHBoxLayout *horizontalLayout = new QHBoxLayout;
    horizontalLayout->addWidget(m_instrumentSelector);
    horizontalLayout->addWidget(m_stackWidget, 1);

    mainLayout->addWidget(bar);
    mainLayout->addLayout(horizontalLayout);
    setLayout(mainLayout);

}


