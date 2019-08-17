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

		#define OCTAVE_OFFSET_MAX 100000
		#define OCTAVE_OFFSET_MIN -OCTAVE_OFFSET_MAX
	}
}

#endif // TERRA_TYPE_GENERATOR_TYPE_H_
