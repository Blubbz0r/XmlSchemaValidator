# TODO allow system gmock/Qt..
project(XmlSchemaValidator)

cmake_minimum_required(VERSION 2.8.8)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib)

# Enable ExternalProject CMake module
include(ExternalProject)

# Set default ExternalProject root directory
set(external_directory ${PROJECT_BINARY_DIR}/ext)

# Add gmock
ExternalProject_Add(
    googlemock
    PREFIX ${external_directory}/gmock
    SVN_REPOSITORY http://googlemock.googlecode.com/svn/tags/release-1.7.0
    TIMEOUT 30
    # Force separate output paths for debug and release builds to allow easy
    # identification of correct lib in subsequent TARGET_LINK_LIBRARIES commands
    CMAKE_ARGS -DCMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG:PATH=DebugLibs
               -DCMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE:PATH=ReleaseLibs
               -Dgtest_force_shared_crt=ON
    # Disable install and update step
    INSTALL_COMMAND ""
    UPDATE_COMMAND ""
    # Wrap download, configure and build steps in a script to log output
    LOG_DOWNLOAD ON
    LOG_CONFIGURE ON
    LOG_BUILD ON)

# Specify directories for googlemock
ExternalProject_Get_Property(googlemock source_dir)
set(gmock_source_dir ${source_dir})
ExternalProject_Get_Property(googlemock binary_dir)
set(gmock_binary_dir ${binary_dir})

# Add Qt
# Tell CMake to run moc when necessary
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

# As moc files are generated in the binary dir, tell CMake to always look for includes there
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(QT_ROOT_DIR "E:/dev/Projects/qt_cmake-build/ext/qt/src/qt")
set(CMAKE_PREFIX_PATH ${QT_ROOT_DIR}/qtbase)
set(QT_QMAKE_EXECUTABLE ${QT_ROOT_DIR}/qtbase/bin/qmake)

# TODO dependencies (perl, python)?
# TODO linked openssl, psql/mysql plugins
# TODO current approach is Win only...
# NOTE to clean a configured qt: git submodule foreach --recursive "git clean -dfx"
#set(qt_dir ${external_directory}/qt)
#ExternalProject_add(
#    qt
#    PREFIX ${qt_dir}
#    GIT_REPOSITORY http://code.qt.io/cgit/qt/qt5.git
#    GIT_TAG 6c8876d917d6675119185d0503c552bd9aa47e54
#    TIMEOUT 30
#    CONFIGURE_COMMAND ${CMAKE_COMMAND} -D qt_dir=${qt_dir}/src/qt -P ${PROJECT_SOURCE_DIR}/QtConfigure.cmake
#    BUILD_IN_SOURCE 1
#    BUILD_COMMAND "nmake"
#    # Disable update step
#    UPDATE_COMMAND ""
#    # Wrap download, configure and build steps in a script to log output
#    LOG_DOWNLOAD ON
#    LOG_CONFIGURE ON
#    LOG_BUILD ON)
#
## Specify directories for googlemock
#ExternalProject_Get_Property(qt source_dir)
#set(qt_src_dir ${source_dir})
#set(qt_include_dir ${qt_src_dir}/include)
#ExternalProject_Get_Property(qt binary_dir)
#set(qt_binary_dir ${binary_dir})

if(MSVC_VERSION EQUAL 1700)
  add_definitions(-D_VARIADIC_MAX=10)
endif()

add_subdirectory(src)
add_subdirectory(test)
