#-------------------------------------------------
#
# Project created by QtCreator 2014-06-03T08:10:03
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = HuffmanCoding
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
#    data_file.cpp \
    file.cpp \
    tree.cpp \
    node.cpp \
    bitvector.cpp \
    huffman.cpp

HEADERS += \
#    data_file.h \
    file.h \
    tree.h \
    node.h \
    bitvector.h \
    huffman.h
