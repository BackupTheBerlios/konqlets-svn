INCLUDES    = $(all_includes)

kde_module_LTLIBRARIES = kio_javascript.la

kio_javascript_la_SOURCES = javascript.cpp
kio_javascript_la_LIBADD = -lkio        
kio_javascript_la_LDFLAGS = -module -avoid-version $(all_libraries) $(KDE_PLUGIN)

protocol_DATA = javascript.protocol
protocoldir = $(kde_servicesdir)

messages: rc.cpp
	$(XGETTEXT) *.cpp -o $(podir)/kio_javascript.pot
