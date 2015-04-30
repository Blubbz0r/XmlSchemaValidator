set(CURRENT_PROJECT_NAME ${PROJECT_NAME}-Console)

include_directories(${PROJECT_SOURCE_DIR}/src/lib)

add_executable(${CURRENT_PROJECT_NAME} main.cpp)

add_dependencies(${CURRENT_PROJECT_NAME} XmlSchemaValidator)

find_package(Qt5XmlPatterns REQUIRED)
qt5_use_modules(${CURRENT_PROJECT_NAME} XmlPatterns)

target_link_libraries(${CURRENT_PROJECT_NAME}
                      ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}/${CMAKE_FIND_LIBRARY_PREFIXES}XmlSchemaValidator${CMAKE_FIND_LIBRARY_SUFFIXES})
