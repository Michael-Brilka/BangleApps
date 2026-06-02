cmake_minimum_required(VERSION 3.10)

project(HistoriographerDecoder VERSION 2.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Quellcodedateien (kann auch mit Glob verwendet werden, aber nicht empfohlen)
set(SOURCES
    Decoder.cpp
    BangleJSMath.cpp
    DecodeData.cpp
	DecodeGlobal.cpp
	ReadFromData.cpp
)

# Executable erstellen
add_executable(HistoriographerDecoder ${SOURCES})
