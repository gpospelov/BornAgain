//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      InputOutput/OutputDataReadFactory.cpp
//! @brief     Implements class OutputDataReadFactory.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //
#include "OutputDataReadFactory.h"
#include "OutputDataReader.h"
#include "OutputDataReadStrategy.h"
#include "Exceptions.h"
#include "FileSystem.h"
#include "TiffReadStrategy.h"



OutputDataReader *OutputDataReadFactory::getReader(const std::string &file_name)
{
    OutputDataReader *result = new OutputDataReader(file_name);

    result->setStrategy(getReadStrategy(file_name));
    result->setCompression(getCompressionMode(file_name));
    result->setBinaryFlag(getBinaryFlag(file_name));
    return result;
}

IOutputDataReadStrategy *OutputDataReadFactory::getReadStrategy(const std::string &file_name)
{

    IOutputDataReadStrategy *result(0);
    if( Utils::FileSystem::GetFileMainExtension(file_name) == ".int") {
        result = new OutputDataReadStreamINT();
    }

    else if( Utils::FileSystem::GetFileMainExtension(file_name) == ".tif") {
       result = new TiffReadStrategy();
    }

    else {
        throw LogicErrorException("IntensityDataIOFactory::getReader() -> Error. "
                "Don't know how to read file '" + file_name+std::string("'"));
    }

    return result;
}

bool OutputDataReadFactory::getBinaryFlag(const std::string &file_name)
{
    if(Utils::FileSystem::isCompressed(file_name)) return true;
    if(Utils::FileSystem::GetFileMainExtension(file_name) == ".int") return false;
    return true;
}

OutputDataReader::CompressionType OutputDataReadFactory::getCompressionMode(const std::string &file_name)
{
    if(Utils::FileSystem::isGZipped(file_name)) return OutputDataReader::GZIP;
    if(Utils::FileSystem::isBZipped(file_name)) return OutputDataReader::BZIP2;
    return OutputDataReader::UNCOMPRESSED;
}



//fs = InputFileStream(file_name);
//getStream() {
//    fs = open bla-bla
//    if(child) return getStream(fs);
//    else
//    return fs
//}


//ds = DecopressInputStream(InputFileStream())
//{
//    getStream(fs){

//        return fs;
//        }
//}

//mv = MoveToMemory(DecopressFileStream(InputFileStream()));



//fs.getStream()

//class InputStreamAdaptor
//{

//};
