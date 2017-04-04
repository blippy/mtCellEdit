AM_CXXFLAGS = `pkg-config --cflags pango` \
	      `pkg-config --cflags cairo`
#include		../_conf.txt

#LIB_SONAME	= $(LIB_NAME).1
lib_LTLIBRARIES = libmtcedui.la
libmtcedui_la_LDFLAGS = --version-info 1
HEADER		= mtcedui.h
libmtcedui_la_SOURCES	=	\
		cui_clip.cpp	\
		cui_dup.cpp	\
		cui_file.cpp	\
		cui_graph.cpp	\
		cui_prefs.cpp	\
		cui_render.cpp	\
		cui_undo.cpp	


#.PHONY:		all install uninstall clean

#all:		$(LIB_SONAME)

#$(LIB_SONAME):	$(OBJS)
#		$(CXX) -shared -o $(LIB_SONAME) $(OBJS) $(LDFLAGS) -Wl,-soname,$(LIB_SONAME)

#$(OBJS):	*.h

# .c.o Implicit rule
# .cpp.o Implicit rule

#install:
#		install -d $(DESTDIR)$(LIB_INSTALL)
#		install $(LIB_SONAME) $(DESTDIR)$(LIB_INSTALL)/
#		cd $(DESTDIR)$(LIB_INSTALL); ln -sf $(LIB_SONAME) $(LIB_NAME)
#		install -d $(DESTDIR)$(HEAD_INSTALL)
#		install -m 644 $(HEADER) $(DESTDIR)$(HEAD_INSTALL)

#uninstall:
#		rm -f $(DESTDIR)$(LIB_INSTALL)/$(LIB_NAME)
#		rm -f $(DESTDIR)$(LIB_INSTALL)/$(LIB_SONAME)
#		rm -f $(DESTDIR)$(HEAD_INSTALL)/$(HEADER)

#clean:
#		rm -f *.o $(LIB_SONAME)
