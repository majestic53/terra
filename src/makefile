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

DIR_BIN_INC=../bin/include/
DIR_BIN_LIB=../bin/lib/
DIR_BUILD=../build/
DIR_INC=../include/
DIR_INC_TYPE=../include/type/
DIR_SRC=./
DIR_SRC_TYPE=./type/
FLAGS=-march=native -std=c++17 -Wall -Werror
LIB=libterra.a

all: build archive

### LIBRARY ###

archive:
	@echo ''
	@echo '--- BUILDING LIBRARY -----------------------'
	ar rcs $(DIR_BIN_LIB)$(LIB) $(DIR_BUILD)base_terra.o \
		$(DIR_BUILD)type_exception.o $(DIR_BUILD)type_trace.o
	cp $(DIR_INC)terra.h $(DIR_BIN_INC)
	@echo '--- DONE -----------------------------------'

build: build_base build_type

### BASE ###

build_base: base_terra.o

base_terra.o: $(DIR_SRC)terra.cpp $(DIR_INC)terra.h
	$(CXX) $(FLAGS) $(BUILD_FLAGS) $(TRACE_FLAGS) -c $(DIR_SRC)terra.cpp -o $(DIR_BUILD)base_terra.o

### TYPE ###

build_type: type_exception.o type_trace.o

type_exception.o: $(DIR_SRC_TYPE)exception.cpp $(DIR_INC_TYPE)exception.h
	$(CXX) $(FLAGS) $(BUILD_FLAGS) $(TRACE_FLAGS) -c $(DIR_SRC_TYPE)exception.cpp -o $(DIR_BUILD)type_exception.o

type_trace.o: $(DIR_SRC_TYPE)trace.cpp $(DIR_INC_TYPE)trace.h
	$(CXX) $(FLAGS) $(BUILD_FLAGS) $(TRACE_FLAGS) -c $(DIR_SRC_TYPE)trace.cpp -o $(DIR_BUILD)type_trace.o