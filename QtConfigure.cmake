if(NOT DEFINED qt_dir)
  message(FATAL_ERROR "error: required variable qt_dir not defined...")
endif()

#
# Windows builds with nmake are "in-source/in-place" builds.
#   i.e. source == build == install dir
#   and prefix is irrelevant...
#
# Linux/Mac builds with make honor -prefix. They do not necessarily have to
# be "in-source/in-place" builds, although they can be... So we do in-source
# everywhere for consistency's sake.
#
set(cmd configure.bat)
set(args ${args} -debug-and-release -opensource -confirm-license -nomake examples -nomake tests -skip qtwebkit -skip qtwebkit-examples -skip qtfeedback -skip qtserialport -skip qtquick1 -skip qt3d -skip qtsystems -skip qtwayland -skip qtwebengine)

message(STATUS "cmd='${cmd}'")
message(STATUS "args='${args}'")
message(STATUS "qt_dir='${qt_dir}'")

execute_process(COMMAND ${cmd} ${args}
  WORKING_DIRECTORY ${qt_dir}
  RESULT_VARIABLE rv
)

if(NOT "${rv}" STREQUAL "0")
  message(FATAL_ERROR "error: problem configuring Qt: rv='${rv}'")
endif()
