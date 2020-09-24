set(TEST_SUITE_EXTERNALS_DIR "" CACHE PATH
    "Directory containing test-suite external benchmark sources")

# Find path containing an external benchmark and set PATHVAR to it.
# Specifically this:
# - Adds a CACHE variable for PATHVAR
# - If PATHVAR is unset set it to the first existing directory in this list:
#   - ${TEST_SUITE_EXTERNALS_DIR}/${NAME}
#   - ${CMAKE_SOURCE_DIR}/test-suite-externals/${NAME}
function(llvm_externals_find PATHVAR NAME DESCRIPTION)
  set(${PATHVAR} "" CACHE PATH "Directory containing ${DESCRIPTION} sourcecode")
  if(NOT ${PATHVAR})
    if(TEST_SUITE_EXTERNALS_DIR)
      if (IS_DIRECTORY "${TEST_SUITE_EXTERNALS_DIR}/${NAME}")
        set(${PATHVAR} "${TEST_SUITE_EXTERNALS_DIR}/${NAME}" PARENT_SCOPE)
      endif()
    else()
      if(IS_DIRECTORY "${CMAKE_SOURCE_DIR}/test-suite-externals/${NAME}")
        set(${PATHVAR} "${CMAKE_SOURCE_DIR}/test-suite-externals/${NAME}"
            PARENT_SCOPE)
      endif()
    endif()
    if(${PATHVAR})
      message(STATUS "Found ${DESCRIPTION}: ${${PATHVAR}}")
    endif()
  endif()
endfunction()
