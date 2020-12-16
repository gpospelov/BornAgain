// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "gui2/settingsview/settingsview.h"
#include "gui2/model/applicationmodels.h"
#include "mvvm/model/sessionmodel.h"
#include "mvvm/widgets/allitemstreeview.h"
#include "mvvm/widgets/widgetutils.h"
#include <QHBoxLayout>
#include <QListView>
#include <QListWidget>
#include <QStackedWidget>
#include <QTabWidget>
#include <QTreeView>

namespace gui2 {

SettingsView::SettingsView(ApplicationModels* models, QWidget* parent)
    : QWidget(parent)
    , m_listWidget(new QListWidget)
    , m_stackedWidget(new QStackedWidget)
    , m_tabWidget(new QTabWidget)
    , m_models(models) {
    init_list_selector();
    init_model_settings();
    init_other_settings();

    auto layout = new QHBoxLayout(this);
    layout->addWidget(m_listWidget);
    layout->addSpacing(ModelView::Utils::WidthOfLetterM() / 2);
    layout->addWidget(m_stackedWidget);

    m_stackedWidget->setCurrentIndex(0);
}

//! Initialize tabs with model content.
//! Each model will be represented by a single tree (with all items shown) in a tab.

void SettingsView::init_model_settings() {
    for (auto model : m_models->application_models()) {
        auto view = new ModelView::AllItemsTreeView(model);
        view->treeView()->setAlternatingRowColors(true);
        m_tabWidget->addTab(view, QString::fromStdString(model->modelType()));
    }
    m_stackedWidget->addWidget(m_tabWidget);
}

void SettingsView::init_list_selector() {
    const int width = ModelView::Utils::WidthOfLetterM() * 10;
    m_listWidget->setFixedWidth(width);
    m_listWidget->setIconSize(
        QSize(ModelView::Utils::WidthOfLetterM() * 1.2, ModelView::Utils::WidthOfLetterM() * 1.2));

    auto item = new QListWidgetItem(QIcon(":/icons/card-bulleted-outline.svg"), "All models");
    m_listWidget->addItem(item);

    item = new QListWidgetItem(QIcon(":/icons/cog-outline.svg"), "Miscellaneous");
    m_listWidget->addItem(item);

    connect(m_listWidget, &QListWidget::currentRowChanged,
            [this](int row) { m_stackedWidget->setCurrentIndex(row); });
}

void SettingsView::init_other_settings() {
    m_stackedWidget->addWidget(new QWidget);
}

} // namespace gui2
