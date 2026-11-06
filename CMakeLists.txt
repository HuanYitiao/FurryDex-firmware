# The following five lines of boilerplate have to be in your project's
# CMakeLists in this exact order for cmake to work correctly
cmake_minimum_required(VERSION 3.22)

# Layering: application -> middleware, never the other way round.
# Add "application" here once its first component exists.
set(EXTRA_COMPONENT_DIRS middleware)

include($ENV{IDF_PATH}/tools/cmake/project.cmake)
project(furrydex)
