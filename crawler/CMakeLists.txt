project(crawler)


ExternalProject_Add(

  torsocks
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

ExternalProject_Get_Property(torsocks INSTALL_DIR)
set(TORSOCKS_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/deps/torsocks/src)
set(TORSOCKS_LIB_DIR ${INSTALL_DIR}/lib/torsocks)



message(STATUS ${INSTALL_DIR})
message(STATUS ${CMAKE_CURRENT_SOURCE_DIR}/deps/torsocks/src)
add_library(${PROJECT_NAME} crawler.cpp)
add_library(wvatha::crawler ALIAS ${PROJECT_NAME})

target_include_directories(${PROJECT_NAME} PRIVATE ${TORSOCKS_INCLUDE_DIR})
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/deps/torsocks/include)

set_target_properties(${PROJECT_NAME} PROPERTIES
  IMPORTED_LOCATION ${TORSOCKS_LIB_DIR}/${CMAKE_FIND_LIBRARY_PREFIXES}torsocks.a)
add_dependencies(${PROJECT_NAME} torsocks)