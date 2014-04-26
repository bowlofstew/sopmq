# SOPMQ - Scalable optionally persistent message queue
# Copyright 2014 InWorldz, LLC
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#    http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

# - Try to find libcql (cassandra C++ driver)
# Once done this will define
#  LIBCQL_FOUND - System has LibCQL
#  LIBCQL_INCLUDE_DIRS - The LibCQL include directories
#  LIBCQL_LIBRARIES - The libraries needed to use LibCQL
#  LIBCQL_DEFINITIONS - Compiler switches required for using LibCQL


find_path(LIBCQL_INCLUDE_DIR cql/cql.hpp
          HINTS
          PATH_SUFFIXES libcql )

find_library(LIBCQL_LIBRARY NAMES cql
             HINTS )


set(LIBCQL_LIBRARIES ${LIBCQL_LIBRARY} )
set(LIBCQL_INCLUDE_DIRS ${LIBCQL_INCLUDE_DIR} )

include(FindPackageHandleStandardArgs)

# handle the QUIETLY and REQUIRED arguments and set LIBCQL_FOUND to TRUE
# if all listed variables are TRUE
find_package_handle_standard_args(LibCQL  DEFAULT_MSG
                                  LIBCQL_LIBRARY LIBCQL_INCLUDE_DIR)

mark_as_advanced(LIBCQL_INCLUDE_DIR LIBCQL_LIBRARY )
