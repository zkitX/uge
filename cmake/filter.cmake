function(add_executable target)
    # Call the built-in CMake function to add an executable target to the project
    _add_executable(${target} ${ARGN})

    # Call the _add_filters function to organize the executable's source files into folders in the IDE
    _add_filters(${target})
endfunction()

function(_add_filters target)
    # Retrieve the list of source files for the given target
    get_target_property(sources "${target}" SOURCES)

    # Iterate over each source file and group them into folders in the IDE
    foreach(filename IN LISTS sources)
        # Extract the directory path from the source file's path
        get_filename_component(path "${filename}" PATH)

        # Replace forward slashes with backslashes to form a valid folder path in the IDE
        string(REPLACE "/" "\\" group "${path}")

        # Group the file into a folder in the IDE
        source_group("${group}" FILES "${filename}")
    endforeach()
endfunction()

function(add_library target)
    # Call the built-in CMake function to add a library target to the project
    _add_library(${target} ${ARGN})

    # Call the _add_filters function to organize the library's source files into folders in the IDE
    _add_filters(${target})
endfunction()

function(target_precompile_headers target)
    _target_precompile_headers(${target} ${ARGN})

    source_group("pch" REGULAR_EXPRESSION "${filePath}/[^/.]+(.(pch))?.(hxx|cxx)$")
endfunction()