cmake_minimum_required(VERSION 3.8)
include(${cpp_lib_build_scripts_path}/cmake-module/setup.cmake)
include(target_import_base)

set(ProjectName sync-time)
project(${ProjectName})

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_C_STANDARD 17)

add_executable(${ProjectName})
target_import_src(${ProjectName})

target_link_libraries(${ProjectName} PUBLIC -Wl,--start-group)
target_import_base(${ProjectName} PUBLIC)
target_link_libraries(${ProjectName} PUBLIC
						libPocoNet
						libPocoUtil
						libPocoFoundation)
target_link_libraries(${ProjectName} PUBLIC -Wl,--end-group)


set(CMAKE_INSTALL_PREFIX ${cpp_lib_build_scripts_path}/${platform}/.libs/${ProjectName}/)
