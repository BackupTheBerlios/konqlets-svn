INCLUDES = $(all_includes)
METASOURCES = AUTO

kde_module_LTLIBRARIES = libkonqletsplugin.la
libkonqletsplugin_la_SOURCES = konqletsplugin.cpp
libkonqletsplugin_la_LIBADD = $(LIB_KHTML) -lkonq
libkonqletsplugin_la_LDFLAGS = -module $(KDE_PLUGIN) $(all_libraries)

pluginsdir = $(kde_datadir)/khtml/kpartplugins
plugins_DATA = konqletsplugin.rc

appsdir = $(kde_appsdir)/.hidden
apps_DATA = konqletsplugin.desktop

messages: rc.cpp
	$(XGETTEXT) *.cpp *.h -o $(podir)/konqletsplugin.pot
