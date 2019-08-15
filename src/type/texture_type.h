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

#ifndef TERRA_TYPE_TEXTURE_TYPE_H_
#define TERRA_TYPE_TEXTURE_TYPE_H_

#include "../../include/type/exception.h"

namespace terra {

	namespace type {

		#define TERRA_TYPE_TEXTURE_HEADER "[TERRA::TYPE::TEXTURE]"
#ifndef NDEBUG
		#define TERRA_TYPE_TEXTURE_EXCEPTION_HEADER TERRA_TYPE_TEXTURE_HEADER " "
#else
		#define TERRA_TYPE_TEXTURE_EXCEPTION_HEADER
#endif // NDEBUG

		enum {
			TERRA_TYPE_TEXTURE_EXCEPTION_EXTERNAL = 0,
			TERRA_TYPE_TEXTURE_EXCEPTION_FORMAT_INVALID,
			TERRA_TYPE_TEXTURE_EXCEPTION_PIXEL_INVALID,
			TERRA_TYPE_TEXTURE_EXCEPTION_TYPE_INVALID,
			TERRA_TYPE_TEXTURE_EXCEPTION_ZOOM_INVALID,
		};

		#define TERRA_TYPE_TEXTURE_EXCEPTION_MAX TERRA_TYPE_TEXTURE_EXCEPTION_ZOOM_INVALID

		static const std::string TERRA_TYPE_TEXTURE_EXCEPTION_STR[] = {
			TERRA_TYPE_TEXTURE_EXCEPTION_HEADER "External exception",
			TERRA_TYPE_TEXTURE_EXCEPTION_HEADER "Invalid format",
			TERRA_TYPE_TEXTURE_EXCEPTION_HEADER "Invalid pixel",
			TERRA_TYPE_TEXTURE_EXCEPTION_HEADER "Invalid type",
			TERRA_TYPE_TEXTURE_EXCEPTION_HEADER "Invalid zoom",
			};

		#define TERRA_TYPE_TEXTURE_EXCEPTION_STRING(_TYPE_) \
			(((_TYPE_) > TERRA_TYPE_TEXTURE_EXCEPTION_MAX) ? STRING_UNKNOWN : \
				STRING(TERRA_TYPE_TEXTURE_EXCEPTION_STR[_TYPE_]))

		#define THROW_TERRA_TYPE_TEXTURE_EXCEPTION(_EXCEPT_) \
			THROW_TERRA_TYPE_TEXTURE_EXCEPTION_FORMAT(_EXCEPT_, "", "")
		#define THROW_TERRA_TYPE_TEXTURE_EXCEPTION_FORMAT(_EXCEPT_, _FORMAT_, ...) \
			THROW_EXCEPTION(TERRA_TYPE_TEXTURE_EXCEPTION_STRING(_EXCEPT_), _FORMAT_, __VA_ARGS__)
	}
}

#endif // TERRA_TYPE_TEXTURE_TYPE_H_
