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
#include <QPushButton>
#include <QTableWidget>
#include <QSettings>
#include <QVBoxLayout>
#include <QFileDialog>
#include <QMessageBox>
#include <QMenu>
#include <QFormLayout>

namespace
{
const QSize default_dialog_size(300, 400);
}

CsvImportAssistant::CsvImportAssistant(QString& file, QWidget* parent):
    QDialog(parent),
    m_fileName(file),
    m_lastDataRow(0),
    m_intensityCol(0),
    m_coordinateCol(0),
    m_singleCol(0),
    m_tableWidget(nullptr),
    m_separatorField(nullptr),
    m_firstDataRowSpinBox(nullptr),
    m_singleDataColSpinBox(nullptr),
    m_importButton(nullptr),
    m_csvFile(nullptr),
    m_columnTypeSelector(nullptr),
    m_setAsTheta(new QAction("Set as " + relevantHeaders[_theta_],nullptr)),
    m_setAs2Theta(new QAction("Set as " + relevantHeaders[_2theta_],nullptr)),
    m_setAsQ(new QAction("Set as " + relevantHeaders[_q_],nullptr)),
    m_setAsIntensity(new QAction("Set as " + relevantHeaders[_intensity_],nullptr)),
    m_setAsIntensityBins(new QAction("Use single column as intensity bins",nullptr))
{
    setWindowTitle("Data Importer");
    setMinimumSize(default_dialog_size);
    resize(400, 400);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    StyleUtils::setResizable(this);
    setLayout(createLayout());

    try {
        if(!m_fileName.isEmpty())
            m_csvFile = std::make_unique<CSVFile>(m_fileName.toStdString(), separator());
    }
    catch (...) {
        showErrorMessage("There was a problem opening the file \"" + m_fileName.toStdString() + "\"");
        return;
    }


    Reload();

}

QBoxLayout* CsvImportAssistant::createLayout()
{
    //table Widget
    m_tableWidget = new QTableWidget();
    m_tableWidget->setContextMenuPolicy(Qt::CustomContextMenu);
    m_tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    connect(m_tableWidget, &QTableWidget::cellClicked, this, &CsvImportAssistant::OnColumnClicked);
    connect(m_tableWidget, &QTableWidget::customContextMenuRequested, this, &CsvImportAssistant::onColumnRightClick);

    //Import button
    m_importButton = new QPushButton("Import");
    m_importButton->setDefault(true);
    connect(m_importButton, &QPushButton::clicked, this, &CsvImportAssistant::onImportButton);

    //Reject button
    auto rejectButton = new QPushButton("Cancel");
    connect(rejectButton, &QPushButton::clicked, this, &CsvImportAssistant::onRejectButton);

    //Separator field
    m_separatorField = new QLineEdit(QString(""));
    m_separatorField->setMaxLength(1);
    m_separatorField->setMaximumWidth(50);
    connect(m_separatorField, &QLineEdit::editingFinished, this, &CsvImportAssistant::reloadCsvFile);

    //First Row SpinBox
    m_firstDataRowSpinBox = new QSpinBox();
    m_firstDataRowSpinBox->setMinimum(1);
    m_firstDataRowSpinBox->setMaximum(1);
    m_firstDataRowSpinBox->setValue(1);
    m_firstDataRowSpinBox->setMaximumWidth(50);
    connect(m_firstDataRowSpinBox, static_cast<void(QSpinBox::*)(int)>(&QSpinBox::valueChanged),[this](){ Reload(); });

    //Single Column spinBox
    m_singleDataColSpinBox = new QSpinBox();
    m_singleDataColSpinBox->setMinimum(0);
    m_singleDataColSpinBox->setMaximum(0);
    m_singleDataColSpinBox->setValue(0);
    m_singleDataColSpinBox->setMaximumWidth(50);
    connect(m_singleDataColSpinBox, static_cast<void(QSpinBox::*)(int)>(&QSpinBox::valueChanged), [this](int i){ setColumnAsBinValues(i);});


    //Column type selector
    m_columnTypeSelector = new QComboBox();
    m_columnTypeSelector->addAction(m_setAsTheta);
    m_columnTypeSelector->addAction(m_setAs2Theta);
    m_columnTypeSelector->addAction(m_setAsQ);
    m_columnTypeSelector->addAction(m_setAsIntensity);
    m_columnTypeSelector->addAction(m_setAsIntensityBins);
    ///m_columnTypeSelector->setDisabled(m_tableWidget->selectedRanges().front().leftColumn());


    auto layout = new QVBoxLayout;
    layout->setContentsMargins(0, 0, 0, 0);

    //place table Widget
    auto tableLayout = new QVBoxLayout;
    tableLayout->setMargin(10);
    tableLayout->addWidget(new QLabel("Right click on the table or use the controls below to modify what will be imported"));
    //tableLayout->addWidget(m_columnTypeSelector);
    tableLayout->addWidget(m_tableWidget);

    //place separator_field, single_column_spinbox and first_row:
    auto controlsLayout = new QFormLayout;
    controlsLayout->addRow(tr("&Separator:"), m_separatorField);
    controlsLayout->addRow(tr("&Column:"), m_singleDataColSpinBox);
    controlsLayout->addRow(tr("&From row:"),m_firstDataRowSpinBox);

    //buttons layout
    auto buttonsLayout = new QHBoxLayout;
    buttonsLayout->addWidget(m_importButton);
    buttonsLayout->addWidget(rejectButton);

    //place controls and import/reject buttons
    auto controlsAndButtonsGrid = new QGridLayout;
    controlsAndButtonsGrid->setMargin(10);
    controlsAndButtonsGrid->addItem(new QSpacerItem(10000,1),1,1,2,1);
    controlsAndButtonsGrid->addLayout(controlsLayout, 1, 2, 1, 1, Qt::AlignRight);
    controlsAndButtonsGrid->addLayout(buttonsLayout, 2, 2, 1, 1, Qt::AlignLeft);

    //build all the layout
    layout->addLayout(tableLayout);
    layout->addLayout(controlsAndButtonsGrid);

    return layout;
}

