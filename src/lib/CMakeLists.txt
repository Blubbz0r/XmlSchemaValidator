find_package(Qt5XmlPatterns REQUIRED)

add_library(${PROJECT_NAME} MessageHandler.h MessageHandler.cpp
                            XmlSchemaValidator.h XmlSchemaValidator.cpp)

qt5_use_modules(${PROJECT_NAME} XmlPatterns)
