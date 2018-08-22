// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/ImportDataWidgets/CsvImportAssistant.cpp
//! @brief     Implements class CsvImportAssistant
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "CsvImportAssistant.h"
#include "mainwindow_constants.h"
#include "StyleUtils.h"
#include <QAction>
#include <QPushButton>
#include <QTableWidget>
#include <QSettings>
#include <QVBoxLayout>
#include <QFileDialog>
#include <QMessageBox>

namespace
{
const QSize default_dialog_size(600, 800);
}

CsvImportAssistant::CsvImportAssistant(QString dir, QString file, QWidget* parent)
    : QDialog(parent), m_dirName(dir), m_fileName(file)
{
    setWindowTitle("Data Importer");
    setMinimumSize(128, 128);
    resize(600, 800);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    auto layout = new QVBoxLayout;
    layout->setContentsMargins(0, 0, 0, 0);
    layout->addLayout(createLayout());

    setLayout(layout);

    StyleUtils::setResizable(this);

    if(!m_fileName.isEmpty())
        CsvImportAssistant::onReloadButton();
}



QBoxLayout* CsvImportAssistant::createLayout()
{
    auto result = new QVBoxLayout;
    auto preresult = new QHBoxLayout;

    auto importButton = new QPushButton("Import");
    connect(importButton, &QPushButton::clicked, this, &CsvImportAssistant::onImportButton);

    auto rejectButton = new QPushButton("Cancel");
    connect(rejectButton, &QPushButton::clicked, this, &CsvImportAssistant::onRejectButton);


    m_tableWidget = new QTableWidget();

    preresult->setMargin(10);
    //preresult->setSpacing(5);
    //preresult->addStretch(1);

    preresult->addWidget(rejectButton);
    preresult->addWidget(importButton);


    result->setMargin(10);
    //result->setSpacing(5);
    //result->addStretch(1);
    result->addWidget(m_tableWidget);
    //
    result->addLayout(CsvImportAssistant::createFileDetailsLayout());
    //

    result->addLayout(preresult);

    return result;
}

QBoxLayout* CsvImportAssistant::createFileDetailsLayout(){
    auto result = new QVBoxLayout;
    result->setMargin(10);
    //result->setSpacing(5);
    //result->addStretch(1);

    auto labelFilepath = new QLabel("File to import: ");
    m_filePathField = new QLineEdit(m_fileName,this);
    auto browseButton = new QPushButton("browse");
    connect(browseButton, &QPushButton::clicked, this, &CsvImportAssistant::onBrowseButton);
    auto lay1 = new QHBoxLayout;
    //lay1->setMargin(10);
    //lay1->setSpacing(5);
    //lay1->addStretch(1);
    lay1->addWidget(labelFilepath);
    lay1->addWidget(m_filePathField);
    lay1->addWidget(browseButton);

    result->addLayout(lay1);

    auto labelSeparator = new QLabel("Separator: ");
    m_separatorField = new QLineEdit(QString(guessSeparator()));
    m_separatorField->setMaxLength(1);
    auto lay2 = new QHBoxLayout;
    //lay2->setMargin(10);
    //lay2->setSpacing(5);
    //lay2->addStretch(1);
    lay2->addWidget(labelSeparator);
    lay2->addWidget(m_separatorField);
    result->addLayout(lay2);

    //    auto labelHeaderRow = new QLabel("Headers row (zero for no headers): ");
    //    m_headersRowSpinBox = new QSpinBox();
    //    m_headersRowSpinBox->setMinimum(0);
    //    m_headersRowSpinBox->setMaximum(0);
    //    m_headersRowSpinBox->setValue(0);
    //    auto lay3 = new QHBoxLayout;
    //    //lay3->setMargin(10);
    //    //lay3->setSpacing(5);
    //    //lay3->addStretch(1);
    //    lay3->addWidget(labelHeaderRow);
    //    lay3->addWidget(m_headersRowSpinBox);
    //    result->addLayout(lay3);

    auto labelFirstDataRow = new QLabel("First data row: ");
    m_firstDataRowSpinBox = new QSpinBox();
    m_firstDataRowSpinBox->setMinimum(1);
    m_firstDataRowSpinBox->setMaximum(1);
    m_firstDataRowSpinBox->setValue(1);
    auto lay4 = new QHBoxLayout;
    //lay4->setMargin(10);
    //lay4->setSpacing(5);
    //lay4->addStretch(1);
    lay4->addWidget(labelFirstDataRow);
    lay4->addWidget(m_firstDataRowSpinBox);
    result->addLayout(lay4);

    auto labelLastDataRow = new QLabel("Last data row (zero to read until last row found): ");
    m_lastDataRowSpinBox = new QSpinBox();
    m_lastDataRowSpinBox->setMinimum(0);
    m_lastDataRowSpinBox->setMaximum(0);
    m_lastDataRowSpinBox->setValue(0);
    auto lay5 = new QHBoxLayout;
    //lay5->setMargin(10);
    //lay5->setSpacing(5);
    //lay5->addStretch(1);
    lay5->addWidget(labelLastDataRow);
    lay5->addWidget(m_lastDataRowSpinBox);
    result->addLayout(lay5);


    auto lay6 = new QVBoxLayout;
    auto reloadButton = new QPushButton("Reload");
    connect(reloadButton, &QPushButton::clicked, this, &CsvImportAssistant::onReloadButton);
    //lay6->setMargin(10);
    lay6->addWidget(reloadButton);

    result->addLayout(lay1);
    result->addLayout(lay2);
    //result->addLayout(lay3);
    result->addLayout(lay4);
    result->addLayout(lay5);
    result->addLayout(lay6);

    return result;
}

