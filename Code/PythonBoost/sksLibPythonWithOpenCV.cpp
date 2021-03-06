/*=============================================================================

  SKSURGERYOPENCVCPP: Image-guided surgery functions, in C++, using OpenCV.

  Copyright (c) University College London (UCL). All rights reserved.

  This software is distributed WITHOUT ANY WARRANTY; without even
  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
  PURPOSE.

  See LICENSE.txt in the top level directory for details.

=============================================================================*/

/*=============================================================================

  Derived from pyboostcvconverter by Gregory Kramida.
  See full package, as a git submodule in ./pyboostcvconverter.

=============================================================================*/
#define PY_ARRAY_UNIQUE_SYMBOL pbcvt_ARRAY_API

#include "sksTriangulate.h"
#include "sksStoyanov2010.h"
#include "sksException.h"
#include "sksVideoCapture.h"
#include "sksMasking.h"
#include "sksDotDetection.h"

#include <boost/python.hpp>
#include <boost/python/exception_translator.hpp>
#include <pyboostcvconverter/pyboostcvconverter.hpp>

using namespace boost::python;

#include <ostream>
#include <sstream>

namespace sks {

#if (PY_VERSION_HEX >= 0x03000000)
static void *init_ar() {
#else
static void init_ar(){
#endif
  Py_Initialize();
  import_array();
  return NUMPY_IMPORT_ARRAY_RETVAL;
}

void translate_exception(Exception const& e)
{
  std::ostringstream ss;
  ss << e.GetDescription();
  ss << " in file:" << e.GetFileName();
  ss << ", line:" << e.GetLineNumber();
  PyErr_SetString(PyExc_RuntimeError, ss.str().c_str());
}

// The name of the module should match that in CMakeLists.txt
BOOST_PYTHON_MODULE (sksurgeryopencvpython) {
  init_ar();

  boost::python::to_python_converter<cv::Mat, pbcvt::matToNDArrayBoostConverter>();
  pbcvt::matFromNDArrayBoostConverter();

  boost::python::register_exception_translator<Exception>(&translate_exception);

  boost::python::def("triangulate_points_using_hartley", TriangulatePointsUsingHartley);
  boost::python::def("triangulate_points_using_midpoint", TriangulatePointsUsingMidpointOfShortestDistance);
  boost::python::def("compute_disparity_using_stoyanov", ComputeDisparityUsingStoyanov);
  boost::python::def("match_points_using_stoyanov", MatchPointsUsingStoyanov);
  boost::python::def("reconstruct_points_using_stoyanov", ReconstructPointsUsingStoyanov);
  boost::python::def("mask_points", MaskPoints);
  boost::python::def("mask_stereo_points", MaskStereoPoints);
  boost::python::def("extract_dots", ExtractDots);

  class_<VideoCapture>("VideoCapture", init<int, int, int>())
    .def(init<int>())
    .def("read", &VideoCapture::read)
    .def("isOpened", &VideoCapture::isOpened)
  ;
}

}  // end namespace sks
