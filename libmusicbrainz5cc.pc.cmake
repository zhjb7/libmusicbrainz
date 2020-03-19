prefix=${CMAKE_INSTALL_PREFIX}
exec_prefix=${EXEC_INSTALL_PREFIX}
libdir=${LIB_INSTALL_DIR}
includedir=${INCLUDE_INSTALL_DIR}

Name: ${PROJECT_NAME}cc
Description: The Musicbrainz Client Library.
URL: http://musicbrainz.org/doc/libmusicbrainz
Version: ${PROJECT_VERSION}
Requires.private: neon >= 0.25 libxml-2.0 gss-1.0.3
Libs: -L${LIB_INSTALL_DIR} -lmusicbrainz5cc
Cflags: -I${INCLUDE_INSTALL_DIR}

