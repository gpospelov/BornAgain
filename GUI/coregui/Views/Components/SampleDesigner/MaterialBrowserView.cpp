#include "MaterialBrowserView.h"
#include "MaterialBrowserModel.h"
#include <QTableView>
#include <QVBoxLayout>
#include <QHeaderView>
#include <iostream>

MaterialBrowserView::MaterialBrowserView(QWidget *parent)
    : QDialog(parent)
    , m_tableView(0)
{
    std::cout << "MaterialEditorView::MaterialEditorView() ->  " << std::endl;
    setMinimumSize(128, 128);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    std::cout << "MaterialEditorView::MaterialEditorView() ->  1.1" << std::endl;
    m_tableView = new QTableView(this);
    std::cout << "MaterialEditorView::MaterialEditorView() ->  1.2" << std::endl;
    m_tableModel = new MaterialBrowserModel(0);
    std::cout << "MaterialEditorView::MaterialEditorView() ->  1.3" << std::endl;
    m_tableView->setModel( m_tableModel );
    std::cout << "MaterialEditorView::MaterialEditorView() ->  1.4" << std::endl;

    m_tableView->horizontalHeader()->setStretchLastSection(true);
    std::cout << "MaterialEditorView::MaterialEditorView() ->  1.5" << std::endl;

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(m_tableView);
    layout->setMargin(0);
    layout->setSpacing(0);
    setLayout(layout);
    std::cout << "MaterialEditorView::MaterialEditorView() ->  1.6" << std::endl;

    show();
    std::cout << "MaterialEditorView::MaterialEditorView() ->  1.7" << std::endl;
}
