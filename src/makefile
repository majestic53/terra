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
	ar rcs $(DIR_BIN_LIB)$(LIB) $(DIR_BUILD)base_terra.o $(DIR_BUILD)base_world.o \
		$(DIR_BUILD)type_display.o $(DIR_BUILD)type_exception.o $(DIR_BUILD)type_generator.o $(DIR_BUILD)type_perlin.o \
			$(DIR_BUILD)type_texture.o $(DIR_BUILD)type_trace.o
	cp $(DIR_INC)terra.h $(DIR_BIN_INC)
	@echo '--- DONE -----------------------------------'

build: build_base build_type

### BASE ###

build_base: base_terra.o base_world.o

base_terra.o: $(DIR_SRC)terra.cpp $(DIR_INC)terra.h
	$(CXX) $(FLAGS) $(BUILD_FLAGS) $(TRACE_FLAGS) -c $(DIR_SRC)terra.cpp -o $(DIR_BUILD)base_terra.o

base_world.o: $(DIR_SRC)world.cpp $(DIR_INC)world.h
	$(CXX) $(FLAGS) $(BUILD_FLAGS) $(TRACE_FLAGS) -c $(DIR_SRC)world.cpp -o $(DIR_BUILD)base_world.o

### TYPE ###

build_type: type_display.o type_exception.o type_generator.o type_perlin.o type_texture.o type_trace.o

type_display.o: $(DIR_SRC_TYPE)display.cpp $(DIR_INC_TYPE)display.h
	$(CXX) $(FLAGS) $(BUILD_FLAGS) $(TRACE_FLAGS) -c $(DIR_SRC_TYPE)display.cpp -o $(DIR_BUILD)type_display.o

type_exception.o: $(DIR_SRC_TYPE)exception.cpp $(DIR_INC_TYPE)exception.h
	$(CXX) $(FLAGS) $(BUILD_FLAGS) $(TRACE_FLAGS) -c $(DIR_SRC_TYPE)exception.cpp -o $(DIR_BUILD)type_exception.o

type_generator.o: $(DIR_SRC_TYPE)generator.cpp $(DIR_INC_TYPE)generator.h
	$(CXX) $(FLAGS) $(BUILD_FLAGS) $(TRACE_FLAGS) -c $(DIR_SRC_TYPE)generator.cpp -o $(DIR_BUILD)type_generator.o

type_perlin.o: $(DIR_SRC_TYPE)perlin.cpp $(DIR_INC_TYPE)perlin.h
	$(CXX) $(FLAGS) $(BUILD_FLAGS) $(TRACE_FLAGS) -c $(DIR_SRC_TYPE)perlin.cpp -o $(DIR_BUILD)type_perlin.o

type_texture.o: $(DIR_SRC_TYPE)texture.cpp $(DIR_INC_TYPE)texture.h
	$(CXX) $(FLAGS) $(BUILD_FLAGS) $(TRACE_FLAGS) -c $(DIR_SRC_TYPE)texture.cpp -o $(DIR_BUILD)type_texture.o

type_trace.o: $(DIR_SRC_TYPE)trace.cpp $(DIR_INC_TYPE)trace.h
	$(CXX) $(FLAGS) $(BUILD_FLAGS) $(TRACE_FLAGS) -c $(DIR_SRC_TYPE)trace.cpp -o $(DIR_BUILD)type_trace.o
