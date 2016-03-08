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
#include "MaterialEditorWidget.h"
#include "MaterialUtils.h"
//#include <QStyle>
//#include <QStatusBar>
//#include <QToolBar>
#include <QVBoxLayout>
#include <QPushButton>
#include <QAction>
#include <QDebug>
//#include <QtTreePropertyBrowser>


//int MaterialEditorDialog::m_IndexOfUnnamed = 0;

MaterialEditorDialog::MaterialEditorDialog(MaterialModel *materialModel, QWidget *parent)
    : QDialog(parent)
    , m_materialEditor(new MaterialEditorWidget(materialModel, this))
{
    setWindowTitle("Material Editor");
    setMinimumSize(128, 128);
    resize(512, 400);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setContentsMargins(0,0,0,0);
    layout->addWidget(m_materialEditor);

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
    setLayout(layout);
}

void MaterialEditorDialog::onSelectButton()
{
   accept();
}


void MaterialEditorDialog::onCancelButton()
{
    reject();
}

MaterialProperty MaterialEditorDialog::getSelectedMaterialProperty()
{
    if(MaterialItem *material = m_materialEditor->getSelectedMaterial()) {
        return MaterialProperty(material->getIdentifier());
    }

    return MaterialProperty();
}

