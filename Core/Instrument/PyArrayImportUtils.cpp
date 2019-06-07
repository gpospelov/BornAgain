#include "PyArrayImportUtils.h"
#include "ArrayUtils.h"

OutputData<double>* PyArrayImport::importArrayToOutputData(const std::vector<double>& vec)
{
    return ArrayUtils::createData(vec).release();
}

OutputData<double>*
PyArrayImport::importArrayToOutputData(const std::vector<std::vector<double>>& vec)
{
    return ArrayUtils::createData(vec).release();
}