void CsvImportAssistant::Reload()
{

    std::ifstream f(m_fileName.toStdString());
    if(f.good()){
        generate_table();
    }else{
        QMessageBox msgBox;
        std::string message = "There was a problem opening the file \"" + m_fileName.toStdString() + "\"";
        message += "\n Check for any errors in the path and try again.";
        msgBox.setText(QString::fromStdString(message));
        msgBox.setIcon(msgBox.Critical);
        msgBox.exec();
    }
}

void CsvImportAssistant::reloadCsvFile(){
    reset();
    try {
        if(!m_fileName.isEmpty())
            m_csvFile = std::make_unique<CSVFile>(m_fileName.toStdString(), separator());
    }
    catch (...) {
        showErrorMessage("There was a problem opening the file \"" + m_fileName.toStdString() + "\"");
        return;
    }
    Reload();
}

void CsvImportAssistant::onRejectButton(){
    reject();
}


void CsvImportAssistant::onImportButton()
{
    try {
        auto data = getData();
        accept();
    } catch(std::exception& e){
        QString message = QString("Unable to import, the following exception was thrown:\n") + QString::fromStdString(e.what());
        QMessageBox::warning(nullptr, "Wrong data format", message);
    }
}


std::unique_ptr<OutputData<double>> CsvImportAssistant::getData()
{
    int nTableRows = m_tableWidget->rowCount();
    int nTableCols = m_tableWidget->columnCount();
    std::vector<std::vector<std::string>> StringVectorVector;
    std::vector<std::string> StringVector;

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

    std::unique_ptr<OutputData<double>> result;
    result = std::make_unique<OutputData<double>>();

    if( (nDataCols < 2) || (nDataRows < 2) ){
        size_t nElem = std::max(nDataCols,nDataRows);
        result->addAxis("intensity", nElem, 0.0, double(nElem));
        std::vector<unsigned> axes_indices(1);
        unsigned item = 0;
        for(unsigned row=0; row<nDataRows; row++) {
            for(unsigned col=0; col<nDataCols; col++) {
                axes_indices[0] = item;
                size_t global_index = result->toGlobalIndex(axes_indices);
                std::string string_to_parse;
                std::vector<double> parsed_doubles;
                string_to_parse = StringVectorVector[row][col];
                parsed_doubles = DataFormatUtils::parse_doubles(string_to_parse);
                (*result)[global_index] = parsed_doubles[0];
                item++;
            }
        }
    }
    else if(m_coordinateName != ""){
        //Fill intensity values and coordinate values:
        size_t intensityCol = 1;
        size_t coordinateCol = 0;
        std::vector<double> coordValues;
        std::vector<double> intensityValues;
        for(unsigned row=0; row < nDataRows; row++) {
            std::string string_to_parse;
            std::vector<double> parsed_doubles;

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
        std::vector<unsigned> axes_indices(2);
        for(unsigned row=0; row<nDataRows; row++) {
            for(unsigned col=0; col<nDataCols; col++) {
                axes_indices[0] = col;
                axes_indices[1] = static_cast<unsigned>(nDataRows) - 1 - row;
                size_t global_index = result->toGlobalIndex(axes_indices);
                std::string string_to_parse;
                std::vector<double> parsed_doubles;
                string_to_parse = StringVectorVector[row][col];
                parsed_doubles = DataFormatUtils::parse_doubles(string_to_parse);
                (*result)[global_index] = parsed_doubles[0];
            }
        }
    }
    return result;
}


void CsvImportAssistant::generate_table() {
    m_firstDataRowSpinBox->setMaximum(int(m_csvFile->NumberOfRows()));
    m_singleDataColSpinBox->setMaximum(int(m_csvFile->NumberOfColumns()));
    m_lastDataRow = unsigned(int(m_csvFile->NumberOfRows()));
    std::vector<std::vector<std::string>> csvArray = m_csvFile->asArray();

    if (m_lastDataRow < 1) {
        m_importButton->setDisabled(true);
        return;
    }


    //Remove empty lines at the end automatically:
    while(QString::fromStdString(accumulate(csvArray[m_lastDataRow-1].begin(), csvArray[m_lastDataRow-1].end(), std::string(""))).trimmed() == ""){
        m_lastDataRow--;
        m_firstDataRowSpinBox->setMaximum(int(m_lastDataRow));
        if (m_lastDataRow < 1) {
            m_importButton->setDisabled(true);
            return;
        }
    }

    std::vector<std::vector<std::string>> dataArray( csvArray.begin() , csvArray.begin() + m_lastDataRow );

    removeBlankColumns(dataArray);

    //extractDesiredColumns(dataArray);

    set_table_data(dataArray);

    greyOutCells();

}

void CsvImportAssistant::set_table_data(std::vector<std::vector<std::string>> dataArray){

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

void CsvImportAssistant::greyOutCells(){
    int nRows = m_tableWidget->rowCount();
    int nCols = m_tableWidget->columnCount();
    QFont italicFont;
    italicFont.setItalic(true);
    italicFont.setStrikeOut(true);

    //grey out non useful first rows
    for(int i = 0; i < int(firstLine()) - 1; i++)
        for(int j = 0; j < nCols; j++){
            m_tableWidget->item(i,j)->setBackground(Qt::gray);
            m_tableWidget->item(i,j)->setFont(italicFont);
        }

    //Return if there are no columns to grey out
    if( m_coordinateCol + m_intensityCol + m_singleCol < 1 )
        return;

    //Grey out columns
    for(int i = 0; i < nRows; i++)
        for(int j = 0; j < nCols; j++)
            if(j+1 != int(m_coordinateCol) &&
                            j+1 != int(m_intensityCol)  &&
                            j+1 != int(m_singleCol) ){
                m_tableWidget->item(i,j)->setBackground(Qt::gray);
                m_tableWidget->item(i,j)->setFont(italicFont);
            }
}

void CsvImportAssistant::removeBlankColumns(std::vector<std::vector<std::string> > &dataArray){

    if(dataArray.empty())
        return;

    std::vector<std::vector<std::string>> buffer2d;
    std::vector<std::string> buffer1d;
    std::vector<int> to_be_removed;

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
        if(QString::fromStdString(accumulate(buffer1d.begin(), buffer1d.end(), std::string(""))).trimmed() == "")
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

char CsvImportAssistant::separator() const{
    char separator;
    QString tmpstr = m_separatorField->text();
    if(tmpstr.size() < 1){
        separator = guessSeparator();
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
    std::vector<char> preferredSeparators;
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
    m_setAsIntensityBins->setDisabled(m_singleCol>0);
    menu.addAction(m_setAsIntensityBins);
    connect(m_setAsIntensityBins,&QAction::triggered,this, [this](){ setColumnAsBinValues();});

    //Action "select from this row"
    QAction selectFromThisRowOn("Set as first data row",nullptr);
    menu.addAction(&selectFromThisRowOn);
    connect(&selectFromThisRowOn,&QAction::triggered,this,[this](){setFirstRow();});

    menu.addSeparator();


    //Set column as "Intensity".
    m_setAsIntensity->setDisabled(m_intensityCol>0 || m_singleCol > 0);
    menu.addAction(m_setAsIntensity);
    connect(m_setAsIntensity,&QAction::triggered,this, [this](){setColumnAsIntensity();});
    //.connect(m_setAsIntensity,&QAction::triggered,this, m_setAsIntensityColumnAsIntensity());


    //Coordinate menu disabled if a coordinate column is already set.
    QMenu *coordMenu = menu.addMenu("Set as coordinate column");
    coordMenu->setDisabled(m_coordinateCol>0 || m_singleCol > 0);


    //Set column as "Theta".
    coordMenu->addAction(m_setAsTheta);
    connect(m_setAsTheta,&QAction::triggered,this, [this](){setColumnAsCoordinate(_theta_);});


    //Set column as "2Theta".
    coordMenu->addAction(m_setAs2Theta);
    connect(m_setAs2Theta,&QAction::triggered,this, [this](){setColumnAsCoordinate(_2theta_);});


    //Set column as "q".
    coordMenu->addAction(m_setAsQ);
    connect(m_setAsQ,&QAction::triggered,this, [this](){setColumnAsCoordinate(_q_);});

    menu.addSeparator();

    //Action "reset"
    QAction resetAction("reset",nullptr);
    menu.addAction(&resetAction);
    connect(&resetAction,&QAction::triggered, [this](){reset();});

    menu.exec(m_tableWidget->mapToGlobal(position));
}


bool CsvImportAssistant::hasEqualLengthLines(std::vector<std::vector<std::string>> &dataArray){
   auto tf =  all_of( begin(dataArray), end(dataArray), [dataArray](const std::vector<std::string>& x) {
       return x.size() == dataArray.front().size();
   });
   return tf;
}

void CsvImportAssistant::extractDesiredColumns(std::vector<std::vector<std::string>> &dataArray) {

    if (dataArray.empty()) {
        m_tableWidget->clearContents();
        m_tableWidget->setRowCount(0);
        return;
    }

    if ((m_coordinateCol * m_intensityCol < 1) && (m_singleCol < 1))
        return;

    std::vector<std::string> buffer1d;
    std::vector<std::vector<std::string>> buffer2d;
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

void CsvImportAssistant::showErrorMessage(std::string message){
    QMessageBox msgBox;
    msgBox.setText(QString::fromStdString(message));
    msgBox.setIcon(msgBox.Critical);
    msgBox.exec();
}

void CsvImportAssistant::setColumnAsCoordinate(int coord){
    auto selectedRanges = m_tableWidget->selectedRanges();
    if (selectedRanges.empty())
        return;
    auto front = selectedRanges.front();
    auto col = front.leftColumn();

    m_tableWidget->setHorizontalHeaderItem( col, new QTableWidgetItem( relevantHeaders[coord]) );
    m_coordinateCol = unsigned(col+1);
    m_coordinateName = m_tableWidget->horizontalHeaderItem(col)->text();
    if(m_coordinateCol == m_intensityCol){
        m_intensityCol=0;
        return;
    }
    if(m_intensityCol > 0){
        Reload();
    }
}

void CsvImportAssistant::setColumnAsIntensity() {
    //get selected column
    auto selectedRanges = m_tableWidget->selectedRanges();
    if (selectedRanges.empty())
        return;
    auto front = selectedRanges.front();
    auto col = front.leftColumn();

    m_tableWidget->clearSelection();
    m_tableWidget->setHorizontalHeaderItem(col, new QTableWidgetItem(relevantHeaders[_intensity_]));
    m_intensityCol = unsigned(col + 1);
    if (m_coordinateCol == m_intensityCol) {
        m_coordinateCol = 0;
        return;
    }
    if (m_coordinateCol > 0) {
        Reload();
    }
}

void CsvImportAssistant::setColumnAsBinValues() {
    //get selected column
    auto selectedRanges = m_tableWidget->selectedRanges();
    if (selectedRanges.empty())
        return;
    auto front = selectedRanges.front();
    auto col = front.leftColumn();

    m_tableWidget->clearSelection();
    m_singleDataColSpinBox->setValue(col + 1);
    setHeaders();
}


void CsvImportAssistant::setColumnAsBinValues(int col) {
    if(col < 1){
        reset();
        return;
    }
    m_intensityCol = 0;
    m_coordinateCol = 0;
    m_coordinateName = "";
    m_singleCol = unsigned(col);
    Reload();
}


void CsvImportAssistant::setFirstRow(){
    //get selected column
    auto selectedRanges = m_tableWidget->selectedRanges();
    if (selectedRanges.empty())
        return;
    auto front = selectedRanges.front();
    auto row = front.topRow();
    m_firstDataRowSpinBox->setValue(row+1);
}

void CsvImportAssistant::reset(){
    m_intensityCol = 0;
    m_coordinateCol = 0;
    m_coordinateName = "";
    m_singleCol = 0;
    m_firstDataRowSpinBox->setValue(0);
    m_singleDataColSpinBox->setValue(0);
    setHeaders();
    Reload();
}
