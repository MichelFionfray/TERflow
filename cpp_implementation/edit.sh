#!/bin/bash
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
files=" \
  flow.cpp \
  Graph.hpp \
  Graph.cpp \
  Edge.hpp \
  Edge.cpp \
  Node.hpp \
  Node.cpp \
  enum.hpp \
  makefile \
"
vim -p $files