void CsvImportAssistant::onBrowseButton()
{
    const QString filter_string = "Intensity File (*.txt *.dat *.ascii *.int *.gz *.tif *.tiff *.csv);;All files (*.*)";
    QString fileName = QFileDialog::getOpenFileName(nullptr, QStringLiteral("Open Intensity File"),
                                                    this->m_dirName, filter_string);
    if(fileName != nullptr){
        m_filePathField->setText(fileName);
        m_fileName = fileName;
        CsvImportAssistant::onReloadButton();
    }

}

void CsvImportAssistant::onReloadButton()
{
    std::ifstream f(filepath().toStdString());
    if(f.good()){
        generate_table();
    }else{
        QMessageBox msgBox;
        std::string message = "There was a problem opening the file \"" + filepath().toStdString() + "\"";
        message += "\n Check for any errors in the path and try again.";
        msgBox.setText(QString::fromStdString(message));
        msgBox.setIcon(msgBox.Critical);
        msgBox.exec();
    }
}

void CsvImportAssistant::onRejectButton(){
    reject();
}


void CsvImportAssistant::onImportButton()
{
    using namespace std;

    int nRows = m_tableWidget->rowCount();
    int nCols = m_tableWidget->columnCount();
    vector<vector<string>> A;
    vector<string> B;

    //save the values of the array
    for(int i = 0; i < nRows; i++){
        B.clear();
        for(int j = 0; j < nCols; j++){
            B.push_back( m_tableWidget->item(i,j) != nullptr ? m_tableWidget->item(i,j)->text().toStdString() : "");
        }
        A.push_back(B);
    }

    setFilepath(filepath()+"-ba-imported.txt");
    ofstream output_file(filepath().toStdString());
    for(int i = 0; i < nRows; i++){
        for(int j = 0; j < nCols - 1; j++){
            std::string a = A[unsigned(i)][unsigned(j)];
            output_file << a << " ";
        }
        std::string a = A[unsigned(i)][unsigned(nCols) - 1];
        output_file << a << '\n';
    }
    accept();
}


