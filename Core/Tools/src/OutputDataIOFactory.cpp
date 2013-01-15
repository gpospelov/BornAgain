#include "OutputDataIOFactory.h"
#include "Exceptions.h"
#include "Utils.h"



OutputData<double > *OutputDataIOFactory::getOutputData(const std::string &file_name)
{
    return getReader(file_name)->getOutputData();
}

OutputDataIOFactory::OutputDataReader_t OutputDataIOFactory::getReader(const std::string &file_name)
{
    OutputDataReader *reader = new OutputDataReader( file_name );

    IOutputDataReadStrategy *read_strategy(0);
    if( Utils::FileSystem::GetFileMainExtension(file_name) == ".txt") {
        read_strategy = new OutputDataReadStreamV1();
    } else if ( Utils::FileSystem::GetFileMainExtension(file_name) == ".ima") {
        read_strategy = new OutputDataReadStreamIMA();
    } else {
        throw LogicErrorException("OutputDataIOFactory::getReader() -> Error. Don't know how to read file '" + file_name+std::string("'"));
    }

    if( Utils::FileSystem::isGZipped(file_name) ) {
        reader->setStrategy( new OutputDataReadStreamGZip( read_strategy ) );
    } else {
        reader->setStrategy( read_strategy );
    }

    return OutputDataReader_t(reader);
}
