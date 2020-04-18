# Set C compiler options
if (NOT CODE_COVERAGE)
	set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -g")
	set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -O3")
endif(NOT CODE_COVERAGE)

add_executable(fixmydl main.c)
target_compile_options(fixmydl PUBLIC -Wall -Werror -Wno-unused-function -pedantic)

target_link_libraries(fixmydl PUBLIC coverage_config)
