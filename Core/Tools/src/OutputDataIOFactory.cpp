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
    std::cout << "XXX 1.1" << std::endl;
    if( Utils::FileSystem::GetFileMainExtension(file_name) == ".txt") {
        read_strategy = new OutputDataReadStreamV1();
        std::cout << "XXX 1.2" << std::endl;
    } else if ( Utils::FileSystem::GetFileMainExtension(file_name) == ".ima") {
        read_strategy = new OutputDataReadStreamIMA();
        std::cout << "XXX 1.3" << std::endl;
    } else {
        throw LogicErrorException("OutputDataIOFactory::getReader() -> Error. Don't know how to read file '" + file_name+std::string("'"));
    }

    if( Utils::FileSystem::isGZipped(file_name) ) {
        std::cout << "XXX 1.4" << std::endl;
        reader->setStrategy( new OutputDataReadStreamGZip( read_strategy ) );
    } else {
        reader->setStrategy( read_strategy );
        std::cout << "XXX 1.5" << std::endl;
    }

    return OutputDataReader_t(reader);
}
