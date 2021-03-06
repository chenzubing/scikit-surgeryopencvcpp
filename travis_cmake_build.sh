#/*============================================================================
#
#  SKSURGERYOPENCVCPP: Image-guided surgery functions, in C++, using OpenCV.
#
#  Copyright (c) University College London (UCL). All rights reserved.
#
#  This software is distributed WITHOUT ANY WARRANTY; without even
#  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
#  PURPOSE.
#
#  See LICENSE.txt in the top level directory for details.
#
#============================================================================*/

function cmake_build {
  echo "Starting travis_cmake_build.sh"
  pwd
  echo "Requested python version:${PYTHON_VERSION}"
  cmake --version
  python --version
  mkdir build
  cd build
  if [ -n "$IS_OSX" ]; then
    extra_flags=" -DCMAKE_CXX_FLAGS=-stdlib=libc++ -DCMAKE_OSX_DEPLOYMENT_TARGET:STRING=10.7 "
  fi
  cmake -DSKSURGERYOPENCVCPP_PYTHON_VERSION:STRING=${PYTHON_VERSION} -DSKSURGERYOPENCVCPP_USE_V4L:BOOL=ON -DSKSURGERYOPENCVCPP_USE_GSTREAMER:BOOL=ON -DBUILD_SUPERBUILD:BOOL=ON -DBUILD_TESTING:BOOL=ON -DCMAKE_BUILD_TYPE:String=Release ${extra_flags} ..
  make -j 2
  cd SKSURGERYOPENCVCPP-build
  ctest -S CTestContinuous.cmake -V
  cd ../../
  echo "Finished travis_cmake_build.sh"
}
