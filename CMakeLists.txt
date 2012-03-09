#=======================================================================
#                 Copyright (c) 2012 S. L. Yilmaz 
#            Distributed under the MIT Software License. 
#                See accompanying file LICENSE.txt.
#=======================================================================

#
# This CMake build is for tests only. You don't need to build or configure 
# anything in order to use boost-graph-rapidxml, it is just a single header. 
#

project(BoostGraphRapidxml CXX)
cmake_minimum_required( VERSION 2.8 ) 

# Need boost (Test, Graph)
find_package(Boost REQUIRED)
# \todo add optional boost-test dependency if test libs are available
include_directories( ${Boost_INCLUDE_DIRS} ${PROJECT_SOURCE_DIR} )
enable_testing()

add_definitions( -DBOOST_TEST_NO_MAIN )
add_executable( test_driver test/test_driver.cpp ${testsrc}) 


#  +------------+
#  |  Add tests |
#  +------------+
foreach( x ${tests} )
   add_test(${x} serial_test_driver --run_test=${x})
endforeach( x )

