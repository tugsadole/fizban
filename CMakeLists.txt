project(subs)
cmake_minimum_required(VERSION 3.2.2)

include(ExternalProject)

FIND_PACKAGE(CURL)
IF(CURL_FOUND)
  INCLUDE_DIRECTORIES(${CURL_INCLUDE_DIR})
  SET(requiredlibs ${requiredlibs} ${CURL_LIBRARIES} )
ELSE(CURL_FOUND)
  MESSAGE(FATAL_ERROR "Could not find the CURL library and development files.")
ENDIF(CURL_FOUND)


ExternalProject_Add(

  ${PROJECT_NAME} 
  GIT_REPOSITORY https://github.com/dgoulet/torsocks.git
  GIT_TAG origin/master
  SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/deps/torsocks
  PREFIX deps/torsocks
  BUILD_IN_SOURCE 1
  UPDATE_DISCONNECTED true
  CONFIGURE_COMMAND ./autogen.sh
  COMMAND ./configure --prefix=<INSTALL_DIR>
  BUILD_COMMAND ${MAKE}
  BUILD_BYPRODUCTS <INSTALL_DIR>/lib/${CMAKE_FIND_LIBRARY_PREFIXES}torsocks.a
  INSTALL_COMMAND make install
)

add_subdirectory(main)
add_subdirectory(crawler)
