cmake_minimum_required(VERSION 3.12.2)

project("DeuteriumC")

# BEGIN configuration

set(DTC_SRC_DIR "src/"    ) # Source file directory
set(DTC_INC_DIR "inc/") # Include directory
set(DTC_TEST_DIR "test/")

# END configuration

set(DTC_TGT dtc)
set(DTC_DEF_PFX DTC)

file(GLOB_RECURSE DTC_SRC "${DTC_SRC_DIR}*.c")
file(GLOB_RECURSE DTC_INC "${DTC_INC_DIR}*.h" "${DTC_SRC_DIR}*.h")

add_library(${DTC_TGT} STATIC ${DTC_SRC} ${DTC_INC})



# Add DTC definition
target_compile_definitions(${DTC_TGT} PRIVATE ${DTC_DEF_PFX})

# Handle build in debug mode
if(DEBUG)
    message("Building in debug mode...")
    set(CMAKE_BUILD_TYPE Debug)
    target_compile_definitions(${DTC_TGT} PRIVATE "${DTC_DEF_PFX}_DEBUG")
    target_compile_definitions(${DTC_TGT} PRIVATE "${DTC_DEF_PFX}_SAFE")
else()
    message("Building in release mode...")
    set(CMAKE_BUILD_TYPE Release)
    target_compile_definitions(${DTC_TGT} PRIVATE "${DTC_DEF_PFX}_RELEASE")
endif()

# Use C 17
set_property(TARGET ${DTC_TGT} PROPERTY C_STANDARD 17)

# Include directories
target_include_directories(${DTC_TGT} PUBLIC "${DTC_INC_DIR}/")

# Include internal/common.h
target_compile_options(${DTC_TGT} PRIVATE -include internal/common.h)

# Testing

include(CTest)

add_executable(dtc_test_str test/str.c)

target_link_libraries(dtc_test_str ${DTC_TGT})

add_test(NAME dtc_test_str COMMAND dtc_test_str)
