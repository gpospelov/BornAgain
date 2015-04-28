"""
Collection of classes to parse Doxygen C++ comments from cpp file and generate from them nicely looking docstring.
"""

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
        Given string will be used later on to find out types of variables during python docstring generation.
        Currently not used.
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
        " - radius - of Cone's base\n"
        " - height - of Cone's base\n"
        " - angle - in radians between base and facet\n"

        :TODO:
        Make parameter line show type of variable. It can be parsed from the declaration string.
        " - radius (float) - of Cone's base\n"

        """
        brief = self.getBriefDescription()
        params = self.getParamList()
        eol = "\\n"

        result = ""
        if len(brief):
            result += brief
        if len(params):
            result += eol + eol
            result += ":Parameters:" + eol
            for p in params:
                param_name = p.split()[0]
                param_description = p[len(param_name):].strip()
                result += "  - \'" + param_name + "\' - " + param_description + eol
        return "\""+result+"\""



class DoxygenDocExtractor:
    """
    Extracts Doxygen styled documentation from source or generates it from description.
    """
    def __init__(self):
        #for caching source
        self.file_name = None
        self.source = None
        self.doc_list = []

    def parse_file(self, filename):
        self.file_name = filename
        self.source = open(filename).readlines()

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
            #print "line_number:", line_number, "doc_end_line", doc.end_line, diff
            # We count lines starting from 0, pygccxml counts starting from 1. Where can be one empty line between
            # Doxygen comment and declaration. Also pygccxml seems to rely on position of bracket "{" in class declaration.
            # So to assign comment block to given declaration, we have to have the difference in line numbering
            # between 2 and 4.
            if diff >=2 and diff <= 4:
                return doc
        return None

    def is_doxygen_comment(self, text):
        return text.lstrip()[:3] == "//!"

    def __call__(self, declaration):
        if self.file_name != declaration.location.file_name:
            self.doc_list = []
            self.file_name = declaration.location.file_name
            self.parse_file(self.file_name)

        doc = self.getDocObject(declaration.location.line)

        if not doc == None:
            return doc.getPythonDocString()
