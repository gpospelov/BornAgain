#!/usr/bin/python
 # -*- coding: utf-8 -*-


## ************************************************************************** ##
##
##  BornAgain: simulate and fit scattering at grazing incidence
##
##! @file      test_performance.py
##! @brief     Defines class TestPerformance for logging performance changes
##!
##! @homepage  http:##www.bornagainproject.org
##! @license   GNU General Public License v3 or higher (see COPYING)
##! @copyright Forschungszentrum Jülich GmbH 2016
##! @authors   Scientific Computing Group at MLZ Garching
##! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
##
## ************************************************************************** ##

from __future__ import print_function
import datetime
import sys
import platform
import timeit
from collections import OrderedDict
import resource
from libBornAgainCore import *

logfile = sys.stdout

class PerfTest:
    def __init__(self, name, simulation_name, sample_builder, nrepetitions):
        self.m_test_name = name
        self.m_simulation_name = simulation_name
        self.m_sample_builder_name = sample_builder
        self.m_nrepetitions = nrepetitions
        self.m_cpu_time = 0.0
        self.m_real_time = 0.0

class TestPerformance:
    def __init__(self, filename=None):
        self.m_tests = []
        self.m_datime = ""
        self.m_hostname = ""
        self.m_sysinfo = ""
        self.m_filename = filename

        self.add("MultiLayer",         "MaxiGISAS",    "MultiLayerWithRoughnessBuilder", 1);
        self.add("CylindersInDWBA",    "MaxiGISAS",    "CylindersInDWBABuilder", 10);
        self.add("RotatedPyramids",    "MaxiGISAS",    "RotatedPyramidsBuilder", 10);
        self.add("CoreShell",          "MaxiGISAS",    "CoreShellParticleBuilder", 10);
        self.add("SquareLattice",      "MaxiGISAS",    "SquareLatticeBuilder", 10);
        self.add("RadialParaCrystal",  "MaxiGISAS",    "RadialParaCrystalBuilder", 10);
        self.add("HexParaCrystal",     "BasicGISAS",   "HexParaCrystalBuilder", 1);
        self.add("SSCA",               "MaxiGISAS",    "SizeDistributionSSCAModelBuilder", 10);
        self.add("Mesocrystal",        "MaxiGISAS",    "MesoCrystalBuilder", 2);
        self.add("PolMagCyl",          "MaxiGISAS00",  "MagneticCylindersBuilder", 10);
        logfile.write("\nPreparing to run %d performance tests.\n\n" % len(self.m_tests))

    def add(self, name, simulation_name, sample_builder, nrepetitions):
        self.m_tests.append(PerfTest(name, simulation_name, sample_builder, nrepetitions))

    def execute(self):
        self.init_sysinfo()

        for test in self.m_tests:
            self.runTest(test)
        
        self.write_results()
        
    def runTest(self, test):
        simulationRegistry = SimulationRegistry()
        sampleFactory = SampleBuilderFactory()
                
        # std::cout << "Running test: " << std::setw(20) << std::left << test->m_test_name << " ... ";
        logfile.write("Running test: %-30s " % test.m_test_name)
        logfile.flush()
        
        # std::cout.flush();

        # boost::scoped_ptr<Simulation> simulation(simulationRegistry.createSimulation(test->m_simulation_name));
        simulation = simulationRegistry.createSimulation(test.m_simulation_name)
        
        # SampleBuilder_t sample = sampleFactory.createBuilder(test->m_sample_builder_name);
        sample = sampleFactory.createBuilder(test.m_sample_builder_name)

        # timeit.default_timer picks the most accurate timer available
        start_real_time = timeit.default_timer()

        # resource.getrusage is less accurate but returns user time
        start_cpu_time = resource.getrusage(resource.RUSAGE_SELF)[0]

        for i in range(test.m_nrepetitions):
            simulation.setSampleBuilder(sample)
            simulation.runSimulation()

        end_real_time = timeit.default_timer()
        end_cpu_time = resource.getrusage(resource.RUSAGE_SELF)[0]

        # note that on multi-core system, cpu time can be higher than wall time
        test.m_real_time = end_real_time - start_real_time
        test.m_cpu_time = end_cpu_time - start_cpu_time

        logfile.write("OK: %-6.3f (real sec), %-6.3f (cpu sec) \n" % (test.m_real_time, test.m_cpu_time))

    def write_results(self):

        if ( self.m_filename != None ):
            try:
                write_file = open(self.m_filename, "a")
            except:
                sys.stderr.write("Could not open filed %s for writing.\n" % self.m_filename)
                exit(1)
        else:
            write_file = sys.stdout

        logfile.write("\nWriting output to %s...\n\n" % write_file.name)
                
        dictionary = OrderedDict()

        dictionary["date"] = self.m_datime
        dictionary["hostname"] = self.m_hostname
        dictionary["sysinfo"] = self.m_sysinfo

        sum_real = 0.0
        sum_cpu = 0.0
        
        for test in self.m_tests:
            sum_real += test.m_real_time;
            sum_cpu += test.m_cpu_time;

        dictionary["total cpu"] = "%-.4f" % sum_cpu
        dictionary["total real"] = "%-.4f" % sum_real

        for test in self.m_tests:
            dictionary[test.m_test_name] = "%-.4f" % test.m_real_time
            
        pretty_write(dictionary, write_file)
        write_file.write("\n");
        write_file.flush()

        if ( self.m_filename != None ):
            write_file.close()  
            
    def init_sysinfo(self):
        system, node, release, version, machine, processor = platform.uname()
        
        if system == 'Linux':        
            system, version, id = platform.linux_distribution()

        self.m_sysinfo = system + " " + version + " " + machine
        self.m_datime = datetime.datetime.strftime(datetime.datetime.now(), '%Y-%m-%d %H:%M:%S')
        self.m_hostname = node        


def pretty_write(dictionary, file):
    header = "|"
    footer = "|"

    for key in dictionary:
        value = dictionary[key]
        length = max(len(key), len(value))
        format_str = " {0:" + str(length) + "} |"
        header += format_str.format(key)
        footer += format_str.format(value)

    file.write(header + "\n")
    file.write(footer + "\n")

if __name__ == '__main__':

    if ( len(sys.argv) > 2 ):
        print("Usage: test_performance.py [output file]")
        exit(0)

    if (len(sys.argv) == 2):
        filename = sys.argv[1]
    else:
        filename = None
        
    testPerformance = TestPerformance(filename)
    testPerformance.execute()
