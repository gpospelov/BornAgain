#include "OutputDataIOFactory.h"
#include "Exceptions.h"

OutputDataIOFactory::OutputDataIOFactory()
{
}




OutputDataReader *OutputDataIOFactory::getReader(const std::string &file_name)
{
    OutputDataReader *reader = new OutputDataReader( file_name );
    if( file_name.find(".txt.gz") != std::string::npos ) {
        reader->setStrategy( new OutputDataReadStreamGZip( new OutputDataReadStreamV1() ) );
    } else if(file_name.find(".txt") != std::string::npos ) {
        reader->setStrategy( new OutputDataReadStreamV1());
    } else {
        std::string info("OutputDataIOFactory::getReader() -> Error. Don't know how to read file '" + file_name+std::string("'"));
        throw LogicErrorException(info);
    }
    return reader;
}
