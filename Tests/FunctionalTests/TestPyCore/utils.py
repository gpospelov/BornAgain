"""
Collection of utils for testing
"""
import sys
import numpy
import gzip
import os

sys.path.append(os.path.abspath(
                os.path.join(os.path.split(__file__)[0],
                '..', '..', '..', 'lib')))

from libBornAgainCore import *


def get_difference(data, reference):
    """
    calculate numeric difference between result and reference data
    """
    reference = reference.reshape(data.shape)
    data -= reference
    diff = 0.0
    epsilon = sys.float_info.epsilon
    for x, y in numpy.ndindex(data.shape):
        v1 = data[x][y]
        v2 = reference[x][y]
        if v1 <= epsilon and v2 <= epsilon:
            diff += 0.0
        elif v2 <= epsilon:
            diff += abs(v1/epsilon)
        else:
            diff += abs(v1/v2)
    diff = diff/data.size
    if numpy.isnan(diff):
        raise Exception("get_difference", "isnan")

    return diff


def get_reference_data(filename):
    """
    read and return reference data from file
    """
    path = os.path.split(__file__)[0]
    if path:
        path += "/"
    #f = gzip.open(path+'../../ReferenceData/BornAgain/'+filename, 'rb')
    #reference = numpy.fromstring(f.read(), numpy.float64, sep=' ')
    #f.close()
    #return reference
    return OutputDataIOFactory.readIntensityData(path+'../../ReferenceData/BornAgain/'+filename)


