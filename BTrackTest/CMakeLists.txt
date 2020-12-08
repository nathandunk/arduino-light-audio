cmake_minimum_required(VERSION 3.13)

project(my_proj)

add_definitions(-DUSE_KISS_FFT)

include(FetchContent)
FetchContent_Declare(libsamplerate GIT_REPOSITORY https://github.com/libsndfile/libsamplerate.git)
FetchContent_MakeAvailable(libsamplerate)

# FetchContent_Declare(audio-file GIT_REPOSITORY https://github.com/adamstark/AudioFile.git)
# FetchContent_MakeAvailable(audio-file)

# target_compile_definitions(AudioFile INTERFACE M_PI=3.14159265358979)

include_directories(include)

set(BTRACK_SRC
        src/OnsetDetectionFunction.cpp
        src/kiss_fft.c
        src/BTrack.cpp
)

add_executable(my_app src/main.cpp ${BTRACK_SRC})
target_link_libraries(my_app samplerate)