AM_CFLAGS = -Wall
bin_PROGRAMS = monorun
monorun_SOURCES = monorun.c player.c roland.c vector.c
monorun_LDADD = $(SDL2_LIBS) $(SDL2_image_LIBS) $(SDL2_ttf_LIBS)

EXTRA_DIST = monorun.h player.h roland.h vector.h

monorun_CFLAGS = -g $(SDL2_CFLAGS) $(SDL2_image_CFLAGS) $(SDL2_ttf_CFLAGS)
