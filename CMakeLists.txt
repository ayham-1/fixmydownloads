cmake_minimum_required(VERSION 3.15)

project("fixmydownloads" VERSION 0.0.1)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/CMake" ${CMAKE_MODULE_PATH})

# Set C compiler options
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -g -Wall -Werror -Wno-unused-function")
set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -O3 -Wall -Werror -Wno-unused-function")

# Code Coverage Configuration
add_library(coverage_config INTERFACE)

add_executable(fixmydl src/main.c)

install(TARGETS fixmydl 
  RUNTIME DESTINATION bin
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib)

set(CPACK_PACKAGE_VENDOR "altffour")
set(CPACK_PACKAGE_CONTACT "ayhamaboualfadl@gmail.com")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Download folder organizer")
set(CPACK_PACKAGE_VERSION ${PROJECT_VERSION})
set(CPACK_PACKAGE_FILE_LICENSE "${CMAKE_SOURCE_DIR}/LICENCE")
set(CPACK_PACKAGE_FILE_README "${CMAKE_SOURCE_DIR}/README.md")
SET(CPACK_GENERATOR "DEB;RPM;TGZ;STGZ;TBZ2;TZ;ZIP")

include(CPack)

