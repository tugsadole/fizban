project(crawler)
add_library(${PROJECT_NAME} crawler.cpp)
add_library(wvatha::crawler ALIAS ${PROJECT_NAME})