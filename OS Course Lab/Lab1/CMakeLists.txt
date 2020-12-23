# name
project(TestShell)
# src
aux_source_directory(. DIR_SRCS)
# target
add_executable(TestShell ${DIR_SRCS})
