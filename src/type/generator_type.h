/**
 * Terra
 * Copyright (C) 2019 David Jolly
 *
 * Terra is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Terra is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef TERRA_TYPE_GENERATOR_TYPE_H_
#define TERRA_TYPE_GENERATOR_TYPE_H_

#include "../../include/type/exception.h"

namespace terra {

	namespace type {

		#define TERRA_TYPE_GENERATOR_HEADER "[TERRA::TYPE::GENERATOR]"
#ifndef NDEBUG
		#define TERRA_TYPE_GENERATOR_EXCEPTION_HEADER TERRA_TYPE_GENERATOR_HEADER " "
#else
		#define TERRA_TYPE_GENERATOR_EXCEPTION_HEADER
#endif // NDEBUG

		enum {
			TERRA_TYPE_GENERATOR_EXCEPTION_CONTEXT_INVALID = 0,
		};

		#define TERRA_TYPE_GENERATOR_EXCEPTION_MAX TERRA_TYPE_GENERATOR_EXCEPTION_CONTEXT_INVALID

		static const std::string TERRA_TYPE_GENERATOR_EXCEPTION_STR[] = {
			TERRA_TYPE_GENERATOR_EXCEPTION_HEADER "Invalid context",
			};

		#define TERRA_TYPE_GENERATOR_EXCEPTION_STRING(_TYPE_) \
			(((_TYPE_) > TERRA_TYPE_GENERATOR_EXCEPTION_MAX) ? STRING_UNKNOWN : \
				STRING(TERRA_TYPE_GENERATOR_EXCEPTION_STR[_TYPE_]))

		#define THROW_TERRA_TYPE_GENERATOR_EXCEPTION(_EXCEPT_) \
			THROW_TERRA_TYPE_GENERATOR_EXCEPTION_FORMAT(_EXCEPT_, "", "")
		#define THROW_TERRA_TYPE_GENERATOR_EXCEPTION_FORMAT(_EXCEPT_, _FORMAT_, ...) \
			THROW_EXCEPTION(TERRA_TYPE_GENERATOR_EXCEPTION_STRING(_EXCEPT_), _FORMAT_, __VA_ARGS__)

		enum {
			COLOR_WATER_DEEP = 0,
			COLOR_WATER_SHALLOW,
			COLOR_SAND,
			COLOR_GRASS,
			COLOR_GRASS_DARK,
			COLOR_STONE,
			COLOR_STONE_DARK,
			COLOR_SNOW,
		};

		#define COLOR_MAX COLOR_SNOW

		static const color_t COL[] = {
			{{ 175, 92, 45, 255 }}, // COLOR_WATER_DEEP
			{{ 201, 115, 68, 255 }}, // COLOR_WATER_SHALLOW
			{{ 145, 212, 216, 255 }}, // COLOR_SAND
			{{ 53, 157, 112, 255 }}, // COLOR_GRASS
			{{ 38, 115, 82, 255 }}, // COLOR_GRASS_DARK
			{{ 72, 78, 101, 255 }}, // COLOR_STONE
			{{ 66, 69, 84, 255 }}, // COLOR_STONE_DARK
			{{ 255, 255, 255, 255 }}, // COLOR_SNOW
			};

		#define COLOR(_TYPE_) \
			(((_TYPE_) > COLOR_MAX) ? COL[COLOR_WATER_DEEP] : \
				COL[_TYPE_])

		static const double COL_RANGE[] = {
			0.3, // COLOR_WATER_DEEP
			0.4, // COLOR_WATER_SHALLOW
			0.45, // COLOR_SAND
			0.55, // COLOR_GRASS
			0.6, // COLOR_GRASS_DARK
			0.7, // COLOR_STONE
			0.9, // COLOR_STONE_DARK
			1.0, // COLOR_SNOW
			};

		#define COLOR_RANGE(_TYPE_) \
			(((_TYPE_) > COLOR_MAX) ? COL_RANGE[COLOR_WATER_DEEP] : \
				COL_RANGE[_TYPE_])

		#define OCTAVE_OFFSET_MAX 100000
		#define OCTAVE_OFFSET_MIN -OCTAVE_OFFSET_MAX

		#define SCALE_MIN 0.0001
	}
}

#endif // TERRA_TYPE_GENERATOR_TYPE_H_
