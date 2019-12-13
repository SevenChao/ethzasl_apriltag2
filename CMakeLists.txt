cmake_minimum_required(VERSION 3.5)
project(ethzasl_apriltag2)

set(CMAKE_CXX_STANDARD 11)

#################
#     EIGEN     #
#################
find_package(Eigen3 REQUIRED)
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")

#################
#    OPENCV     #
#################
find_package(OpenCV REQUIRED)


add_definitions("-fPIC -O3")
find_package(Threads)

if ("!${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
  # The clang compiler (on osx) is somehow much more strict
  # than the compilers on ubuntu and so this does not seem
  # possible on OSX just yet.
  add_definitions( -Werror )
endif()

#################
#   INCLUDE     #
#################
include_directories(include ${EIGEN3_INCLUDE_DIR} ${OpenCV_INCLUDE_DIRS})

#################
# output path   #
#################
set(EXECUTABLE_OUTPUT_PATH bin)
set(LIBRARY_OUTPUT_PATH lib)

#############
# LIBRARIES #
#############
file(GLOB SOURCE_FILES "src/*.cc")
add_library(${PROJECT_NAME} SHARED ${SOURCE_FILES})
# set_target_properties(${PROJECT_NAME} PROPERTIES PUBLIC_HEADER include/*.h)
set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE C)
target_link_libraries(${PROJECT_NAME} ${CMAKE_THREAD_LIBS_INIT} ${OpenCV_LIBS})

##############
# LIB INSTALL#
##############
install(
   DIRECTORY include/apriltags/
   DESTINATION include
)
install(
   TARGETS ${PROJECT_NAME}
   ARCHIVE DESTINATION lib
   LIBRARY DESTINATION lib
   COMPONENT library
)
############
# EXAMPLES #
############
if(NOT APPLE)
  add_executable(apriltags_demo 
    example/apriltags_demo.cpp example/Serial.cpp
  )
  target_link_libraries(apriltags_demo ${PROJECT_NAME} v4l2)
endif()

  add_executable(image_demo 
                  example/apriltags_image_demo.cpp
)
target_link_libraries(image_demo ${PROJECT_NAME})
