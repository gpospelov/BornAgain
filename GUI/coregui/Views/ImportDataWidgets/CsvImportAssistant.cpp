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

#include "DataFormatUtils.cpp"
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
#include <QMenu>

namespace
{
const QSize default_dialog_size(300, 400);
}

CsvImportAssistant::CsvImportAssistant(QString& dir, QString& file, QWidget* parent):
    QDialog(parent),
    m_dirName(dir),
    m_fileName(file),
    m_lastDataRow(0),
    m_intensityCol(0),
    m_coordinateCol(0),
    m_singleCol(0),
    m_tableWidget(nullptr),
    m_separatorField(nullptr),
    m_firstDataRowSpinBox(nullptr),
    m_singleDataColSpinBox(nullptr),
    m_importButton(nullptr)
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
        CsvImportAssistant::Reload();
}



QBoxLayout* CsvImportAssistant::createLayout()
{
    auto result = new QVBoxLayout;
    auto preresult = new QHBoxLayout;

    m_importButton = new QPushButton("Import");
    m_importButton->setDefault(true);
    connect(m_importButton, &QPushButton::clicked, this, &CsvImportAssistant::onImportButton);

    auto rejectButton = new QPushButton("Cancel");
    connect(rejectButton, &QPushButton::clicked, this, &CsvImportAssistant::onRejectButton);


    m_tableWidget = new QTableWidget();

    preresult->setMargin(10);

    preresult->addWidget(rejectButton);
    preresult->addWidget(m_importButton);


    result->setMargin(10);
    result->addWidget(new QLabel("Right click on the table or use the controls below to modify what will be imported"));
    result->addWidget(m_tableWidget);
    result->addLayout(CsvImportAssistant::createFileDetailsLayout());

    result->addLayout(preresult);

    m_tableWidget->setContextMenuPolicy(Qt::CustomContextMenu);
    m_tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    connect(m_tableWidget, &QTableWidget::cellClicked, this, &CsvImportAssistant::OnColumnClicked);
    connect(m_tableWidget, &QTableWidget::customContextMenuRequested, this, &CsvImportAssistant::onColumnRightClick);
    return result;
}

QBoxLayout* CsvImportAssistant::createFileDetailsLayout(){
    auto result = new QHBoxLayout;
    result->setMargin(10);

    auto labelSeparator = new QLabel("Separator: ");
    m_separatorField = new QLineEdit(QString(guessSeparator()));
    m_separatorField->setMaxLength(1);
    m_separatorField->setMaximumWidth(50);
    auto lay2 = new QVBoxLayout;
    lay2->addWidget(labelSeparator);
    lay2->addWidget(m_separatorField);
    //result->addLayout(lay2);
    connect(m_separatorField, &QLineEdit::editingFinished, this, &CsvImportAssistant::Reload);


    auto lay3 = new QVBoxLayout;
    auto labelFirstDataRow = new QLabel("First data row: ");
    m_firstDataRowSpinBox = new QSpinBox();
    m_firstDataRowSpinBox->setMinimum(1);
    m_firstDataRowSpinBox->setMaximum(1);
    m_firstDataRowSpinBox->setValue(1);
    m_firstDataRowSpinBox->setMaximumWidth(50);
    lay3->addWidget(labelFirstDataRow);
    lay3->addWidget(m_firstDataRowSpinBox);

    connect(m_firstDataRowSpinBox, static_cast<void(QSpinBox::*)(int)>(&QSpinBox::valueChanged),
        [=](int i){ Reload(); });

    auto lay4 = new QVBoxLayout;
    auto labelSingleColImport = new QLabel("Import Single Column (zero to import all): ");
    m_singleDataColSpinBox = new QSpinBox();
    m_singleDataColSpinBox->setMinimum(0);
    m_singleDataColSpinBox->setMaximum(0);
    m_singleDataColSpinBox->setValue(0);
    m_singleDataColSpinBox->setMaximumWidth(50);
    lay4->addWidget(labelSingleColImport);
    lay4->addWidget(m_singleDataColSpinBox);
    connect(m_singleDataColSpinBox, static_cast<void(QSpinBox::*)(int)>(&QSpinBox::valueChanged),
        [=](int i){ m_singleCol = i; Reload(); });



    result->addLayout(lay2);
    result->addSpacing(20);
    result->addLayout(lay3);
    result->addSpacing(20);
    result->addLayout(lay4);

    return result;
}

