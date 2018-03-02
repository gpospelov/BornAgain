#include "google_test.h"
#include "testlist.h"

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);

    // run all google tests
    return RUN_ALL_TESTS();
}
