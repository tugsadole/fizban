project(torsocks_boost)

add_library(${PROJECT_NAME} torsocks_boost.cpp)
add_library(wvatha::crawler::torsocks ALIAS ${PROJECT_NAME})

set(Boost_USE_STATIC_LIBS        ON)  # only find static libs
set(Boost_USE_DEBUG_LIBS         OFF) # ignore debug libs and 
set(Boost_USE_RELEASE_LIBS       ON)  # only find release libs 
set(Boost_USE_MULTITHREADED      ON)
set(Boost_USE_STATIC_RUNTIME    OFF) 


find_package(Boost REQUIRED)
if(Boost_FOUND)
    find_path(BOOST_FILESYSTEM_INCLUDE_DIRS boost/asio.hpp)

    message("Found boost adding, linking...")
    target_include_directories(${PROJECT_NAME} PUBLIC ${BOOST_FILESYSTEM_INCLUDE_DIRS})
    target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES})
endif()