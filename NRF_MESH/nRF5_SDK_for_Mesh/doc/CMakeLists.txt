# Add doc target for generating doxygen documentation

find_package(Doxygen)

set(HAVE_DOT "YES")

if (DOXYGEN_FOUND)

    string(TIMESTAMP TODAY "%Y-%m-%d")
    set(PROJECT_DOC_NAME "Bluetooth Mesh SDK")

    # Get latest commit hash for the working branch
    execute_process(
        COMMAND git rev-parse --short HEAD
        WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
        OUTPUT_VARIABLE GIT_HEAD_COMMIT_ID
        OUTPUT_STRIP_TRAILING_WHITESPACE
    )

    set(PROJECT_REPO_PATH "ssh://git@stash.nordicsemi.no:7999/mesh/mesh-btle.git")
    set(CURRENT_USER $ENV{USER})
    set(DOCUMENTATION_DIR offline)

    set(PROJECT_REVISION ${GIT_HEAD_COMMIT_ID})
    # Configure Doxyfiles
    configure_file(
        ${CMAKE_CURRENT_SOURCE_DIR}/doxygen/Doxyfile.in
        ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
    )

    add_custom_target(doc
        COMMAND ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
        SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/doxygen/Doxyfile.in
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        COMMENT "Generating Doxygen documentation..." VERBATIM
    )

    # Configure Doxyfile for building the Infocenter documentation:
    set(PROJECT_DOC_NAME "${PROJECT_DOC_NAME} ${VERSION_STRING}")
    # Project revision is in title
    set(PROJECT_REVISION "")
    set(DOCUMENTATION_DIR infocenter)
    configure_file(
        ${CMAKE_CURRENT_SOURCE_DIR}/doxygen/Doxyfile.in
        ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile-infocenter
    )

    # Build infocenter documentation:
    add_custom_target(doc_online
        COMMAND ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile-infocenter
        SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/doxygen/Doxyfile.in
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        COMMENT "Generating online Doxygen documentation..." VERBATIM
    )

    # Add dependencies for the serial documentation:
    add_dependencies(doc serial_doc_markdown)
    add_dependencies(doc_online serial_doc_markdown)

endif ()

