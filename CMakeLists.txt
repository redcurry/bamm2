CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
PROJECT(BAMM2 CXX)

# Set compiler flags
SET(CXX_DEBUG_FLAGS "-g")
SET(CXX_WARNING_FLAGS "-Wall -Wextra")
SET(CXX_OPTIMIZATION_FLAGS "-O3")

# Support Mac OS X 32-bit and 64-bit architectures (if using Clang)
IF(APPLE AND (${CMAKE_CXX_COMPILER_ID} MATCHES Clang))
    SET(CXX_ARCHITECTURE_FLAGS "-arch i386 -arch x86_64")
ENDIF(APPLE AND (${CMAKE_CXX_COMPILER_ID} MATCHES Clang))

ADD_DEFINITIONS(${CXX_DEBUG_FLAGS}
                ${CXX_WARNING_FLAGS}
                ${CXX_OPTIMIZATION_FLAGS}
                ${CXX_ARCHITECTURE_FLAGS})

SET(BAMM2_LIBRARY_SRC
    source/core/Event.cc
    source/core/Event.h
    source/core/EventMover.cc
    source/core/EventMover.h
    source/core/MCMC.cc
    source/core/MCMC.h
    source/core/Model.cc
    source/core/Model.h
    source/core/ModelProposal.cc
    source/core/ModelProposal.h
    source/core/Node.cc
    source/core/Node.h
    source/core/Proposer.h
    source/core/Random.cc
    source/core/Random.h
    source/core/Tree.cc
    source/core/Tree.h
    source/core/UniformProposer.cc
    source/core/UniformProposer.h)

SET(BAMM2_LIBRARY_NAME bamm2lib)
ADD_LIBRARY(${BAMM2_LIBRARY_NAME} STATIC ${BAMM2_LIBRARY_SRC})

SET(BAMM2_APP_SRC source/app/bamm2.cc)

SET(BAMM2_APP_NAME bamm2)
ADD_EXECUTABLE(${BAMM2_APP_NAME} ${BAMM2_APP_SRC})

TARGET_LINK_LIBRARIES(${BAMM2_APP_NAME} ${BAMM2_LIBRARY_NAME})
