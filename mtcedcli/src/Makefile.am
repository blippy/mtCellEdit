AM_CXXFLAGS = -I$(top_srcdir)/libmtkit/src \
	      -I$(top_srcdir)/libmtcedui/src \
	      -I$(top_srcdir)/libmtcelledit/src

#include		../_conf.txt

bin_PROGRAMS = mtcedcli
mtcedcli_SOURCES = 		\
		cli_clipboard.cpp	\
		cli_edit.cpp	\
		cli_file.cpp	\
		cli_main.cpp	\
		cli_misc.cpp	\
		cli_parse.cpp	\
		cli_prefs.cpp	\
		cli_sheet.cpp	\
		cli_sort.cpp	\
		cli_tab.cpp	


#.PHONY:		all install uninstall clean

#all:		$(BIN_NAME)

#$(BIN_NAME):	$(OBJS)
#		$(CXX) $(OBJS) -o $(BIN_NAME) $(LDFLAGS)

#$(OBJS):	*.h

## .c.o Implicit rule
## .cpp.o Implicit rule

#install:
#		install -d $(DESTDIR)$(BIN_INSTALL)
#		install $(BIN_NAME) $(DESTDIR)$(BIN_INSTALL)

#uninstall:
#		rm $(DESTDIR)$(BIN_INSTALL)/$(BIN_NAME)

#clean:
#		rm -f $(BIN_NAME) *.o
