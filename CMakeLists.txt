cmake_minimum_required(VERSION 3.8)
project(
	yo
	VERSION 1.0
	LANGUAGES CXX
)

add_executable(main src/main.cpp)

include(FetchContent)
FetchContent_Declare(cpr GIT_REPOSITORY https://github.com/libcpr/cpr.git)
FetchContent_MakeAvailable(cpr)

find_package(PkgConfig REQUIRED)
pkg_check_modules(JSONCPP jsoncpp)

set(CMAKE_THREAD_PREFER_PTHREAD TRUE)
set(THREADS_PREFER_PTHREAD_FLAG TRUE)
find_package(Threads REQUIRED)


target_link_libraries(main PRIVATE cpr::cpr)
target_link_libraries(main PRIVATE Threads::Threads ${JSONCPP_LIBRARIES})
