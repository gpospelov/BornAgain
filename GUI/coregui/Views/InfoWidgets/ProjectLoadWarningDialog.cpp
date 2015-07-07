// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/InfoWidgets/ProjectLoadWarningDialog.cpp
//! @brief     Implements class ProjectLoadWarningDialog
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "ProjectLoadWarningDialog.h"
#include "DesignerHelper.h"
#include "WarningMessageService.h"
#include "MessageContainer.h"
#include "GUIMessage.h"
#include "SessionModel.h"
#include <QBoxLayout>
#include <QGridLayout>
#include <QPushButton>
#include <QLabel>
#include <QFrame>
#include <QTextEdit>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QHeaderView>

namespace {
const int top_panel_height = 80;
}

ProjectLoadWarningDialog::ProjectLoadWarningDialog(QWidget *parent,
                                                   const WarningMessageService *messageService)
    : QDialog(parent), m_messageService(messageService)
{
    setMinimumSize(256, 256);
    resize(520, 620);
    setWindowTitle("Problems encountered while loading project");
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    //setModal(true);

    QVBoxLayout *mainLayout = new QVBoxLayout;

    mainLayout->addWidget(createTopPanel());
    mainLayout->addWidget(createModelInfoPanel());
    mainLayout->addWidget(createExplanationPanel());
    mainLayout->addWidget(createDetailsPanel());

    QPushButton *button = new QPushButton("Close", this);
    button->setAutoDefault(false);
    connect(button, SIGNAL(clicked()), this, SLOT(close()));

    QHBoxLayout *buttonLayout = new QHBoxLayout;
    buttonLayout->addStretch(1);
    buttonLayout->setContentsMargins(0, 8, 5, 0);
    buttonLayout->addWidget(button);

    mainLayout->addLayout(buttonLayout);

    setLayout(mainLayout);

    setAttribute(Qt::WA_DeleteOnClose, true);
}

//! Top panel with warning icon and the header
QWidget *ProjectLoadWarningDialog::createTopPanel()
{
    QWidget *result = new QWidget(this);
    QHBoxLayout *layout = new QHBoxLayout;

    // ---
    QLabel *warningLabel = new QLabel;
    warningLabel->setPixmap(QPixmap(":/images/warning_64x64.png"));

    QWidget *warningWidget = new QWidget;
    warningWidget->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    warningWidget->resize(top_panel_height,top_panel_height);
    QHBoxLayout *warningWidgetLayout = new QHBoxLayout;
    warningWidgetLayout->addWidget(warningLabel);
    warningWidget->setLayout(warningWidgetLayout);

    QFont titleFont;
    titleFont.setPointSize(DesignerHelper::getSectionFontSize());
    titleFont.setBold(true);

    QLabel *messageLabel = new QLabel();
    messageLabel->setFont(titleFont);
    messageLabel->setText("Some parts of the project were not loaded correctly.");
    messageLabel->setWordWrap(true);

    layout->addWidget(warningWidget);
    layout->addWidget(messageLabel);

    result->setLayout(layout);
    return result;
}

//! Info panel with summary over warnings in different models
QWidget *ProjectLoadWarningDialog::createModelInfoPanel()
{
    QWidget *result = new QWidget(this);
    QHBoxLayout *layout = new QHBoxLayout;

    QFrame* line = new QFrame();
    line->setFrameShape(QFrame::VLine);
    line->setFrameShadow(QFrame::Sunken);


    QGridLayout *gridLayout = new QGridLayout;

    QStringList names = getModelNames();
    for(int irow=0; irow<names.size(); ++irow) {
        gridLayout->addWidget(new QLabel(names.at(irow)), irow, 0);
        gridLayout->addWidget(createModelStatusLabel(names.at(irow)), irow, 1);
    }

    layout->addWidget(line);
    layout->addLayout(gridLayout);
    layout->addWidget(new QWidget);

    result->setLayout(layout);
    return result;
}

