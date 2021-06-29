project(fizban)

Include(FetchContent)

FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        v2.13.1)

FetchContent_MakeAvailable(Catch2)


FIND_PACKAGE(CURL REQUIRED)
IF(CURL_FOUND)
  INCLUDE_DIRECTORIES(${CURL_INCLUDE_DIR})
ELSE(CURL_FOUND)
  MESSAGE(FATAL_ERROR "Could not find the CURL library and development files.")
ENDIF(CURL_FOUND)



add_executable(${PROJECT_NAME} main.cpp)
include_directories(../crawler/)
target_link_libraries(${PROJECT_NAME} ${CURL_LIBRARIES})

target_link_libraries(${PROJECT_NAME} wvatha::crawler crawler)
target_link_libraries(${PROJECT_NAME} wvatha::crawler::torsocks)
target_link_libraries(${PROJECT_NAME} Catch2::Catch2)
