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

#ifndef TERRA_COMMON_MACRO_H_
#define TERRA_COMMON_MACRO_H_

#define _AS_STRING(_STRING_) \
	# _STRING_
#define AS_STRING(_STRING_) \
	_AS_STRING(_STRING_)

#define LEVEL_STRING(_TYPE_) \
	(((_TYPE_) > LEVEL_MAX) ? STRING_UNKNOWN : \
		STRING(LEVEL_STR[_TYPE_]))

#define STRING(_STRING_) \
	((_STRING_).empty() ? STRING_EMPTY : (_STRING_).c_str())

#ifdef TRACE_COLOR
#define LEVEL_COLOR_STRING(_TYPE_) \
	(((_TYPE_) > LEVEL_MAX) ? LEVEL_COLOR_STR[LEVEL_NONE] : \
		STRING(LEVEL_COLOR_STR[_TYPE_]))
#define STRING_COLOR(_LEVEL_) \
	LEVEL_COLOR_STRING(_LEVEL_)
#else
#define STRING_COLOR(_LEVEL_)
#endif // TRACE_COLOR

#define _STRING_COLUMN(_WIDTH_) \
	std::left << std::setw(_WIDTH_)
#define STRING_COLUMN() \
	_STRING_COLUMN(COLUMN_WIDTH)

#define _STRING_FLOAT(_PRECISION_, _VALUE_) \
	std::right << std::setprecision(_PRECISION_) << std::fixed << (_VALUE_) << std::defaultfloat
#define STRING_FLOAT(_VALUE_) \
	_STRING_FLOAT(FLOAT_PRECISION, _VALUE_)

#define STRING_HEXIDECIMAL(_TYPE_, _VALUE_) \
	std::right << std::setw(sizeof(_TYPE_) * 2) << std::setfill('0') << std::hex << (uintmax_t) ((_TYPE_) (_VALUE_)) \
		<< std::dec << std::setfill(' ')

#define THROW_EXCEPTION(_MESSAGE_, _FORMAT_, ...) \
	terra::type::exception::generate(_MESSAGE_, __FILE__, __FUNCTION__, __LINE__, _FORMAT_, __VA_ARGS__)

#ifndef NDEBUG
#define _TRACE(_LEVEL_, _PREFIX_, _MESSAGE_, _FILE_, _FUNCTION_, _LINE_, _FORMAT_, ...) { \
		if((_LEVEL_) <= (TRACE)) { \
			terra::type::trace::generate(_LEVEL_, _PREFIX_, _MESSAGE_, _FILE_, _FUNCTION_, _LINE_, \
				_FORMAT_, __VA_ARGS__); \
		} \
	}
#else
#define _TRACE(_LEVEL_, _PREFIX_, _MESSAGE_, _FILE_, _FUNCTION_, _LINE_, _FORMAT_, ...)
#endif // NDEBUG

#define TRACE_ENTRY() \
	TRACE_ENTRY_FORMAT("", "")
#define TRACE_ENTRY_FORMAT(_FORMAT_, ...) \
	_TRACE(LEVEL_VERBOSE, "+", __FUNCTION__, __FILE__, __FUNCTION__, __LINE__, _FORMAT_, __VA_ARGS__)

#define TRACE_EXIT() \
	TRACE_EXIT_FORMAT("", "")
#define TRACE_EXIT_FORMAT(_FORMAT_, ...) \
	_TRACE(LEVEL_VERBOSE, "-", __FUNCTION__, __FILE__, __FUNCTION__, __LINE__, _FORMAT_, __VA_ARGS__)

#define TRACE_MESSAGE(_LEVEL_, _MESSAGE_) \
	TRACE_MESSAGE_FORMAT(_LEVEL_, _MESSAGE_, "", "")
#define TRACE_MESSAGE_FORMAT(_LEVEL_, _MESSAGE_, _FORMAT_, ...) \
	_TRACE(_LEVEL_, std::string(), _MESSAGE_, __FILE__, __FUNCTION__, __LINE__, _FORMAT_, __VA_ARGS__)

#define TRACE_ERROR(_MESSAGE_, _FILE_, _FUNCTION_, _LINE_) \
	_TRACE(LEVEL_ERROR, std::string(), _MESSAGE_, _FILE_, _FUNCTION_, _LINE_, "", "")

#define VERSION_STRING() \
	AS_STRING(VERSION_MAJOR) "." AS_STRING(VERSION_MINOR) "." AS_STRING(VERSION_WEEK) "." \
		AS_STRING(VERSION_REVISION) "-" VERSION_RELEASE

#endif // TERRA_COMMON_MACRO_H_