void CsvImportAssistant::Reload()
{
    ifstream f(m_fileName.toStdString());
    if(f.good()){
        generate_table();
    }else{
        QMessageBox msgBox;
        string message = "There was a problem opening the file \"" + m_fileName.toStdString() + "\"";
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
    try {
        auto data = getData();
        accept();
    } catch(exception& e){
        QString message = QString("Unable to import, check that the table contains only numerical values");
        QMessageBox::warning(nullptr, "Wrong data format", message);
    }
}


unique_ptr<OutputData<double>> CsvImportAssistant::getData()
{
    int nTableRows = m_tableWidget->rowCount();
    int nTableCols = m_tableWidget->columnCount();
    vector<vector<string>> StringVectorVector;
    vector<string> StringVector;

    //save the values of the array
    size_t nDataCols = 0;
    size_t nDataRows = 0;
    for(int i = 0; i < nTableRows; i++){
        StringVector.clear();
        nDataCols = 0;
        for(int j = 0; j < nTableCols; j++){
            auto tableElement = m_tableWidget->item(i,j);
            if(tableElement != nullptr){
                StringVector.push_back(tableElement->text().toStdString());
                nDataCols++;
            }
        }
        StringVectorVector.push_back(StringVector);
        nDataRows++;
    }

    unique_ptr<OutputData<double>> result;
    result = std::make_unique<OutputData<double>>();

    if( (nDataCols < 2) || (nDataRows < 2) ){
        size_t nElem = max(nDataCols,nDataRows);
        result->addAxis("intensity", nElem, 0.0, double(nElem));
        vector<unsigned> axes_indices(1);
        unsigned item = 0;
        for(unsigned row=0; row<nDataRows; row++) {
            for(unsigned col=0; col<nDataCols; col++) {
                axes_indices[0] = item;
                size_t global_index = result->toGlobalIndex(axes_indices);
                string string_to_parse;
                vector<double> parsed_doubles;
                string_to_parse = StringVectorVector[row][col];
                parsed_doubles = DataFormatUtils::parse_doubles(string_to_parse);
                (*result)[global_index] = parsed_doubles[0];
                item++;
            }
        }
    }
    else if(m_coordinateName != ""){
        //Fill intensity values and coordinate values:
        int intensityCol = 1;
        int coordinateCol = 0;
        vector<double> coordValues;
        vector<double> intensityValues;
        for(unsigned row=0; row < nDataRows; row++) {
            string string_to_parse;
            vector<double> parsed_doubles;

            string_to_parse = StringVectorVector[row][coordinateCol];
            parsed_doubles = DataFormatUtils::parse_doubles(string_to_parse);
            coordValues.push_back(parsed_doubles[0]);

            string_to_parse = StringVectorVector[row][intensityCol];
            parsed_doubles = DataFormatUtils::parse_doubles(string_to_parse);
            intensityValues.push_back(parsed_doubles[0]);
        }
        auto axisName = m_coordinateName.toStdString();
        PointwiseAxis coordAxis(axisName, coordValues);
        result->addAxis(coordAxis);

        for(unsigned i = 0; i < intensityValues.size(); i++)
            (*result)[i] = intensityValues[i];
    }
    else{
        result->addAxis("x", nDataCols, 0.0, double(nDataCols));
        result->addAxis("y", nDataRows, 0.0, double(nDataRows));
        vector<unsigned> axes_indices(2);
        for(unsigned row=0; row<nDataRows; row++) {
            for(unsigned col=0; col<nDataCols; col++) {
                axes_indices[0] = col;
                axes_indices[1] = static_cast<unsigned>(nDataRows) - 1 - row;
                size_t global_index = result->toGlobalIndex(axes_indices);
                string string_to_parse;
                vector<double> parsed_doubles;
                string_to_parse = StringVectorVector[row][col];
                parsed_doubles = DataFormatUtils::parse_doubles(string_to_parse);
                (*result)[global_index] = parsed_doubles[0];
            }
        }
    }
    return result;
}


void CsvImportAssistant::generate_table() {
    unique_ptr<CSVFile> csvFile;
    try {
        csvFile = std::make_unique<CSVFile>(m_fileName.toStdString(), separator());
    }
    catch (...) {
        QMessageBox msgBox;
        string message = "There was a problem opening the file \"" + m_fileName.toStdString() + "\"";
        msgBox.setText(QString::fromStdString(message));
        msgBox.setIcon(msgBox.Critical);
        msgBox.exec();
        return;
    }
    m_firstDataRowSpinBox->setMaximum(int(csvFile->NumberOfRows()));
    m_singleDataColSpinBox->setMaximum(int(csvFile->NumberOfColumns()));
    m_lastDataRow = unsigned(int(csvFile->NumberOfRows()));
    vector<vector<string>> csvArray = csvFile->asArray();

    if (m_lastDataRow < 1) {
        m_importButton->setDisabled(true);
        return;
    }


    //Remove empty lines at the end automatically:
    while(QString::fromStdString(accumulate(csvArray[m_lastDataRow-1].begin(), csvArray[m_lastDataRow-1].end(), string(""))).trimmed() == ""){
        m_lastDataRow--;
        m_firstDataRowSpinBox->setMaximum(int(m_lastDataRow));
        if (m_lastDataRow < 1) {
            m_importButton->setDisabled(true);
            return;
        }
    }

    vector<vector<string>> dataArray( csvArray.begin() + firstLine()-1, csvArray.begin() + m_lastDataRow );

    removeBlankColumns(dataArray);

    extractDesiredColumns(dataArray);

    set_table_data(dataArray);

    setRowNumbering();
}

void CsvImportAssistant::set_table_data(vector<vector<string>> dataArray){

    if(dataArray.empty()){
        m_tableWidget->clearContents();
        m_tableWidget->setRowCount(0);
        return;
    }

    size_t nRows = dataArray.size();
    size_t nCols = dataArray[0].size();
    m_tableWidget->clearContents();
    m_tableWidget->setColumnCount(int(nCols));
    m_tableWidget->setRowCount(0);

    for(unsigned i = 0; i < nRows ; i++){
        m_tableWidget->insertRow(m_tableWidget->rowCount());
        unsigned I = unsigned(m_tableWidget->rowCount()) - 1;
        for(unsigned j = 0; j < dataArray[i].size(); j++){
            m_tableWidget->setItem(int(I),int(j),new QTableWidgetItem(QString::fromStdString(dataArray[i][j])));
        }
    }
}


void CsvImportAssistant::removeBlankColumns(vector<vector<string> > &dataArray){

    if(dataArray.empty())
        return;

    vector<vector<string>> buffer2d;
    vector<string> buffer1d;
    vector<int> to_be_removed;

    size_t nRows = dataArray.size();
    size_t nCols = dataArray[0].size();

    if(!hasEqualLengthLines(dataArray)){
        throw Exceptions::NotImplementedException("All inner vectors should have the same length already.");
    }

    //traverse the array columnwise -- this may be inneficient.
    for(size_t j = 0; j < nCols; j++){
        buffer1d.clear();
        for(size_t i = 0; i < nRows; i++){
            buffer1d.push_back(dataArray[i][j]);
        }
        if(QString::fromStdString(accumulate(buffer1d.begin(), buffer1d.end(), string(""))).trimmed() == "")
            continue;

        buffer2d.push_back(buffer1d);
    }

    if(buffer2d.empty()){
        dataArray.clear();
        return;
    }

    //now buffer2d has the original array, without blank columns, transposed.
    nCols = buffer2d.size();
    nRows = buffer2d[0].size();

    //Save the modified array --i.e. transpose buffer2d
    dataArray.clear();
    for(size_t i = 0; i < nRows; i++){
        buffer1d.clear();
        for(size_t j = 0; j < nCols; j++){
            buffer1d.push_back(buffer2d[j][i]);
        }
        dataArray.push_back(buffer1d);
    }
}

void CsvImportAssistant::setRowNumbering(){

    unsigned firstDataLine = firstLine();
    unsigned lastDataLine = lastLine();


    QStringList displayRowNumbers;
    for(unsigned i = firstDataLine; i <= lastDataLine; i++)
        displayRowNumbers << QString::number(i);

    m_tableWidget->setVerticalHeaderLabels(displayRowNumbers);
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
    ifstream is(m_fileName.toStdString());
    while (is.get(c)){
        if(unsigned(c) < 127)
            frequencies[unsigned(c)]++;
    }
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

void CsvImportAssistant::setHeaders(){
   //Reset header labels
   QStringList headers;

   for(int j = 0; j < m_tableWidget->columnCount(); j++)
       headers.append(QString::number(j + 1));

   m_tableWidget->setHorizontalHeaderLabels(headers);
}

unsigned CsvImportAssistant::firstLine() const{
    return unsigned(m_firstDataRowSpinBox->value());
}

unsigned CsvImportAssistant::lastLine() const{
    return m_lastDataRow;
}

void CsvImportAssistant::OnColumnClicked(int row, int column)
{
    if(column < -1) return;
    if(row < -1) return;

    //m_tableWidget->clearSelection();
    //m_tableWidget->selectionModel()->select
//    QModelIndex left   = m_tableWidget->model()->index(row, 0);
 //   QModelIndex right  = m_tableWidget->model()->index(row, m_tableWidget->columnCount() - 1);
  //  QModelIndex top    = m_tableWidget->model()->index(0, column);
   // QModelIndex bottom = m_tableWidget->model()->index(m_tableWidget->rowCount() - 1, column);

//    QItemSelection selection(left, right);
//    selection.merge(QItemSelection(top, bottom), QItemSelectionModel::Select);
//    m_tableWidget->selectionModel()->select(selection, QItemSelectionModel::Select);
}

void CsvImportAssistant::onColumnRightClick(const QPoint position)
{
    auto item = m_tableWidget->itemAt(position);
    if(!item) return;
    auto row = item->row();
    auto col = item->column();

    if(row*col < 0) return;

    OnColumnClicked(row,col);
    QMenu menu;


    //Use single column
    QAction onlyThisColumn("Use single column as intensity bins",nullptr);
    onlyThisColumn.setDisabled(m_coordinateCol+m_intensityCol > 0 || m_singleCol > 0);
    menu.addAction(&onlyThisColumn);
    connect(&onlyThisColumn,&QAction::triggered,
            [&](){
            m_intensityCol = 0;
            m_coordinateCol = 0;
            m_coordinateName = "";
            m_singleCol = unsigned(col+1);
            m_singleDataColSpinBox->setValue(col+1);
            m_tableWidget->setHorizontalHeaderItem(0, new QTableWidgetItem( relevantHeaders[_intensity_]) );
        }
    );

    //Action "select from this row"
    QAction selectFromThisRowOn("Ignore preceding rows",nullptr);
    menu.addAction(&selectFromThisRowOn);
    connect(&selectFromThisRowOn,&QAction::triggered,
            [&](){m_firstDataRowSpinBox->setValue(m_tableWidget->verticalHeaderItem(row)->text().toInt());}
    );


    menu.addSeparator();


    //Set column as "Intensity"
    QAction setAsIntensity("Set as " + relevantHeaders[_intensity_] + " column", nullptr);
    setAsIntensity.setDisabled(m_intensityCol>0 || m_singleCol > 0);
    menu.addAction(&setAsIntensity);
    connect(&setAsIntensity,&QAction::triggered,
    [&]() {
        m_tableWidget->setHorizontalHeaderItem(col, new QTableWidgetItem(relevantHeaders[_intensity_]));
        m_intensityCol = unsigned(col+1);
        if (m_coordinateCol == m_intensityCol) {
            m_coordinateCol = 0;
            return;
        }
        if (m_coordinateCol > 0){
            Reload();
            m_tableWidget->setHorizontalHeaderItem(0, new QTableWidgetItem(m_coordinateName));
            m_tableWidget->setHorizontalHeaderItem(1, new QTableWidgetItem(relevantHeaders[_intensity_]));
        }
    }
    );

    QMenu *coordMenu = menu.addMenu("Set as coordinate column");
    coordMenu->setDisabled(m_coordinateCol>0 || m_singleCol > 0);


    //Set column as "Theta"
    QAction setAsTheta("Set as " + relevantHeaders[_theta_],nullptr);
    coordMenu->addAction(&setAsTheta);
    connect(&setAsTheta,&QAction::triggered,
    [&](){
        m_tableWidget->setHorizontalHeaderItem( col, new QTableWidgetItem( relevantHeaders[_theta_]) );
        m_coordinateCol = unsigned(col+1);
        m_coordinateName = m_tableWidget->horizontalHeaderItem(col)->text();
        if(m_coordinateCol == m_intensityCol){
            m_intensityCol=0;
            return;
        }
        if(m_intensityCol > 0){
            Reload();
            m_tableWidget->setHorizontalHeaderItem( 0, new QTableWidgetItem( relevantHeaders[_theta_]) );
            m_tableWidget->setHorizontalHeaderItem( 1, new QTableWidgetItem( relevantHeaders[_intensity_]) );
        }
    }
    );


    //Set column as "2Theta"
    QAction setAs2Theta("Set as " + relevantHeaders[_2theta_] + " column",nullptr);
    coordMenu->addAction(&setAs2Theta);
    connect(&setAs2Theta,&QAction::triggered,
    [&](){
        m_tableWidget->setHorizontalHeaderItem( col, new QTableWidgetItem( relevantHeaders[_2theta_]) );
        m_coordinateCol = unsigned(col+1);
        m_coordinateName = m_tableWidget->horizontalHeaderItem(col)->text();
        if(m_coordinateCol == m_intensityCol){
            m_intensityCol=0;
            return;
        }
        if(m_intensityCol > 0){
            Reload();
            m_tableWidget->setHorizontalHeaderItem( 0, new QTableWidgetItem( relevantHeaders[_2theta_]) );
            m_tableWidget->setHorizontalHeaderItem( 1, new QTableWidgetItem( relevantHeaders[_intensity_]) );
        }
    }
    );


    //Set column as "qvector"
    QAction setAsQvector("Set as " + relevantHeaders[_q_] + " column",nullptr);
    coordMenu->addAction(&setAsQvector);
    connect(&setAsQvector,&QAction::triggered,
    [&](){
        m_tableWidget->setHorizontalHeaderItem( col, new QTableWidgetItem( relevantHeaders[_q_]) );
        m_coordinateCol = unsigned(col+1);
        m_coordinateName = m_tableWidget->horizontalHeaderItem(col)->text();
        if(m_coordinateCol == m_intensityCol){
            m_intensityCol=0;
            return;
        }
        if(m_intensityCol > 0){
            Reload();
            m_tableWidget->setHorizontalHeaderItem( 0, new QTableWidgetItem( relevantHeaders[_q_]) );
            m_tableWidget->setHorizontalHeaderItem( 1, new QTableWidgetItem( relevantHeaders[_intensity_]) );
        }
    }
    );



    menu.addSeparator();

    //Action "reset"
    QAction reset("reset",nullptr);
    menu.addAction(&reset);
    connect(&reset,&QAction::triggered,
            [&](){
                m_intensityCol = 0;
                m_coordinateCol = 0;
                m_coordinateName = "";
                m_singleCol = 0;
                m_firstDataRowSpinBox->setValue(0);
                m_singleDataColSpinBox->setValue(0);
                setHeaders();
                Reload();
            }
    );

    menu.exec(m_tableWidget->mapToGlobal(position));
}


bool CsvImportAssistant::hasEqualLengthLines(vector<vector<string>> &dataArray){
   auto tf =  all_of( begin(dataArray), end(dataArray), [dataArray](const vector<string>& x) {
       return x.size() == dataArray.front().size();
   });
   return tf;
}

void CsvImportAssistant::extractDesiredColumns(vector<vector<string>> &dataArray) {

    if (dataArray.empty()) {
        m_tableWidget->clearContents();
        m_tableWidget->setRowCount(0);
        return;
    }

    if ((m_coordinateCol * m_intensityCol < 1) && (m_singleCol < 1))
        return;

    vector<string> buffer1d;
    vector<vector<string>> buffer2d;
    auto nRows = dataArray.size();
    auto nCols = dataArray[0].size();

    if (m_singleCol > 0) {
        for (unsigned i = 0; i < nRows; i++) {
            buffer1d.clear();
            for (unsigned j = 0; j < nCols; j++) {
                if (j + 1 == m_singleCol)
                    buffer1d.push_back(dataArray[i][j]);
            }
            buffer2d.push_back(buffer1d);
        }
    }
    else {
        for (unsigned i = 0; i < nRows; i++) {
            buffer1d.clear();
            //No matter what, we want coordinate column first
            for (unsigned j = 0; j < nCols; j++) {
                if (j + 1 == m_coordinateCol)
                    buffer1d.push_back(dataArray[i][j]);
            }
            //Intensity columns comes next
            for (unsigned j = 0; j < nCols; j++) {
                if (j + 1 == m_intensityCol)
                    buffer1d.push_back(dataArray[i][j]);
            }
            buffer2d.push_back(buffer1d);
        }
    }

    dataArray.clear();
    swap(buffer2d,dataArray);
}
