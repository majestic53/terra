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

#ifndef TERRA_WORLD_TYPE_H_
#define TERRA_WORLD_TYPE_H_

#include "../include/type/exception.h"

namespace terra {

	#define TERRA_WORLD_HEADER "[TERRA::WORLD]"
#ifndef NDEBUG
	#define TERRA_WORLD_EXCEPTION_HEADER TERRA_WORLD_HEADER " "
#else
	#define TERRA_WORLD_EXCEPTION_HEADER
#endif // NDEBUG

	enum {
		TERRA_WORLD_EXCEPTION_CONTEXT_INVALID = 0,
	};

	#define TERRA_WORLD_EXCEPTION_MAX TERRA_WORLD_EXCEPTION_CONTEXT_INVALID

	static const std::string TERRA_WORLD_EXCEPTION_STR[] = {
		TERRA_WORLD_EXCEPTION_HEADER "Invalid context",
		};

	#define TERRA_WORLD_EXCEPTION_STRING(_TYPE_) \
		(((_TYPE_) > TERRA_WORLD_EXCEPTION_MAX) ? STRING_UNKNOWN : \
			STRING(TERRA_WORLD_EXCEPTION_STR[_TYPE_]))

	#define THROW_TERRA_WORLD_EXCEPTION(_EXCEPT_) \
		THROW_TERRA_WORLD_EXCEPTION_FORMAT(_EXCEPT_, "", "")
	#define THROW_TERRA_WORLD_EXCEPTION_FORMAT(_EXCEPT_, _FORMAT_, ...) \
		THROW_EXCEPTION(TERRA_WORLD_EXCEPTION_STRING(_EXCEPT_), _FORMAT_, __VA_ARGS__)

	//#define OCCLUSION_DISABLE
	#define OCCLUSION_LIMIT COLOR_RANGE(COLOR_WATER_SHALLOW)
	#define OCCLUSION_RADIUS 1
	#define OCCLUSION_SCALE 10

	#define TEXTURE_DISABLE

	#define ZOOM_MAX 6
	#define ZOOM_MIN 0
}

#endif // TERRA_WORLD_TYPE_H_
