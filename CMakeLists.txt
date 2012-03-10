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
enable_testing()

# Need boost (Test, Graph)
find_package(Boost REQUIRED)
# \todo add optional boost-test dependency if test libs are available

# Find Rapidxml header, default to included header. Allows for testing
# system RapixXML if available.
find_path( Rapidxml_INCLUDE_DIRS rapidxml/rapidxml.hpp 
   HINTS ${PROJECT_SOURCE_DIR}/test 
   DOC "Path to RapidXML include directory"
)

# Set includes
include_directories( ${Boost_INCLUDE_DIRS} ${PROJECT_SOURCE_DIR}  ${Rapidxml_INCLUDE_DIRS} )

#  +------------+
#  |  Add tests |
#  +------------+
add_test( buildme test_driver --run_test=buildme )

#  +--------------+
#  |  Test Driver |
#  +--------------+

# Get all cpp (and hpp -- useful for IDE view) files under test/
file(GLOB_RECURSE testsrc RELATIVE ${PROJECT_SOURCE_DIR} test/*.cpp test/*.hpp)

add_definitions( -DBOOST_TEST_NO_MAIN )
add_executable( test_driver ${testsrc} )
