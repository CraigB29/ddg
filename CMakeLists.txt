# SPDX-License-Identifier: Apache-2.0

cmake_minimum_required(VERSION 3.20.0)

find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})
project(hello_world)

target_sources(app PRIVATE src/main.c)
target_sources(app PRIVATE src/duck1.c)
target_sources(app PRIVATE src/duck2.c)
target_sources(app PRIVATE src/goose.c)
target_sources(app PRIVATE src/rando_sleep.c)

target_include_directories(app PRIVATE src)
