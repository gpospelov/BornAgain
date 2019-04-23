// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/ImportDataWidgets/ImportDataUtils.cpp
//! @brief     Implements ImportDataUtils namespace
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "ImportDataUtils.h"
#include "AppSvc.h"
#include "AxesItems.h"
#include "BornAgainNamespace.h"
#include "GUIHelpers.h"
#include "InstrumentItems.h"
#include "IntensityDataIOFactory.h"
#include "IntensityDataItem.h"
#include "RealDataItem.h"
#include "CsvImportAssistant.h"
#include "PointwiseAxis.h"
#include "projectmanager.h"
#include <QFileDialog>
#include <QFileInfo>
#include <QMessageBox>

namespace
{
const QString filter_string_ba = "Intensity File (*.int *.gz *.tif *.tiff *.txt *.csv);;"
                              "Other (*.*)";
const QString filter_string_ascii = "Intensity File (*.int *.int.gz *.txt *.csv *.dat *.ascii);;"
                              "Ascii column-wise data (*.*)";

int getRank(const RealDataItem& item)
{
    return static_cast<int>(item.shape().size());
}

int getRank(const InstrumentItem& item) {
    return static_cast<int>(item.shape().size());
}
}

std::unique_ptr<OutputData<double>> ImportDataUtils::ImportKnownData(QString& fileName){
    //Try to use the canonical tools for importing data
    std::unique_ptr<OutputData<double>> result;
    try {
        std::unique_ptr<OutputData<double>> data(
                    IntensityDataIOFactory::readOutputData(fileName.toStdString()));
        result = CreateSimplifiedOutputData(*data);
    } catch(std::exception& ex)
    {
        QString message = QString("Error while trying to read file\n\n'%1'\n\n%2")
                .arg(fileName)
                .arg(QString::fromStdString(std::string(ex.what())));
        QMessageBox::warning(nullptr, "IO Problem", message);
    }
    return result;

}

std::unique_ptr<OutputData<double>> ImportDataUtils::ImportReflectometryData(QString& fileName){
    std::unique_ptr<OutputData<double>> oData(new OutputData<double>);
    try {
        std::string line;
        std::vector<std::vector<double>> vecVec;
        std::map<double,double> QvsR;
        std::map<double,double> QvsDR;
        std::map<double,double> QvsDQ;

        //Read numbers from file:
        std::ifstream fin(fileName.toStdString().c_str(), std::ios::in);
        while( std::getline(fin, line) ) {
            try {
                std::vector<double> rowVec = DataFormatUtils::parse_doubles(line);
                vecVec.push_back(rowVec);
            } catch (...) {
                continue;
            }
        }
        if(fin.is_open())
            fin.close();

        // validate - There is at least one row and at least two columns
        size_t nrows = vecVec.size();
        if (nrows < 1)
            throw std::runtime_error("Import1dTextData: no numerical values found");
        size_t ncols = vecVec[0].size();
        if (ncols < 2)
            throw std::runtime_error("Import1dTextData: Minimum 2 columns required");

        // Assign Q vs R, dR, dQ:
        for(size_t row=0; row<nrows; row++) {
            if(vecVec[row].size() != ncols)
                throw std::runtime_error("The number of columns varies among the rows");
            double Q = vecVec[row][0];
            switch(ncols){
            case 1:
                break;
            case 2:
                QvsR[Q]  = vecVec[row][1];
                QvsDR[Q] = 0;
                QvsDQ[Q] = 0;
                break;
            case 3:
                QvsR[Q]  = vecVec[row][1];
                QvsDR[Q] = vecVec[row][2];
                QvsDQ[Q] = 0;
                break;
            default:
                QvsR[Q]  = vecVec[row][1];
                QvsDR[Q] = vecVec[row][2];
                QvsDQ[Q] = vecVec[row][3];
                break;
            }
        }


        std::vector<double> qVec;
        std::vector<double> rVec;
        for(auto it = QvsR.begin(); it != QvsR.end(); ++it) {
            if(it->second <= 0)
                continue;
            qVec.push_back(it->first);
            rVec.push_back(it->second);
        }


        oData->addAxis(PointwiseAxis("qVector",qVec));
        oData->setRawDataVector(rVec);
    } catch(std::exception& ex)
    {
        QString message = QString("Error while trying to read file\n\n'%1'\n\n%2")
                        .arg(fileName)
                        .arg(QString::fromStdString(std::string(ex.what())));
        QMessageBox::warning(nullptr, "IO Problem", message);
    }
    return oData;
}

