AM_CXXFLAGS = -I$(top_srcdir)/libmtkit/src \
	     `pkg-config --cflags pango` \
	      `pkg-config --cflags cairo`

#include		../_conf.txt

#LIB_SONAME	= $(LIB_NAME).1
#HEADER		= mtpixy.h

lib_LTLIBRARIES = libmtpixy.la
libmtpixy_la_LDFLAGS = -version-info 1
libmtpixy_la_SOURCES	=	\
		px_blit.cpp	\
		px_brush.cpp	\
		px_convert.cpp	\
		px_effects.cpp	\
		px_file.cpp	\
		px_file_bmp.cpp	\
		px_file_gif.cpp	\
		px_file_jpeg.cpp	\
		px_file_png.cpp	\
		px_floodfill.cpp	\
		px_font.cpp	\
		px_image.cpp	\
		px_impal.cpp	\
		px_overlay.cpp	\
		px_paint.cpp	\
		px_palette.cpp	\
		px_paste.cpp	\
		px_polygon.cpp	\
		px_quantize.cpp	\
		px_scale.cpp	\
		px_text.cpp	


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
