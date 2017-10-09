#ifdef _MSC_VER
#define _VARIADIC_MAX 10
#endif

#ifdef _WIN32
#pragma warning ( push )
#pragma warning ( disable: 4275 )
#include <gtest/gtest.h>
#pragma warning ( pop )
#else
#include <gtest/gtest.h>
#endif

#include "testlist.h"
#include "ErrorStreamRedirect.h"

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);

    // redirect std::cerr stream
    std::stringstream oss;
    ErrorStreamRedirect redirecter( oss.rdbuf() );
    (void)redirecter;

    // run all google tests
    return RUN_ALL_TESTS();
}
