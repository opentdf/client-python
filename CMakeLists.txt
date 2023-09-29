cmake_minimum_required(VERSION 3.10)

project(opentdf_static)

# enable verbose logging
set(CMAKE_VERBOSE_MAKEFILE ON)

if(EXISTS "${CMAKE_BINARY_DIR}/conanbuildinfo.cmake")
  include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
endif()

# set link info
link_directories(
    ${CONAN_LIB_DIRS}
    )

link_libraries(
    ${CONAN_LIBS}
    ${CONAN_SYSTEM_LIBS}
    )

set(TDF_CLIENT_COPY_HEADER copy-tdf-header)
set(TDF_LIB_DIR ../opentdf-cpp/lib)
set(TDF_INCLUDE_DIR ../opentdf-cpp/include)


message(STATUS "Lib output dir: ${TDF_LIB_DIR}")

set(TDF_COMBINED_LIB_SUFFIX _combined)

set(TDF_COMBINED_LIB_FILENAME ${CMAKE_STATIC_LIBRARY_PREFIX}${PROJECT_NAME}${TDF_COMBINED_LIB_SUFFIX}${CMAKE_STATIC_LIBRARY_SUFFIX})
message(STATUS "Combined lib name: ${TDF_COMBINED_LIB_FILENAME}")
set(TDF_COMBINED_LIB_FULL_PATH ${TDF_LIB_DIR}/${TDF_COMBINED_LIB_FILENAME})
message(STATUS "Combined full path: ${TDF_COMBINED_LIB_FULL_PATH}")    
message(STATUS "Building combine lib: ${TDF_COMBINED_LIB_FILENAME}")

# Copy client-cpp headers
add_custom_command(OUTPUT ${TDF_CLIENT_COPY_HEADER}
COMMAND ${CMAKE_COMMAND} -E copy_directory
  ${CONAN_INCLUDE_DIRS_OPENTDF-CLIENT} ${TDF_INCLUDE_DIR}
COMMENT "Copying opentdf cpp header..."
VERBATIM
)

if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin" OR ${CMAKE_SYSTEM_NAME} MATCHES "iOS")

  FOREACH (LDIR ${CONAN_LIB_DIRS})
    set(V_COMBINED_LIB_DIRS ${V_COMBINED_LIB_DIRS} -L${LDIR})
  ENDFOREACH(LDIR)

  FOREACH (LNAME ${CONAN_LIBS})
    set(V_COMBINED_LIB_NAMES ${V_COMBINED_LIB_NAMES} -l${LNAME})
  ENDFOREACH(LNAME)

  add_custom_command(OUTPUT ${TDF_COMBINED_LIB_FILENAME}
    COMMAND libtool -static -o ${TDF_COMBINED_LIB_FULL_PATH} ${V_COMBINED_LIB_DIRS} ${V_COMBINED_LIB_NAMES}
    COMMENT "Creating ${TDF_COMBINED_LIB_FILENAME}..."
    VERBATIM
  )

elseif (${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    
  # TODO: Eventually replace ar command with libtool
  # Create a mri file for ar
  set(MRI_FILE  ${CMAKE_CURRENT_BINARY_DIR}/tdf.mri)

  file(WRITE ${MRI_FILE} "create  ${TDF_COMBINED_LIB_FULL_PATH}\n")
  file(APPEND ${MRI_FILE} "addlib ${CONAN_LIB_DIRS_OPENTDF-CLIENT}/libopentdf_static.a\n")
  file(APPEND ${MRI_FILE} "addlib ${CONAN_LIB_DIRS_BOOST}/libboost_regex.a\n")
  file(APPEND ${MRI_FILE} "addlib ${CONAN_LIB_DIRS_BOOST}/libboost_iostreams.a\n")
  file(APPEND ${MRI_FILE} "addlib ${CONAN_LIB_DIRS_OPENSSL}/libcrypto.a\n")
  file(APPEND ${MRI_FILE} "addlib ${CONAN_LIB_DIRS_OPENSSL}/libssl.a\n")
  file(APPEND ${MRI_FILE} "addlib ${CONAN_LIB_DIRS_LIBXML2}/libxml2.a\n")
  file(APPEND ${MRI_FILE} "addlib ${CONAN_LIB_DIRS_ZLIB}/libz.a\n")
  file(APPEND ${MRI_FILE} "addlib ${CONAN_LIB_DIRS_LIBICONV}/libiconv.a\n")
  file(APPEND ${MRI_FILE} "save\n")
  file(APPEND ${MRI_FILE} "end\n")

  message(STATUS "mri file ${MRI_FILE}")
  add_custom_command(OUTPUT ${TDF_COMBINED_LIB_FILENAME}
    COMMAND  ar -M < ${MRI_FILE}
    COMMENT "Combining libs and creating ${TDF_COMBINED_LIB_FILENAME}..."
    VERBATIM
  )

elseif (${CMAKE_SYSTEM_NAME} MATCHES "Windows")

  FOREACH (LDIR ${CONAN_LIB_DIRS})
    set(V_COMBINED_LIB_DIRS ${V_COMBINED_LIB_DIRS} /LIBPATH:${LDIR})
  ENDFOREACH(LDIR)
  message(STATUS "combined lib dirs: ${V_COMBINED_LIB_DIRS}")

  FOREACH (LNAME ${CONAN_LIBS})
      set(V_COMBINED_LIB_NAMES ${V_COMBINED_LIB_NAMES} "${LNAME}.lib")
  ENDFOREACH(LNAME)
  message(STATUS "combined lib names: ${V_COMBINED_LIB_NAMES}")
  message(STATUS "Config mode: $<CONFIG>")

  add_custom_command(
    COMMENT "Generating libs for Windows"
    OUTPUT ${TDF_COMBINED_LIB_FILENAME}
    COMMAND if exist ${TDF_LIB_DIR}/$<CONFIG>/${TDF_STATIC_LIB_FILENAME} (
        lib -out:${TDF_LIB_DIR}/$<CONFIG>/${TDF_COMBINED_LIB_FILENAME} ${TDF_LIB_DIR}/$<CONFIG>/${TDF_STATIC_LIB_FILENAME} ${V_COMBINED_LIB_DIRS} ${V_COMBINED_LIB_NAMES}
      ) else (
        lib -out:${TDF_LIB_DIR}/${TDF_COMBINED_LIB_FILENAME} ${TDF_LIB_DIR}/${TDF_STATIC_LIB_FILENAME} ${V_COMBINED_LIB_DIRS} ${V_COMBINED_LIB_NAMES}
      )
    VERBATIM
  )
else()
  message(STATUS "${CMAKE_SYSTEM_NAME} - unknown system FIXME........")
endif()

add_custom_target(combinedLib ALL
    COMMAND echo "This is ALL target ${TDF_COMBINED_LIB_FILENAME}, and it depends on ${TEST_FILE}"
    DEPENDS ${TDF_COMBINED_LIB_FILENAME}
    DEPENDS ${TDF_CLIENT_COPY_HEADER}
    VERBATIM
)