void CsvImportAssistant::generate_table()
{
    CSVFile* csvFile;
    try{
        csvFile = new CSVFile(filepath().toStdString(), separator(), headersLine());
    }
    catch(...){
        QMessageBox msgBox;
        std::string message = "There was a problem opening the file \"" + filepath().toStdString() + "\"";
        msgBox.setText(QString::fromStdString(message));
        msgBox.setIcon(msgBox.Critical);
        msgBox.exec();
        return;
    }

    m_tableWidget->clearContents();
    m_tableWidget->setColumnCount(int(csvFile->NumberOfColumns()));
    m_tableWidget->setRowCount(0);
    m_lastDataRowSpinBox->setMaximum(int(csvFile->NumberOfRows()));
    m_firstDataRowSpinBox->setMaximum(int(csvFile->NumberOfRows()));
    //m_headersRowSpinBox->setMaximum(csvFile->NumberOfRows());

    set_table_headers(csvFile);
    set_table_data(csvFile);
    remove_blanks();
    setRowNumbering();

    return;
}

void CsvImportAssistant::set_table_headers(CSVFile* csvFile){
    QStringList titulos;

    CSVRow headers = csvFile->get_headers();

    for(unsigned j = 0; j < headers.size(); j++){
        std::string header = headers[j].empty() ? std::string("Column ") + std::to_string(j+1) : headers[j];
        titulos << QString::fromStdString(header);
    }
    m_tableWidget->setHorizontalHeaderLabels(titulos);

    return;
}


void CsvImportAssistant::set_table_data(CSVFile* csvFile){

    unsigned firstDataLine = firstLine() - 1;
    unsigned lastDataLine = lastLine() == 0 ? unsigned(m_lastDataRowSpinBox->maximum()) : lastLine();


    for(unsigned i = firstDataLine; i < lastDataLine; i++){
        m_tableWidget->insertRow(m_tableWidget->rowCount());
        unsigned I = unsigned(m_tableWidget->rowCount()) - 1;
        for(unsigned j = 0; j < csvFile->NumberOfColumns(); j++){
            std::string aasdf = csvFile->operator [](i)[j];
            m_tableWidget->setItem(int(I),int(j),new QTableWidgetItem(QString::fromStdString(aasdf)));
        }
    }
}

void CsvImportAssistant::remove_blanks(){
    using namespace std;

    int nRows = m_tableWidget->rowCount();
    int nCols = m_tableWidget->columnCount();
    vector<vector<string>> A;
    vector<string> B;
    vector<int> blank_cols;

    //save the inices of blank cols
    for(int j = 0; j < nCols; j++){
        int i = 0;
        bool this_col_is_blank = cell_is_blank(i,j);
        while(this_col_is_blank && i < nRows  ){
            this_col_is_blank = cell_is_blank(i,j);
            i++;
        }
        if(i == nRows){
            blank_cols.push_back(j);
        }
    }

    //save the values of the array
    for(int i = 0; i < nRows; i++){
        B.clear();
        for(int j = 0; j < nCols; j++){
            string contents = m_tableWidget->item(i,j) != nullptr ? m_tableWidget->item(i,j)->text().toStdString() : "";
            B.push_back(contents);
        }
        //Skip last row if it is an empty line:
        if(i == nRows - 1)
            if(QString::fromStdString(std::accumulate(B.begin(), B.end(), std::string(""))).trimmed() == "")
                continue;

        A.push_back(B);
    }

    //correct the size of the table
    m_tableWidget->clearContents();
    m_tableWidget->setRowCount(0);
    m_tableWidget->setColumnCount(nCols-int(blank_cols.size()));
    nRows = int(A.size());

    //put values into a new table
    for(int i = 0; i < nRows; i++){
        m_tableWidget->insertRow(m_tableWidget->rowCount());
        int J = 0;
        for(int j = 0; j < nCols; j++){
            if( std::find(blank_cols.begin(), blank_cols.end(), j) == blank_cols.end()){
                std::string a = A[unsigned(i)][unsigned(j)];
                m_tableWidget->setItem(i,J,new QTableWidgetItem(QString::fromStdString(a)));
                J++;
            }
        }
    }
}