//! Info panel with explanations what had happened and what to do
QWidget *ProjectLoadWarningDialog::createExplanationPanel()
{
    QWidget *result = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout;

    QFont titleFont;
    titleFont.setPointSize(DesignerHelper::getSectionFontSize());
    titleFont.setBold(true);

    QLabel *whyLabel = new QLabel;
    whyLabel->setFont(titleFont);
    whyLabel->setText("Why did this happen to me?");

    QLabel *explanationLabel = new QLabel;
    QString explanationText(
        "Given project was created using BornAgain version 1.0 "
        "which is different from version 2.0 you are currently using."
        "At the moment we provide only limited support for import from older versions. "
                );
    explanationLabel->setText(explanationText);
    explanationLabel->setWordWrap(true);

    QLabel *whatLabel = new QLabel;
    whatLabel->setFont(titleFont);
    whatLabel->setText("What to do?");

    QLabel *adviceLabel = new QLabel;
    QString adviceText(
        "Check parameters of your items and re-enter uninitialized values. "
        "Use detailed log below to get a hint what went wrong."
        "After that, save you project and work as normal."
                );
    adviceLabel->setText(adviceText);
    adviceLabel->setWordWrap(true);

    layout->addWidget(whyLabel);
    layout->addWidget(explanationLabel);
    layout->addWidget(whatLabel);
    layout->addWidget(adviceLabel);

    result->setLayout(layout);
    return result;
}

//! Info panel with table widget containing error messages
QWidget *ProjectLoadWarningDialog::createDetailsPanel()
{
    QWidget *result = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout;

    QFont titleFont;
    titleFont.setPointSize(DesignerHelper::getSectionFontSize());
    titleFont.setBold(true);

    QLabel *detailsLabel = new QLabel;
    detailsLabel->setFont(titleFont);
    detailsLabel->setText("Details");

    layout->addWidget(detailsLabel);
    layout->addWidget(createTableWidget());

    result->setLayout(layout);
    return result;
}

//! Creates QTableWidget and fills it with error messages
QTableWidget *ProjectLoadWarningDialog::createTableWidget()
{
    Q_ASSERT(m_messageService);
    QTableWidget *result = new QTableWidget;

    result->setRowCount(getNumberOfRows());
    result->setColumnCount(getTableHeaderLabels().size());
    result->setHorizontalHeaderLabels(getTableHeaderLabels());
    result->verticalHeader()->setVisible(false);
    result->horizontalHeader()->setStretchLastSection(true);

    int rowCount(0);
    for (WarningMessageService::container_t::const_iterator it = m_messageService->begin();
         it != m_messageService->end(); ++it) {
        const MessageContainer *messageContainer = it.value();
        for (MessageContainer::const_iterator it = messageContainer->begin();
             it != messageContainer->end(); ++it) {
            const GUIMessage *guiMessage = (*it);
            // item->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
            result->setItem(rowCount, 0, new QTableWidgetItem(guiMessage->getSenderName()));
            result->setItem(rowCount, 1, new QTableWidgetItem(guiMessage->getMessageType()));
            result->setItem(rowCount, 2, new QTableWidgetItem(guiMessage->getMessageDescription()));
            ++rowCount;
        }
    }

    return result;
}

//! Returns number of rows in table with error messages, each row represents an error message
int ProjectLoadWarningDialog::getNumberOfRows() const
{
    Q_ASSERT(m_messageService);
    int result(0);
    for(WarningMessageService::container_t::const_iterator it=m_messageService->begin(); it!=m_messageService->end(); ++it) {
        result += it.value()->size();
    }
    return result;
}

//! Returns labels for table header
QStringList ProjectLoadWarningDialog::getTableHeaderLabels() const
{
    QStringList result;
    result << "Sender" << "Warning" << "Description";
    return result;
}


//! Returns list of model names to form summary
QStringList ProjectLoadWarningDialog::getModelNames() const
{
    QStringList names;
    names << SessionXML::MaterialModelTag << SessionXML::InstrumentModelTag
          << SessionXML::SampleModelTag << SessionXML::JobModelTag;
    return names;
}

//! create status label "OK"/"WARNING" depending on presence of warning messages in the container
QLabel *ProjectLoadWarningDialog::createModelStatusLabel(const QString &model_name) const
{
    QLabel *result = new QLabel("OK");
    for (WarningMessageService::container_t::const_iterator it = m_messageService->begin();
         it != m_messageService->end(); ++it) {

        const MessageContainer *messageContainer = it.value();
        if (model_name == it.key()->objectName() && messageContainer->size()) {
            result->setText("WARNING");
        }
    }
    return result;
}
