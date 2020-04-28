cmake_minimum_required(VERSION 3.15)

project("fixmydownloads" VERSION 1.1.0 LANGUAGES C)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/CMake" ${CMAKE_MODULE_PATH})

# Set C compiler options
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -g")
set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -O3")

add_executable(fixmydl src/main.c)
target_compile_options(fixmydl PUBLIC -Wall -Werror -Wno-unused-function -pedantic)

install(TARGETS fixmydl 
  RUNTIME DESTINATION bin
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib)

set(CPACK_PACKAGE_VENDOR "altffour")
set(CPACK_PACKAGE_CONTACT "ayhamaboualfadl@gmail.com")
set(CPACK_PACKAGE_VERSION ${PROJECT_VERSION})
set(CPACK_PACKAGE_FILE_LICENSE "${CMAKE_SOURCE_DIR}/LICENSE")
set(CPACK_PACKAGE_FILE_README "${CMAKE_SOURCE_DIR}/README.md")
set(CPACK_PACKAGE_DESCRIPTION "Refer to https://github.com/realaltffour/fixmydownloads/ for operation instructions.")
set(CPACK_RPM_PACKAGE_DESCRIPTION "Refer to https://github.com/realaltffour/fixmydownloads/ for operation instructions.")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Download folder organizer")
SET(CPACK_GENERATOR "DEB;RPM;TGZ;STGZ;TBZ2;TZ;ZIP")

set(CPACK_DEBIAN_PACKAGE_CONTROL_EXTRA "${CMAKE_SOURCE_DIR}/scripts/postinst;")
set(CPACK_RPM_POST_INSTALL_SCRIPT_FILE "${CMAKE_SOURCE_DIR}/scripts/postinst;")

include(CPack)

