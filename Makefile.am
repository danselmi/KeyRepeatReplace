AM_CPPFLAGS = $(WX_CXXFLAGS) \
		-I$(top_srcdir)/src/include \
		-I$(top_srcdir)/src/sdk/wxscintilla/include

pluginlibdir = $(pkglibdir)/plugins

pluginlib_LTLIBRARIES = libKeyRepeatReplace.la

libKeyRepeatReplace_la_LDFLAGS = @MODULE_SHARED_LDFLAGS@ -version-info 0:1:0 -no-undefined -avoid-version

libKeyRepeatReplace_la_LIBADD = ../../../sdk/libcodeblocks.la $(WX_LIBS)

libKeyRepeatReplace_la_SOURCES = KeyRepeatReplace.cpp \
		EditorHookFunctor.cpp \
		KRRConfigPanel.cpp \
		RepeatReplaceConfig.cpp

noinst_HEADERS = KeyRepeatReplace.h \
		EditorHookFunctor.h \
		KRRConfigPanel.h \
		RepeatReplaceConfig.h

resources_forZIP = manifest.xml

EXTRA_DIST = $(srcdir)/*.cbp \
		$(resources_forZIP)

pkgdata_DATA = KeyRepeatReplace.zip

CLEANFILES = $(pkgdata_DATA)

KeyRepeatReplace.zip: $(resources_forZIP)
	PWD=`pwd` cd $(srcdir) && zip $(PWD)/KeyRepeatReplace.zip $(resources_forZIP) > /dev/null
