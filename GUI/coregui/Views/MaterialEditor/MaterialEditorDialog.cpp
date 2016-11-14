// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/MaterialEditor/MaterialEditorDialog.cpp
//! @brief     Implements class MaterialEditorDialog
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "MaterialEditorDialog.h"
#include "MaterialEditor.h"
#include "MaterialModel.h"
#include "MaterialUtils.h"
#include "mainwindow_constants.h"
#include <QAction>
#include <QDebug>
#include <QPushButton>
#include <QSettings>
#include <QVBoxLayout>

namespace {
const QSize default_dialog_size(512, 400);
}

MaterialEditorDialog::MaterialEditorDialog(MaterialModel *materialModel, QWidget *parent)
    : QDialog(parent)
    , m_origMaterialModel(materialModel)
    , m_materialEditor(0)
{
    setWindowTitle("Material Editor");
    setMinimumSize(128, 128);
    resize(default_dialog_size);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    init_material_editor();

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setContentsMargins(0,0,0,0);
    layout->addWidget(m_materialEditor);

    QPushButton *okButton = new QPushButton("OK");
    connect(okButton, SIGNAL(clicked()), this, SLOT(onOKButton()));
    QPushButton *cancelButton = new QPushButton("Cancel");
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
    if(m_materialEditor->isModelWasModified()) {
        m_origMaterialModel->clear();
        m_origMaterialModel->initFrom(m_tmpMaterialModel.get(), 0);
    }
    writeSettings();
    accept();
}


void MaterialEditorDialog::onCancelButton()
{
    writeSettings();
    reject();
}

void MaterialEditorDialog::init_material_editor()
{
    Q_ASSERT(m_origMaterialModel);
    m_tmpMaterialModel.reset(m_origMaterialModel->createCopy());
    m_materialEditor = new MaterialEditor(m_tmpMaterialModel.get(), this);
    //    m_materialEditor = new MaterialEditor(m_origMaterialModel, this);
    readSettings();

}

void MaterialEditorDialog::readSettings()
{
    QSettings settings;
    if (settings.childGroups().contains(Constants::S_MATERIALEDITOR)) {
        settings.beginGroup(Constants::S_MATERIALEDITOR);
        resize(settings.value(Constants::S_WINDOWSIZE, default_dialog_size).toSize());
        if(settings.contains(Constants::S_WINDOWPOSITION)) {
            move(settings.value(Constants::S_WINDOWPOSITION).toPoint());
        }
    }
    else {
        resize(default_dialog_size);
    }
}

void MaterialEditorDialog::writeSettings()
{
    QSettings settings;
    settings.beginGroup(Constants::S_MATERIALEDITOR);
    settings.setValue(Constants::S_WINDOWSIZE, this->size());
    settings.setValue(Constants::S_WINDOWPOSITION, this->pos());
    settings.endGroup();
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

