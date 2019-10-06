cmake_minimum_required(VERSION 3.15)

project(helloWorld)

add_executable (helloWorld
	main.cpp
	SceneDelegate.cpp)

set_target_properties(helloWorld PROPERTIES
	CXX_STANDARD 14)

set(USD_DIST_ROOT "${CMAKE_SOURCE_DIR}/../../install-pybuild-opt")
#set(USD_DIST_ROOT "${CMAKE_SOURCE_DIR}/../../install-pybuild-dbg")
#set(USD_DIST_ROOT "${CMAKE_SOURCE_DIR}/../../install-${CMAKE_BUILD_TYPE}")
set(USD_INC_DIR "${USD_DIST_ROOT}/include")
set(USD_LIB_DIR "${USD_DIST_ROOT}/lib")

target_include_directories(helloWorld PUBLIC ${USD_INC_DIR})
target_link_libraries(helloWorld PRIVATE
	${USD_LIB_DIR}/libarch.so
	${USD_LIB_DIR}/libar.so
	${USD_LIB_DIR}/libcameraUtil.so
	${USD_LIB_DIR}/libgarch.so
	${USD_LIB_DIR}/libgf.so
	${USD_LIB_DIR}/libglf.so
	${USD_LIB_DIR}/libhd.so
	${USD_LIB_DIR}/libhdSt.so
	${USD_LIB_DIR}/libhdx.so
	${USD_LIB_DIR}/libhf.so
	${USD_LIB_DIR}/libhio.so
	${USD_LIB_DIR}/libjs.so
	${USD_LIB_DIR}/libkind.so
	${USD_LIB_DIR}/libndr.so
	${USD_LIB_DIR}/libpcp.so
	${USD_LIB_DIR}/libplug.so
	${USD_LIB_DIR}/libpxOsd.so
	${USD_LIB_DIR}/libsdf.so
	${USD_LIB_DIR}/libsdr.so
	${USD_LIB_DIR}/libtf.so
	${USD_LIB_DIR}/libtrace.so
	${USD_LIB_DIR}/libusdAppUtils.so
	${USD_LIB_DIR}/libusdGeom.so
	${USD_LIB_DIR}/libusdHydra.so
	${USD_LIB_DIR}/libusdImagingGL.so
	${USD_LIB_DIR}/libusdImaging.so
	${USD_LIB_DIR}/libusdLux.so
	${USD_LIB_DIR}/libusdRi.so
	${USD_LIB_DIR}/libusdShaders.so
	${USD_LIB_DIR}/libusdShade.so
	${USD_LIB_DIR}/libusdSkelImaging.so
	${USD_LIB_DIR}/libusdSkel.so
	${USD_LIB_DIR}/libusd.so
	${USD_LIB_DIR}/libusdUI.so
	${USD_LIB_DIR}/libusdUtils.so
	${USD_LIB_DIR}/libusdviewq.so
	${USD_LIB_DIR}/libusdVolImaging.so
	${USD_LIB_DIR}/libusdVol.so
	${USD_LIB_DIR}/libvt.so
	${USD_LIB_DIR}/libwork.so)

set_target_properties(${PROJECT_NAME} PROPERTIES
		INSTALL_RPATH "\$ORIGIN;${USD_LIB_DIR}"
		INSTALL_RPATH_USE_LINK_PATH FALSE
		SKIP_RPATH FALSE
		BUILD_WITH_INSTALL_RPATH TRUE)

find_package(Python2 COMPONENTS Development)
target_include_directories(helloWorld PUBLIC ${Python2_INCLUDE_DIR})
target_link_libraries(helloWorld PRIVATE ${Python2_LIBRARY_RELEASE})

find_package(Boost COMPONENTS python27)
target_link_libraries(helloWorld PRIVATE Boost::python27)

find_package(OpenGL)
target_link_libraries(helloWorld PRIVATE ${OPENGL_LIBRARIES} OpenGL::GL)

if (CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
	set (CMAKE_INSTALL_PREFIX "${CMAKE_BINARY_DIR}/../install")
	message(STATUS "Set default install prefix: ${CMAKE_INSTALL_PREFIX}")
endif()

install(TARGETS helloWorld RUNTIME DESTINATION bin)
