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
#include <QComboBox>



InstrumentView2::InstrumentView2(SessionModel *model, QWidget *parent)
    : QWidget(parent)
    , m_instrumentModel(model)
//    , m_splitter(new Manhattan::MiniSplitter(this))
    , m_instrumentSelector(new InstrumentSelectorWidget(m_instrumentModel, this))
//    , m_instrumentEditor(new InstrumentEditorWidget(m_instrumentModel, this))
{
//    setInstrumentModel(model);

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

//    Q_ASSERT(m_listView->selectionModel());
    connect(m_instrumentSelector,
        SIGNAL( selectionChanged(const QItemSelection&, const QItemSelection&) ),
        this,
        SLOT( onSelectionChanged(const QItemSelection&, const QItemSelection&) )
        );


}


//void JobOutputDataWidget::onJobItemDelete(JobItem *item)
//{
//    qDebug() << "JobOutputDataWidget::onJobItemDelete()";
//    OutputDataWidget *widget = m_jobItemToPlotWidget[item];
//    if( !widget ) {
//        throw GUIHelpers::Error("JobOutputDataWidget::onJobItemDelete -> Can't find widget");
//    }
//    m_stack->removeWidget(widget);
//    delete widget;
//}




void InstrumentView2::onSelectionChanged(const QItemSelection &selected, const QItemSelection & /* deselected */)
{
    qDebug() << "InstrumentView2::onSelectionChanged()";
    ParameterizedItem *instrument = m_instrumentModel->itemForIndex(selected.indexes().back());
    qDebug() << "InstrumentView2::onSelectionChanged()" << instrument->itemName();

    InstrumentEditorWidget *widget = m_instrumentToEditor[instrument];

    if( !widget) {
        widget = new InstrumentEditorWidget();
        widget->setInstrumentItem(instrument);
        m_stackWidget->addWidget(widget);
        m_instrumentToEditor[instrument] = widget;
    }
    m_stackWidget->setCurrentWidget(widget);

}

