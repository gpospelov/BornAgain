# Patches header in all source files
#
# Usage: cd <BornAgain_source>; python dev-tools/code-tools/update_sourcecode_header.py

import os
import sys
import glob


directories = [
    "Core/Algorithms",
    "Core/FormFactors",
    "Core/Geometry",
    "Core/Samples",
    "Core/StandardSamples",
    "Core/Tools",
    "Fit/FitKernel",
    "GUI/coregui",
    "GUI/main",
    "App"
]

header_top = [
    u"// ************************************************************************** //",
    u"//                                                                              ",
    u"//  BornAgain: simulate and fit scattering at grazing incidence                 ",
    u"//                                                                              "
    ]
header_center = [
    u"//! @file      Algorithms/inc/Beam.h                                            ",
    u"//! @brief     Defines class Beam                                               "
    ]
header_bottom = [
    u"//!                                                                             ",
    u"//! @homepage  http://www.bornagainproject.org                                  ",
    u"//! @license   GNU General Public License v3 or higher (see COPYING)            ",
    u"//! @copyright Forschungszentrum J\u00fclich GmbH 2015                          ",
    u"//! @authors   Scientific Computing Group at MLZ Garching                       ",
    u"//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke      ",
    u"//                                                                              ",
    u"// ************************************************************************** //"
    ]


def get_files_to_update(path):
    """
    Returns list of source code files to update in given directory including subdirectories
    """
    result = []
    for (dirpath, dirnames, filenames) in os.walk(path):
        for filename in filenames:
            file_ext = os.path.splitext(filename)[1]
            if file_ext == ".h" or file_ext == ".cpp":
                result.append(os.sep.join([dirpath, filename]))
            else:
                print "{:65s} {:10s}".format(os.sep.join([dirpath, filename]), "non standard")
    return sorted(result)


def get_current_header(file_content):
    """
    Returns current header of file
    """
    result = []
    for line in file_content:
        if line.startswith("//"):
            result.append(line)
        else:
            break

    return result


def get_new_header(current_header):
    """
    Return list of lines representing new header. List is empty if old header is non-standard one
    """
    if len(current_header) < 14 or len(current_header) > 15:
        return []

    file_part = []
    brief_part = []
    for i in range(0, len(current_header)):
        if "@file" in current_header[i]:
            file_part.append(current_header[i])
        elif "@brief" in current_header[i]:
            brief_part.append(current_header[i])
            if len(current_header[i+1]) > 3:
                brief_part.append(current_header[i+1])

    if len(file_part) == 0 or len(brief_part) == 0:
        return []

    result = header_top + file_part + brief_part + header_bottom
    return result


def update_header_in_file(filename):
    """
    Updates, if necessary, the header in given file
    """
    fin = open(filename, 'r')
    lines = [line.decode('utf8').rstrip('\n') for line in fin]
    fin.close()

    current_header = get_current_header(lines)
    new_header = get_new_header(current_header)

    if len(new_header) == 0:
        print "{:65s} {:10s}".format(filename, "non standard")
        return

    fout = open(filename, 'w')
    new_content = new_header + lines[len(current_header):]
    for line in new_content:
        fout.write(line.encode('utf8').rstrip() + "\n")
    fout.close()

    print "{:65s} {:10s}".format(filename, "OK")



def update_directory(dirname):
    """
    Updates all files recursively in given directory
    """
    # if not os.path.isdir(dirname):
    #     exit("No such directory " + dirname)
    #
    # list_of_files = get_files_to_update(dirname)
    #
    # for filename in list_of_files:
    #     update_header_in_file(filename)

    update_header_in_file("./GUI/coregui/mainwindow/aboutapplicationdialog.cpp")

if __name__ == '__main__':

    for dirname in directories:
        update_directory(dirname)
