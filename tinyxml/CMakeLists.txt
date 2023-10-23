cmake_minimum_required(VERSION 3.17)

project(sandbox)

include_directories(/usr/local/include)

set (builder_SRC
    builder.cpp
)

set (parser_SRC
    parser.cpp
)

add_executable( builder ${builder_SRC} )

target_link_libraries( builder tinyxml pthread)

add_executable( parser ${parser_SRC} )

target_link_libraries( parser tinyxml pthread)