void CsvImportAssistant::setRowNumbering(){

    unsigned firstDataLine = firstLine();
    unsigned lastDataLine = lastLine() == 0 ? unsigned(m_lastDataRowSpinBox->maximum()) : lastLine();


    QStringList displayRowNumbers;
    for(unsigned i = firstDataLine; i <= lastDataLine; i++)
        displayRowNumbers << QString::number(i);

    m_tableWidget->setVerticalHeaderLabels(displayRowNumbers);
}


bool CsvImportAssistant::cell_is_blank(int iRow, int jCol){

    if ( m_tableWidget->item(iRow,jCol) == nullptr)
        return true;

    if ( m_tableWidget->item(iRow,jCol)->text() == nullptr)
        return true;

    if( m_tableWidget->item(iRow,jCol)->text().trimmed() == "")
        return true;

    return false;
}

QString CsvImportAssistant::filepath() const{
    return m_filePathField->text().trimmed();
}

void CsvImportAssistant::setFilepath(QString fpath){
    m_fileName = fpath;
    m_filePathField->setText(m_fileName);
}

char CsvImportAssistant::separator() const{
    char separator;
    QString tmpstr = m_separatorField->text();
    if(tmpstr.size() < 1){
        separator = guessSeparator();
        QMessageBox msgBox;
        msgBox.setText("There was a problem with the separator given.\n Replacing it by ' ' [space]");
        msgBox.setIcon(msgBox.Information);
        msgBox.exec();
        m_separatorField->setText(QString(QChar::fromLatin1(separator)));
    }
    else{
        separator = tmpstr.at(0).toLatin1();
    }
    return separator;
}

char CsvImportAssistant::guessSeparator() const{
    using namespace std;
    int frequencies[127] = {0};

    //The actual characters that may be realistically
    //used as separators are only a handfull...
    //And this list seems already exagerated.
    vector<char> preferredSeparators;
    preferredSeparators.push_back(' ');
    preferredSeparators.push_back(',');
    preferredSeparators.push_back(';');
    preferredSeparators.push_back('|');
    preferredSeparators.push_back(':');
    preferredSeparators.push_back('\t');
    preferredSeparators.push_back('/');
    preferredSeparators.push_back('\\');
    preferredSeparators.push_back('_');
    preferredSeparators.push_back('\'');
    preferredSeparators.push_back('\"');


    //count number of occurences of each char in the file:
    char c;
    std::ifstream is(m_fileName.toStdString());
    while (is.get(c))
      frequencies[int(c)]++;
    is.close();

    //set the guessed separator as the most frequent among the
    //preferred separators. -- Some unavoidable hieararchy is
    //present: characters with lower ascii code are preferred.
    char guessedSep = ' ';
    int freq = 0;
    for(char i = 0; i< 127 ; i++){
        if( std::find(preferredSeparators.begin(), preferredSeparators.end(), i) != preferredSeparators.end())
            if(frequencies[int(i)] > freq){
                freq = frequencies[int(i)];
                guessedSep = i;
            }
    }

    //We don't like tabs, as we cannot write them in the GUI.
    //The rest of the CsvImportAssistant and CsvReader should be already aware of this.
    if(guessedSep == '\t')
        guessedSep = ' ';

    return guessedSep;
}

unsigned CsvImportAssistant::headersLine() const{
    return 0;//m_headersRowSpinBox->value();
}

unsigned CsvImportAssistant::firstLine() const{
    return unsigned(m_firstDataRowSpinBox->value());
}

unsigned CsvImportAssistant::lastLine() const{
    return unsigned(m_lastDataRowSpinBox->value());
}
