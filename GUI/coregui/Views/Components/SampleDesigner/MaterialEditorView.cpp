#include "MaterialEditorView.h"
#include "MaterialModel.h"
#include "minisplitter.h"
#include <QTableView>
#include <QVBoxLayout>
#include <QDebug>


MaterialEditorView::MaterialEditorView(MaterialModel *model, QWidget *parent)
    : QWidget(parent)
    , m_materialModel(0)
    , m_tableView(new QTableView(this))
    , m_splitter(new Manhattan::MiniSplitter(this))

{
    setModel(model);

//    QVBoxLayout *layout = new QVBoxLayout(this);
//    layout->addWidget(m_tableView);

//    setLayout(layout);

    m_splitter->addWidget(m_tableView);
    m_splitter->addWidget(new QWidget(this));

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->setMargin(0);
    mainLayout->setSpacing(0);
    mainLayout->addWidget(m_splitter);
    setLayout(mainLayout);


}



void MaterialEditorView::setModel(MaterialModel *model)
{
    Q_ASSERT(model);
    if(model != m_materialModel) {
        m_materialModel = model;
        m_tableView->setModel(m_materialModel);
    }
}



