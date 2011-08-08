
# Copyright (c) 2011 Stefan Eilemann <eile@eyescale.ch>

if(DOXYGEN_FOUND)
  if(EQUALIZER_RELEASE)
    set(EQ_DOXYGEN_VERSION ${SHORT_VERSION})
    set(CO_DOXYGEN_VERSION ${CO_VERSION})
  else()
    set(EQ_DOXYGEN_VERSION ${SHORT_VERSION}-git)
    set(CO_DOXYGEN_VERSION ${CO_VERSION}-git)
  endif()

  configure_file(doc/DoxygenLayout.xml
    ${CMAKE_CURRENT_BINARY_DIR}/DoxygenLayout.xml @ONLY)
  configure_file(doc/doxyfooter.html
    ${CMAKE_CURRENT_BINARY_DIR}/doxyfooter.html @ONLY)
  configure_file(doc/Doxyfile.ext
    ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile.ext @ONLY)
  configure_file(doc/Doxyfile.int
    ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile.int @ONLY)
  configure_file(doc/Doxyfile.co
    ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile.co @ONLY)
  configure_file(doc/Doxyfile.seq
    ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile.seq @ONLY)

  get_property(INSTALL_DEPENDS GLOBAL PROPERTY ALL_TARGETS)
  add_custom_target(doxygen_install
    ${CMAKE_COMMAND} -D CMAKE_INSTALL_PREFIX=install -P cmake_install.cmake
    DEPENDS ${INSTALL_DEPENDS})

  # Note: packages are chained by depends to enforce serial execution.
  #       Doxygen is not multiprocess-safe when running in the same directory.
  add_custom_target(doxygen_int
    ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile.int
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    COMMENT "Generating internal API documentation using doxygen" VERBATIM)

  add_custom_target(doxygen_co
    ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile.co
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    DEPENDS doxygen_int doxygen_install
    COMMENT "Generating Collage API documentation using doxygen" VERBATIM)

  add_custom_target(doxygen_seq
    ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile.seq
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    DEPENDS doxygen_co doxygen_install
    COMMENT "Generating Sequel API documentation using doxygen" VERBATIM)

  add_custom_target(doxygen_ext
    ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile.ext
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    DEPENDS doxygen_seq doxygen_install
    COMMENT "Generating Equalizer API documentation using doxygen" VERBATIM)

  # set_target_properties(tests PROPERTIES FOLDER "Tests")
  add_custom_target(doxygen DEPENDS doxygen_ext doxygen_int doxygen_co)
  make_directory(${CMAKE_CURRENT_BINARY_DIR}/man/man3)
  install(DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/man/man3 DESTINATION man
          COMPONENT man PATTERN "*_docs_*" EXCLUDE)
endif()