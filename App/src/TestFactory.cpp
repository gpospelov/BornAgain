#include "TestFactory.h"
#include "TestRoughness.h"
#include "TestFresnelCoeff.h"
#include "TestFormFactor.h"
#include "TestDWBAFormFactor.h"
#include "TestDiffuseReflection.h"


//template class ISingleton<IFactory<std::string, IFunctionalTest> >;


TestFactory::TestFactory()
{
    setStoreObjects(true);
    setDeleteObjects(true);

    registerItem("roughness",  IFactoryCreateFunction<TestRoughness, IFunctionalTest> );
    registerItem("fresnel",    IFactoryCreateFunction<TestFresnelCoeff, IFunctionalTest> );
    registerItem("formfactor", IFactoryCreateFunction<TestFormFactor, IFunctionalTest> );
    registerItem("dwba",       IFactoryCreateFunction<TestDWBAFormFactor, IFunctionalTest> );
    registerItem("diffuse",    IFactoryCreateFunction<TestDiffuseReflection, IFunctionalTest> );
}


/* ************************************************************************* */
// execute specific functional tests
/* ************************************************************************* */
void TestFactory::execute(std::string name)
{
    //IFunctionalTest *test = TestFactory::instance().createItem( args[i] );
    IFunctionalTest *test(0);
    try {
        test = createItem( name );
    } catch (std::runtime_error &e) {
        std::cout << e.what() << std::endl;
        std::cout << "TestFactory::execute() -> Warning. No test with name '" << name << "' is defined." << std::endl;
        return;
    }
    test->execute();
}


/* ************************************************************************* */
// execute all registered functional tests
/* ************************************************************************* */
void TestFactory::execute_all()
{
    CallbackMap_t::const_iterator it;
    for(it=m_callbacks.begin(); it != m_callbacks.end(); it++ ) {
        createItem( it->first )->execute();
    }
}

