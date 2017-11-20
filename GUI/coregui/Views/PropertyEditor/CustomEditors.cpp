// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/PropertyEditor/CustomEditors.h
//! @brief     Implements CustomEditors classes
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "CustomEditors.h"
#include "CustomEventFilters.h"
#include "MaterialProperty.h"
#include "MaterialSvc.h"
#include <QBoxLayout>
#include <QLabel>
#include <QToolButton>

//! Sets the data from the model to editor.

void CustomEditor::setData(const QVariant& data)
{
    m_data = data;
}

//! Sets the data from editor and inform external delegates.

void CustomEditor::setDataIntern(const QVariant& data)
{
    setData(data);
    dataChanged(m_data);
}


MaterialPropertyEditor::MaterialPropertyEditor(QWidget* parent)
    : CustomEditor(parent)
    , m_textLabel(new QLabel)
    , m_pixmapLabel(new QLabel)
    , m_focusFilter(new LostFocusFilter(this))
{
    setMouseTracking(true);
    setAutoFillBackground(true);

    auto layout = new QHBoxLayout;
    layout->setMargin(2);
    layout->setSpacing(0);

    MaterialProperty defProperty; // to get label and pixmap of undefined material
    m_textLabel->setText(defProperty.getName());
    m_pixmapLabel->setPixmap(defProperty.getPixmap());

    auto button = new QToolButton;
    button->setSizePolicy(QSizePolicy(QSizePolicy::Fixed,
                                      QSizePolicy::Preferred));
    button->setText(QLatin1String("..."));
    layout->addWidget(m_pixmapLabel, Qt::AlignLeft);
    layout->addWidget(m_textLabel, Qt::AlignLeft);
    layout->addStretch(1);
    layout->addWidget(button);
    setFocusPolicy(Qt::StrongFocus);
    setAttribute(Qt::WA_InputMethodEnabled);
    connect(button, &QToolButton::clicked, this, &MaterialPropertyEditor::buttonClicked);

    setLayout(layout);
}

void MaterialPropertyEditor::setData(const QVariant& data)
{
    Q_ASSERT(data.canConvert<MaterialProperty>());
    CustomEditor::setData(data);

    MaterialProperty materialProperty = m_data.value<MaterialProperty>();
    m_textLabel->setText(materialProperty.getName());
    m_pixmapLabel->setPixmap(materialProperty.getPixmap());
}

void MaterialPropertyEditor::buttonClicked()
{
    // temporarily installing filter to prevent loss of focus caused by too insistent dialog
    installEventFilter(m_focusFilter);
    MaterialProperty materialProperty = m_data.value<MaterialProperty>();
    MaterialProperty mat = MaterialSvc::selectMaterialProperty(materialProperty);
    removeEventFilter(m_focusFilter);

    if(mat.isDefined() )
        setDataIntern(mat.getVariant());
}
