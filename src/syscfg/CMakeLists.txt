
# Copyright (c) 2017-2018 the BasicX authors
# All rights reserved.
#
# The project sponsor and lead author is Xu Rendong.
# E-mail: xrd@ustc.edu, QQ: 277195007, WeChat: ustc_xrd
# You can get more information at https://xurendong.github.io
# For names of other contributors see the contributors file.
#
# Commercial use of this code in source and binary forms is
# governed by a LGPL v3 license. You may get a copy from the
# root directory. Or else you should get a specific written 
# permission from the project author.
#
# Individual and educational use of this code in source and
# binary forms is governed by a 3-clause BSD license. You may
# get a copy from the root directory. Certainly welcome you
# to contribute code of all sorts.
#
# Be sure to retain the above copyright notice and conditions.

INCLUDE_DIRECTORIES (${Boost_INCLUDE_DIRS} "${PROJECT_SOURCE_DIR}")

# Boost 的附加库目录会自动添加
IF (CMAKE_LINKTYPE_SHARED)
    IF (MSVC)
        SET (CMAKE_SHARED_LINKER_FLAGS_DEBUG "${CMAKE_SHARED_LINKER_FLAGS_DEBUG} /LIBPATH:\"${PROJECT_BINARY_DIR}/archive/Debug\"")
        SET (CMAKE_SHARED_LINKER_FLAGS_RELEASE "${CMAKE_SHARED_LINKER_FLAGS_RELEASE} /LIBPATH:\"${PROJECT_BINARY_DIR}/archive/Release\"")
    ELSE ()
        LINK_DIRECTORIES (${PROJECT_BINARY_DIR}/archive) # need check
    ENDIF ()
ELSE ()
    IF (MSVC)
        SET (CMAKE_STATIC_LINKER_FLAGS_DEBUG "${CMAKE_STATIC_LINKER_FLAGS_DEBUG} /LIBPATH:\"${PROJECT_BINARY_DIR}/archive/Debug\"")
        SET (CMAKE_STATIC_LINKER_FLAGS_RELEASE "${CMAKE_STATIC_LINKER_FLAGS_RELEASE} /LIBPATH:\"${PROJECT_BINARY_DIR}/archive/Release\"")
    ELSE ()
        LINK_DIRECTORIES (${PROJECT_BINARY_DIR}/archive) # need check
    ENDIF ()
ENDIF ()

FILE (GLOB SYSCFG_HEADER_FILES "./*.h")
FILE (GLOB SYSCFG_SOURCE_FILES "./*.cpp")

SOURCE_GROUP ("Header Files" FILES ${SYSCFG_HEADER_FILES})
SOURCE_GROUP ("Source Files" FILES ${SYSCFG_SOURCE_FILES})

IF (CMAKE_LINKTYPE_SHARED)
    ADD_LIBRARY ("syscfg" SHARED ${SYSCFG_HEADER_FILES} ${SYSCFG_SOURCE_FILES})
    IF (WIN32)
        TARGET_LINK_LIBRARIES ("syscfg" common.lib)
    ELSEIF (UNIX)
        TARGET_LINK_LIBRARIES ("syscfg" common.a)
    ELSEIF (APPLE)
        TARGET_LINK_LIBRARIES ("syscfg" common.a)
    ENDIF ()
ELSE ()
    ADD_LIBRARY ("syscfg" ${SYSCFG_HEADER_FILES} ${SYSCFG_SOURCE_FILES})
ENDIF ()