std::unique_ptr<OutputData<double>> ImportDataUtils::Import2dData(QString& baseNameOfLoadedFile)
{
    QString dirname = AppSvc::projectManager()->userImportDir();
    QString fileName = QFileDialog::getOpenFileName(Q_NULLPTR, QStringLiteral("Open Intensity File"),
                                                    dirname, filter_string_ba);

    if (fileName.isEmpty())
        return nullptr;


    QString newImportDir = GUIHelpers::fileDir(fileName);
    if (newImportDir != dirname)
        AppSvc::projectManager()->setImportDir(newImportDir);

    QFileInfo info(fileName);
    baseNameOfLoadedFile = info.baseName();

    return ImportKnownData(fileName);

}

ImportDataInfo ImportDataUtils::Import1dData(QString& fileName)
{
    if(DataFormatUtils::isCompressed(fileName.toStdString()) ||
                    DataFormatUtils::isIntFile(fileName.toStdString()) ||
                    DataFormatUtils::isTiffFile(fileName.toStdString())
                    ){
        try{
            return ImportDataInfo(ImportKnownData(fileName), AxesUnits::NBINS);
        }
        catch(...){
            return getFromImportAssistant(fileName);
        }
    }
    else{
        try{
            return ImportDataInfo(ImportReflectometryData(fileName), AxesUnits::NBINS);
        }
        catch(...){
            QString message = QString("There was a problem while trying to import data from file:\n\n'%1'\n--\n%2\n--\n")
                            .arg(fileName)
                            .arg("Data format not supported. Please check your file in an external editor.");
            QMessageBox::warning(nullptr, "Unable to read.", message);

            return ImportDataInfo();
        }
    }
}



ImportDataInfo ImportDataUtils::getFromImportAssistant(QString& fileName){
    if(!csv::isAscii(fileName)){
        QString message = QString("There was a problem while trying to import data from file:\n\n'%1'\n--\n%2\n--\n")
                        .arg(fileName)
                        .arg("The file seems to contain binary data");
        QMessageBox::warning(nullptr, "Unable to read.", message);
        return ImportDataInfo();
    }
    try{
        CsvImportAssistant assistant(fileName,true);
        return assistant.getData();
    }catch(std::exception& e){
        QString message = QString("There was a problem while trying to import data from file:\n\n'%1'\n--\n%2\n--\n")
                        .arg(fileName)
                        .arg(QString::fromStdString(std::string(e.what())));
        QMessageBox::warning(nullptr, "IO Problem", message);
    }
    return ImportDataInfo();
}


bool ImportDataUtils::Compatible(const InstrumentItem& instrumentItem,
                                 const RealDataItem& realDataItem)
{
    return getRank(instrumentItem) == getRank(realDataItem);
}

std::unique_ptr<OutputData<double>>
ImportDataUtils::CreateSimplifiedOutputData(const OutputData<double>& data)
{
    const size_t data_rank = data.getRank();
    if (data_rank > 2 || data_rank < 1)
        throw std::runtime_error("Error in ImportDataUtils::CreateSimplifiedOutputData: passed "
                                 "array is neither 1D nor 2D");

    std::unique_ptr<OutputData<double>> result(new OutputData<double>);
    for (size_t i = 0; i < data_rank; ++i) {
        const IAxis& axis = data.getAxis(i);
        const size_t axis_size = axis.size();
        const double min = 0.0;
        const double max = axis_size;
        result->addAxis(FixedBinAxis(axis.getName(), axis_size, min, max));
    }
    result->setRawDataVector(data.getRawDataVector());

    return result;
}

QString ImportDataUtils::printShapeMessage(const std::vector<int>& instrument_shape,
                                           const std::vector<int>& data_shape)
{
    auto to_str = [](const std::vector<int>& shape) {
        std::string result;
        for (size_t i = 0, size = shape.size(); i < size; ++i) {
            result += std::to_string(shape[i]);
            if (i + 1 != size)
                result += ", ";
        }
        return result;
    };

    std::string message_string = "instrument [";
    message_string += to_str(instrument_shape);
    message_string += "], data [";
    message_string += to_str(data_shape);
    message_string += "]";
    return QString::fromStdString(std::move(message_string));
}
