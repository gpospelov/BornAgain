


class DocObject:
    """
    The DocObject class holds continuous block of raw C++/Doxygen documentation strings related to some declaration.
    This information is taken from BornAgain source file and later used to generate meaningful Python docstring.

    :Example:
    For the constructor of FormFactorCone, member self.doc_lines will contain following lines.
        "//! @brief Cone constructor"
        "//! @param radius of Cone's base"
        "//! @param height of Cone"
        "//! @param angle in radians between base and facet"
    while self.start_line, self.end_line will contain line numbers (starting from 0) of this block in the source file.
    """
    def __init__(self):
        self.start_line = 0
        self.end_line = 0
        self.doc_lines = []
        self.decl_string = ""

    def __len__(self):
        return len(self.doc_lines)

    def addLine(self, line, line_number):
        line = line.replace("//!", "").strip()
        self.doc_lines.append(line)
        if not self.start_line:
            self.start_line = line_number
        self.end_line = line_number

    def setDeclString(self, text):
        """
        Sets declaration string. This is done from master class using information provided by pygccxml machinery.
        Given string will be used later on to find out types of variables during python docstring generation
        """
        self.decl_string = text

    def getBriefDescription(self):
        """
        Parse @brief description from a multi line doxygen block
        """
        brief = ""
        for line in self.doc_lines:
            brief += line
            if brief[len(brief)-1] != ' ':
                brief += ' '

        if "@brief" in brief:
            brief = brief.split("@brief")[1].strip()

            pos = brief.find('.')
            if pos < 0:
                pos = brief.find('@')
            brief = brief[:pos].strip()+"."

        else:
            if len(self.doc_lines) == 1:
                brief = self.doc_lines[0]
                if not brief[len(brief)-1] == ".":
                    brief += "."

        return brief

    def getParamList(self):
        result = []
        for line in self.doc_lines:
            if "@param" in line:
                result.append(line.replace("@param", "").strip())
        return result

    def getPythonDocString(self):
        """
        Constructs and returns Python doc string basing on gathered Doxygen comments.

        :Example:
        For Cone constructor from example above it will be the following text:

        "Cone constructor\n"
        "\n"
        ":Parameters:\n"
        " - radius (float) - of Cone's base\n"
        " - height (float) - of Cone's base\n"
        " - angle (float) - in radians between base and facet\n"
        """
        brief = self.getBriefDescription()
        params = self.getParamList()
        eol = "\n"

        result = ""
        if len(brief):
            result += brief + eol + eol
        if len(params):
            result += ":Parameters:" + eol
            for p in params:
                param_name = p.split()[0]
                param_description = p[len(param_name):].strip()
                result += "  - \'" + param_name + "\' - " + param_description + eol
        return result


class DoxygenDocExtractor:
    """
    Extracts Doxygen styled documentation from source. As a result of extraction list of DocObjects will be created.
    """

    def __init__(self):
        self.file_name = None
        self.source = None
        self.doc_list = []

    def parse_file(self, filename):
        self.file_name = filename
        self.source = open(filename).readlines()
        print self.source

        docObject = DocObject()
        for i_line in range(0, len(self.source)):
            line = self.source[i_line]
            if self.is_doxygen_comment(line):
                docObject.addLine(line, i_line)
            else:
                if len(docObject):
                    self.doc_list.append(docObject)
                    docObject = DocObject()


    def getDocObject(self, line_number):
        """
        Returns DocObject which is located above given line number and the distance between given line number
        and doc block is not larger than 1 line.
        """
        for doc in self.doc_list:
            diff = line_number - doc.end_line
            print "line_number:", line_number, "doc_end_line", doc.end_line, diff
            if diff >=0 and diff <= 2:
                return doc
        return None

    def is_doxygen_comment(self, text):
        return text.lstrip()[:3] == "//!"

if __name__ == '__main__':

    # filename = "/home/pospelov/development/BornAgain/source/Core/Tools/inc/CustomBinAxis.h"
    # filename = "/home/pospelov/development/BornAgain/source/Core/FormFactors/inc/FormFactorCone.h"

    filename = "/home/pospelov/development/BornAgain/source/Core/Samples/inc/ParticleLayout.h"

    extractor = DoxygenDocExtractor()
    extractor.parse_file(filename)

    print extractor.getDocObject(27).getPythonDocString()
