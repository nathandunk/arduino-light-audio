/*
** Copyright (c) 2002-2016, Erik de Castro Lopo <erikd@mega-nerd.com>
** All rights reserved.
**
** This code is released under 2-clause BSD license. Please see the
** file at : https://github.com/libsndfile/libsamplerate/blob/master/COPYING
*/

/* Name of package */
#define PACKAGE "libsamplerate"

/* Version number of package */
#define VERSION "0.1.9"

/* Target processor clips on negative float to int conversion. */
#define CPU_CLIPS_NEGATIVE 0

/* Target processor clips on positive float to int conversion. */
#define CPU_CLIPS_POSITIVE 0

/* Target processor is big endian. */
#define CPU_IS_BIG_ENDIAN 0

/* Target processor is little endian. */
#define CPU_IS_LITTLE_ENDIAN 1

/* Define to 1 if you have the `alarm' function. */
#define HAVE_ALARM 0

/* Define to 1 if you have the <alsa/asoundlib.h> header file. */
#define HAVE_ALSA 0

/* Set to 1 if you have libfftw3. */
#define HAVE_FFTW3 0

/* Define if you have C99's lrint function. */
#define HAVE_LRINT 0

/* Define if you have C99's lrintf function. */
#define HAVE_LRINTF 0

/* Define if you have signal SIGALRM. */
#define HAVE_SIGALRM 0

/* Define to 1 if you have the `signal' function. */
#define HAVE_SIGNAL 1

/* Set to 1 if you have libsndfile. */
#define HAVE_SNDFILE 0

/* Define to 1 if you have the <stdbool.h> header file. */
#define HAVE_STDBOOL_H

/* Define to 1 if you have the <stdint.h> header file. */
#define HAVE_STDINT_H 1

/* Define to 1 if you have the <sys/times.h> header file. */
#define HAVE_SYS_TIMES_H 0

/* Set to 1 if compiling for Win32 */
#define OS_IS_WIN32 1

/* define fast samplerate convertor */
#define ENABLE_SINC_FAST_CONVERTER

/* define balanced samplerate convertor */
#define ENABLE_SINC_MEDIUM_CONVERTER

/* define best samplerate convertor */
#define ENABLE_SINC_BEST_CONVERTER

/* The size of `int', as computed by sizeof. */
#define SIZEOF_INT 

/* The size of `long', as computed by sizeof. */
#define SIZEOF_LONG 
