macro(get_sources SOURCE_LIST DIR)
    set(FOLDER_NAMES main simulation util)
    add_sources(${SOURCE_LIST} "${DIR}/sources" "${FOLDER_NAMES}")
endmacro()