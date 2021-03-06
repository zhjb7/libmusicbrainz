INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE(PkgConfig)
PKG_CHECK_MODULES(PKG_GSS gss)

FIND_PATH(GSS_INCLUDE_DIR gss.h
    PATHS
    ${PKG_GSS_INCLUDE_DIRS}
    /usr/include
    /usr/local/include
    PATH_SUFFIXES gss
)

FIND_LIBRARY(GSS_LIBRARIES gss
    ${PKG_GSS_LIBRARY_DIRS}
    /usr/lib
    /usr/local/lib
)

FIND_PACKAGE_HANDLE_STANDARD_ARGS(Gss DEFAULT_MSG GSS_LIBRARIES GSS_INCLUDE_DIR)
