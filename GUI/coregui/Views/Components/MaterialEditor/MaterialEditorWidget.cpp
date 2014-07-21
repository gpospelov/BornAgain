#include "MaterialEditorWidget.h"
#include "MaterialPropertyBrowser.h"
#include "MaterialModel.h"
#include "MaterialUtils.h"
#include <QStyle>
#include <QStatusBar>
#include <QToolBar>
#include <QVBoxLayout>
#include <QPushButton>
#include <QAction>
#include <QDebug>
#include <QtTreePropertyBrowser>


int MaterialEditorWidget::m_IndexOfUnnamed = 0;

MaterialEditorWidget::MaterialEditorWidget(MaterialModel *materialModel, QWidget *parent)
    : QDialog(parent)
    , m_materialModel(materialModel)
    , m_propertyBrowser(new MaterialPropertyBrowser(materialModel, this))
    , m_statusBar(0)
    , m_toolBar(0)
{
    setWindowTitle("Material Editor");
    setMinimumSize(128, 128);
    resize(512, 400);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    m_toolBar = new QToolBar;
    m_toolBar->setFixedHeight(28);
    m_toolBar->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    const int size = style()->pixelMetric(QStyle::PM_SmallIconSize);
    m_toolBar->setIconSize(QSize(size, size));
    m_toolBar->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);

    m_statusBar = new QStatusBar;

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setMargin(0);
    layout->setSpacing(0);
    layout->addWidget(m_toolBar);
    layout->addWidget(m_propertyBrowser);

    QPushButton *selectButton = new QPushButton(tr("Select"));
    connect(selectButton, SIGNAL(clicked()), this, SLOT(onSelectButton()));
    QPushButton *cancelButton = new QPushButton(tr("Cancel"));
    connect(cancelButton, SIGNAL(clicked()), this, SLOT(onCancelButton()));

    QHBoxLayout *buttonsLayout = new QHBoxLayout;
    buttonsLayout->setMargin(10);
    buttonsLayout->setSpacing(5);

    buttonsLayout->addStretch(1);
    buttonsLayout->addWidget(selectButton);
    buttonsLayout->addWidget(cancelButton);

    layout->addLayout(buttonsLayout);
    layout->addWidget(m_statusBar);

    setLayout(layout);

    setupActions();
}


void MaterialEditorWidget::setModel(MaterialModel *materialModel)
{
    Q_ASSERT(materialModel);
    if(materialModel != m_materialModel) {
        m_materialModel = materialModel;
        m_propertyBrowser->setModel(materialModel);
    }

}


void MaterialEditorWidget::showMessage(const QString &message)
{
    m_statusBar->showMessage(message, 4000);
}


void MaterialEditorWidget::onSelectButton()
{
    if(m_propertyBrowser->getSelectedMaterial()) {
        accept();
    } else {
        showMessage("Please select material");
    }
}


void MaterialEditorWidget::onCancelButton()
{
    reject();
}



void MaterialEditorWidget::setupActions()
{
    QAction *addMaterialAction = new QAction(QIcon(":/SampleDesigner/images/card--plus.png"), tr("Add material"), this);
    connect(addMaterialAction, SIGNAL(triggered()), this, SLOT(addMaterial()));
    m_toolBar->addAction(addMaterialAction);

    QAction *removeMaterialAction = new QAction(QIcon(":/SampleDesigner/images/card--minus.png"), tr("Remove selected material"), this);
    connect(removeMaterialAction, SIGNAL(triggered()), this, SLOT(removeMaterial()));
    m_toolBar->addAction(removeMaterialAction);
}


void MaterialEditorWidget::addMaterial()
{
    Q_ASSERT(0);
    qDebug() << "MaterialEditorWidget::addMaterial() -> ";
//    QString name = QString("unnamed%1").arg(m_IndexOfUnnamed);
//    m_materialModel->addMaterial(name, MaterialItem::HomogeneousMaterial);
    m_IndexOfUnnamed++;
}


void MaterialEditorWidget::removeMaterial()
{
    Q_ASSERT(0);
    qDebug() << "MaterialEditorWidget::removeMaterial() -> ";
//    MaterialItem *material = m_propertyBrowser->getSelectedMaterial();
//    if(material) {
//        m_materialModel->removeMaterial(material);
//    } else {
//        showMessage("Select material to remove");
//    }
}


MaterialProperty MaterialEditorWidget::getSelectedMaterialProperty()
{
    MaterialItem *material = m_propertyBrowser->getSelectedMaterial();
    if(material)
        return MaterialUtils::getMaterialProperty(material);

    return MaterialProperty();
}

