find_path(LIBNOVA_INCLUDE_DIR NAMES libnova/libnova.h)
# Найти требуемую библиотеку в системных путях. Префиксы/суффиксы (lib*,*.so,…) подставляются автоматически.
find_library(LIBNOVA_LIBRARY NAMES nova)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(LIBNOVA LIBNOVA_INCLUDE_DIR LIBNOVA_LIBRARY)

if(LIBNOVA_FOUND AND NOT TARGET libnova::libnova)
    # Импортированная библиотека, т.е. не собираемая этой системой сборки.
    # Тип (статическая/динамическая) не известен – может быть любым, смотря что нашлось.
    add_library(libnova::libnova UNKNOWN IMPORTED)
    set_target_properties(libnova::libnova PROPERTIES
        INTERFACE_INCLUDE_DIRECTORIES "${LIBNOVA_INCLUDE_DIR}"
        # Указать имя файла собранной внешне библиотеки.
        IMPORTED_LOCATION "${LIBNOVA_LIBRARY}"
        # Указать язык библиотеки на случай, когда она статическая.
        IMPORTED_LINK_INTERFACE_LANGUAGES "C"
    )
endif()

mark_as_advanced(LIBNOVA_INCLUDE_DIR LIBNOVA_LIBRARY)
