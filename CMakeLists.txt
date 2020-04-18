cmake_minimum_required(VERSION 3.15)

project("fixmydownloads" VERSION 0.0.1)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/CMake" ${CMAKE_MODULE_PATH})

# Code Coverage Configuration
add_library(coverage_config INTERFACE)

option(CODE_COVERAGE "Enable coverage reporting" OFF)
if(CODE_COVERAGE)
  # Add required flags (GCC & LLVM/Clang)
  target_compile_options(coverage_config INTERFACE
    -O0        # no optimization
    -g         # generate debug info
    --coverage # sets all required flags
  )
	target_link_libraries(coverage_config INTERFACE --coverage)
endif(CODE_COVERAGE)

add_subdirectory(src)

enable_testing()
add_subdirectory(tests)

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

