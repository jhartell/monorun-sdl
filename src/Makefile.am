AM_CFLAGS = -Wall
bin_PROGRAMS = monorun
monorun_SOURCES = monorun.c player.c roland.c vector.c
monorun_LDADD = $(GL_LIBS) $(SDL2_LIBS) $(SDL2_image_LIBS)

EXTRA_DIST = monorun.h player.h roland.h

monorun_CFLAGS = -g $(GL_CFLAGS) $(SDL2_CFLAGS) $(SDL2_image_CFLAGS)
