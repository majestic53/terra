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

#ifndef TERRA_TYPE_H_
#define TERRA_TYPE_H_

#include "../include/type/exception.h"

namespace terra {

	#define TERRA_HEADER "[TERRA]"
#ifndef NDEBUG
	#define TERRA_EXCEPTION_HEADER TERRA_HEADER " "
#else
	#define TERRA_EXCEPTION_HEADER
#endif // NDEBUG

	enum {
		TERRA_EXCEPTION_EXTERNAL = 0,
	};

	#define TERRA_EXCEPTION_MAX TERRA_EXCEPTION_EXTERNAL

	static const std::string TERRA_EXCEPTION_STR[] = {
		TERRA_EXCEPTION_HEADER "External exception",
		};

	#define TERRA_EXCEPTION_STRING(_TYPE_) \
		(((_TYPE_) > TERRA_EXCEPTION_MAX) ? STRING_UNKNOWN : \
			STRING(TERRA_EXCEPTION_STR[_TYPE_]))

	#define THROW_TERRA_EXCEPTION(_EXCEPT_) \
		THROW_TERRA_EXCEPTION_FORMAT(_EXCEPT_, "", "")
	#define THROW_TERRA_EXCEPTION_FORMAT(_EXCEPT_, _FORMAT_, ...) \
		THROW_EXCEPTION(TERRA_EXCEPTION_STRING(_EXCEPT_), _FORMAT_, __VA_ARGS__)

	enum {
		KEY_RIGHT = 0,
		KEY_LEFT,
		KEY_UP,
		KEY_DOWN,
	};

	#define KEY_MAX KEY_DOWN

	static const SDL_Scancode KEY_VAL[] = {
		SDL_SCANCODE_D, // KEY_RIGHT
		SDL_SCANCODE_A, // KEY_LEFT
		SDL_SCANCODE_W, // KEY_UP
		SDL_SCANCODE_S, // KEY_DOWN
		};

	#define KEY_VALUE(_TYPE_) \
		(((_TYPE_) > KEY_MAX) ? SDL_SCANCODE_UNKNOWN : \
			KEY_VAL[_TYPE_])

	#define KEY_RESET SDL_SCANCODE_SPACE

	#define SDL_FLAGS (SDL_INIT_VIDEO)
}

#endif // TERRA_TYPE_H_
