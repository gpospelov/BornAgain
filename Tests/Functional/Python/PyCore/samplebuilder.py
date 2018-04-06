import sys, unittest, ctypes

sys.path.append("@CMAKE_LIBRARY_OUTPUT_DIRECTORY@")
import bornagain as ba


initial_width = 42


class SampleBuilder(ba.IMultiLayerBuilder):
    """
    Test class with one registered parameter and onChange() counter
    """
    def __init__(self):
        super(SampleBuilder, self).__init__()

        self.m_width = ctypes.c_double(initial_width)
        self.registerParameter("width", ctypes.addressof(self.m_width))

        self.m_onchange_counter = 0

    def onChange(self):
        self.m_onchange_counter += 1


class SampleBuilderTest(unittest.TestCase):

    def test_registerParameters(self):
        """
        Checking parameter registration and setting the value.
        """
        builder = SampleBuilder()

        self.assertEqual(builder.m_width.value, initial_width)
        builder.setParameterValue("width", 43.0)
        # self.assertEqual(builder.m_width.value, 43.0)
        #
        # par_str = builder.parametersToString()
        # self.assertEqual(par_str, "'/SampleBuilder/width':43\n\n")

    def test_parameterString(self):
        """
        Checking that parameterString() function is correctly exposed to Python
        """
        par_str = SampleBuilder().parametersToString()
        self.assertEqual(par_str, "'/SampleBuilder/width':42\n\n")

    def test_onChange(self):
        """
        Checking that onChange is triggered once when parameter is changed
        """
        builder = SampleBuilder()
        self.assertEqual(builder.m_onchange_counter, 0)
        builder.setParameterValue("width", 43.0)
        self.assertEqual(builder.m_onchange_counter, 1)
        builder.setParameterValue("width", 44.0)
        self.assertEqual(builder.m_onchange_counter, 2)

        # setting same value, onChange shouldn't be triggered
        builder.setParameterValue("width", 44.0)
        self.assertEqual(builder.m_onchange_counter, 2)


if __name__ == '__main__':
    unittest.main()
