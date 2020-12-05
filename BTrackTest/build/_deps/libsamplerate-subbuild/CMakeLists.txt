# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.14.0-rc2)

# We name the project and the target for the ExternalProject_Add() call
# to something that will highlight to the user what we are working on if
# something goes wrong and an error message is produced.

project(libsamplerate-populate NONE)

include(ExternalProject)
ExternalProject_Add(libsamplerate-populate
                     "UPDATE_DISCONNECTED" "False" "GIT_REPOSITORY" "https://github.com/libsndfile/libsamplerate.git"
                    SOURCE_DIR          "C:/Git/arduino-light-audio/BTrackTest/build/_deps/libsamplerate-src"
                    BINARY_DIR          "C:/Git/arduino-light-audio/BTrackTest/build/_deps/libsamplerate-build"
                    CONFIGURE_COMMAND   ""
                    BUILD_COMMAND       ""
                    INSTALL_COMMAND     ""
                    TEST_COMMAND        ""
                    USES_TERMINAL_DOWNLOAD  YES
                    USES_TERMINAL_UPDATE    YES
)
