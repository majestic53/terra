# Terra
# Copyright (C) 2019 David Jolly
#
# Terra is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# Terra is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.

DIR_BIN=../bin/
DIR_BIN_LIB=../bin/lib/
DIR_BUILD=../build/
DIR_TOOL=./
EXE=terra
EXE_FLAGS=
FLAGS=-march=native -std=c++17 -Wall -Werror
LIB=libterra.a
LIB_FLAGS=-lSDL2 -lSDL2main

all: launcher

### LAUNCHER ###

launcher:
	@echo ''
	@echo '--- BUILDING LAUNCHER ----------------------'
	$(CXX) $(FLAGS) $(BUILD_FLAGS) $(TRACE_FLAGS) $(DIR_TOOL)launcher.cpp $(DIR_BIN_LIB)$(LIB) -o $(DIR_BIN)$(EXE) $(EXE_FLAGS) $(LIB_FLAGS)
	@echo '--- DONE -----------------------------------'
