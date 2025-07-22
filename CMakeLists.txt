cmake_minimum_required(VERSION 3.15...4.0)

project(
	igni-samples
	VERSION 0.2.2
	LANGUAGES C
)

add_executable(
	igni-samples
	src/cmd/cmdline.c
	src/main.c
	src/hitbox.c
	src/cqp_cast.c
	src/load_model.c
)

find_library(LIBM m)
find_library(LIBSUP sup)
find_library(LIBCQP cqp)

target_link_libraries(igni-samples ${LIBCQP} ${LIBM} ${LIBSUP})

set(ASSETS_DIR_SRC "${PROJECT_SOURCE_DIR}/igni-samples")

install(DIRECTORY ${ASSETS_DIR_SRC} DESTINATION "/usr/share")
install(TARGETS igni-samples)
include(CPack)

