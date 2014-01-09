#include "TestPerformance2.h"
#include "TDatime.h"
#include "TSystem.h"
#include <sstream>


TestPerformance2::TestPerformance2()
{
    m_tests.push_back(new PerformanceTest("isgisaxs09a",20));
    m_tests.push_back(new PerformanceTest("isgisaxs09b",20));
    m_tests.push_back(new PerformanceTest("mesocrystal01",1));

}


TestPerformance2::~TestPerformance2()
{
    for(size_t i=0; i<m_tests.size(); ++i) delete m_tests[i];
}


void TestPerformance2::execute()
{
    for(size_t i=0; i<m_tests.size(); ++i) {
        PerformanceTest *test = m_tests[i];
        save_sysinfo(test);
        test->execute();
    }
}


void TestPerformance2::save_sysinfo(PerformanceTest *test)
{
    // saving date and time
    TDatime td;
    test->m_datime = std::string(td.AsSQLString());

    // saving host name
    std::string hostname(gSystem->HostName());
    // stripping host name after first '.' (somehost.jcns.frm2 -> somehost)
    std::string::size_type pos = hostname.find_first_of('.');
    if(pos != std::string::npos) {
        hostname.erase(pos,hostname.size()-pos);
    }
    test->m_hostname = hostname;

    // saving hardware information
    SysInfo_t sys_info;
    int status = gSystem->GetSysInfo(&sys_info);
    if( status == -1) {
        test->m_sysinfo = std::string("failed");
    }else{
        std::ostringstream os;
        os << std::string(gSystem->GetBuildArch()) << ", "<< sys_info.fCpuSpeed << " MHz";
        //os << ", " << 	sys_info.fL2Cache << " Kb";
        test->m_sysinfo = os.str();
    }

}
