import sys, unittest, ctypes

sys.path.append("@CMAKE_LIBRARY_OUTPUT_DIRECTORY@")
import bornagain as ba


initial_width = 42


class SampleBuilder(ba.IMultiLayerBuilder):
    def __init__(self):
        super(SampleBuilder, self).__init__()

        self.m_width = ctypes.c_double(initial_width)
        self.registerParameter("width", ctypes.addressof(self.m_width))


class SampleBuilderTest(unittest.TestCase):

    def test_registerParameters(self):
        builder = SampleBuilder()

        self.assertEqual(builder.m_width.value, initial_width)

        builder.setParameterValue("width", 43.0)
        self.assertEqual(builder.m_width.value, 43.0)

        str = builder.parametersToString()
        self.assertEqual(str, "'/SampleBuilder/width':43\n\n")


if __name__ == '__main__':
    unittest.main()
