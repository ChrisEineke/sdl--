bin_PROGRAMS = test
test_SOURCES = test_suite.cpp
test_CPPFLAGS = \
		-Wall \
		-Wextra \
		-I$(top_srcdir)/include \
		`sdl-config --cflags`
test_LDADD = ../src/libSDL++.la
test_LDFLAGS = `sdl-config --libs` `cppunit-config --libs`
