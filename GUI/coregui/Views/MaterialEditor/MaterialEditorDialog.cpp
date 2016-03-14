// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/MaterialEditor/MaterialEditorWidget.cpp
//! @brief     Implements class MaterialEditorWidget
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "MaterialEditorDialog.h"
#include "MaterialModel.h"
#include "MaterialEditor.h"
#include "MaterialUtils.h"
#include <QVBoxLayout>
#include <QPushButton>
#include <QAction>
#include <QDebug>


MaterialEditorDialog::MaterialEditorDialog(MaterialModel *materialModel, QWidget *parent)
    : QDialog(parent)
    , m_origMaterialModel(materialModel)
    , m_materialEditor(0)
{
    setWindowTitle("Material Editor");
    setMinimumSize(128, 128);
    resize(512, 400);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    init_material_editor();

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setContentsMargins(0,0,0,0);
    layout->addWidget(m_materialEditor);

    QPushButton *okButton = new QPushButton(tr("OK"));
    connect(okButton, SIGNAL(clicked()), this, SLOT(onOKButton()));
    QPushButton *cancelButton = new QPushButton(tr("Cancel"));
    connect(cancelButton, SIGNAL(clicked()), this, SLOT(onCancelButton()));

    QHBoxLayout *buttonsLayout = new QHBoxLayout;
    buttonsLayout->setMargin(10);
    buttonsLayout->setSpacing(5);

    buttonsLayout->addStretch(1);
    buttonsLayout->addWidget(okButton);
    buttonsLayout->addWidget(cancelButton);

    layout->addLayout(buttonsLayout);
    setLayout(layout);
}

//! replaces original material model with the model modified by MaterialEditor
void MaterialEditorDialog::onOKButton()
{
    m_origMaterialModel->clear();
    m_origMaterialModel->initFrom(m_tmpMaterialModel.get(), 0);
    accept();
}


void MaterialEditorDialog::onCancelButton()
{
    reject();
}

void MaterialEditorDialog::init_material_editor()
{
    Q_ASSERT(m_origMaterialModel);
    m_tmpMaterialModel.reset(m_origMaterialModel->createCopy());
    m_materialEditor = new MaterialEditor(m_tmpMaterialModel.get(), this);
//    m_materialEditor = new MaterialEditor(m_origMaterialModel, this);
}

MaterialProperty MaterialEditorDialog::getSelectedMaterialProperty()
{
    if(MaterialItem *material = m_materialEditor->getSelectedMaterial()) {
        return MaterialProperty(material->getIdentifier());
    }

    return MaterialProperty();
}

//!
void MaterialEditorDialog::setInitialMaterialProperty(const MaterialProperty &matProperty)
{
    Q_ASSERT(m_materialEditor);

    m_materialEditor->setInitialMaterialProperty(matProperty);

}

