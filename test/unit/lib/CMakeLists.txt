set(CURRENT_PROJECT_NAME ${PROJECT_NAME}UnitTest)

include_directories(${gmock_source_dir}/include)
include_directories(${gmock_source_dir}/gtest/include)
include_directories(${PROJECT_SOURCE_DIR}/src/lib)

find_package(Qt5XmlPatterns REQUIRED)

qt5_add_resources(RESOURCES XmlSchemaValidatorTest.qrc)
add_executable(${CURRENT_PROJECT_NAME} main.cpp
                                       EventLoopHelper.h EventLoopHelper.cpp
                                       XmlSchemaValidatorTest.cpp
                                       ${RESOURCES})
add_dependencies(${CURRENT_PROJECT_NAME} googlemock XmlSchemaValidator)

qt5_use_modules(${CURRENT_PROJECT_NAME} XmlPatterns)

target_link_libraries(${CURRENT_PROJECT_NAME}
                      ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}/${CMAKE_FIND_LIBRARY_PREFIXES}XmlSchemaValidator${CMAKE_FIND_LIBRARY_SUFFIXES}
                      debug ${gmock_binary_dir}/DebugLibs/${CMAKE_FIND_LIBRARY_PREFIXES}gmock${CMAKE_FIND_LIBRARY_SUFFIXES}
                      optimized ${gmock_binary_dir}/ReleaseLibs/${CMAKE_FIND_LIBRARY_PREFIXES}gmock${CMAKE_FIND_LIBRARY_SUFFIXES})
