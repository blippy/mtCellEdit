AM_CXXFLAGS = -I$(top_srcdir)/libmtkit/src

#include		../_conf.txt

#LIB_SONAME	= $(LIB_NAME).1
HEADER		= mtcelledit.h
PARSER		= ced_parser.cpp
PARSER_REPORT	= ced_parser_report.txt
BUILT_SOURCES = ced_parser.cpp
CLEANFILES = $(BUILT_SOURCES)

lib_LTLIBRARIES = libmtcelledit.la
libmtcelledit_la_LDFLAGS = -version-info 1
libmtcelledit_la_SOURCES =	\
		ced_book.cpp	\
		ced_cell.cpp	\
		ced_file.cpp	\
		ced_find.cpp	\
		ced_index.cpp	\
		ced_output.cpp	\
		ced_parser.yy	\
		ced_paste.cpp	\
		ced_sheet.cpp	\
		ced_sort.cpp	\
		ced_token.cpp	\
		ced_transform.cpp	\
		ced_utils.cpp	


ced_parser.cpp : ced_parser.yy

#.PHONY:		all install uninstall clean

#all:		$(LIB_SONAME)

#$(LIB_SONAME):	$(OBJS)
#		$(CXX) -shared -o $(LIB_SONAME) $(OBJS) $(LDFLAGS) -Wl,-soname,$(LIB_SONAME)

#$(OBJS):	*.h

#$(PARSER):	ced_parser.yy ced_parser_def.cpp
#		bison ced_parser.yy -W --report=all --report-file=$(PARSER_REPORT) -o $(PARSER)

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
#		rm -f *.o $(LIB_SONAME) $(PARSER) $(PARSER_REPORT)
