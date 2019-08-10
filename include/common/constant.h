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

#ifndef TERRA_COMMON_CONSTANT_H_
#define TERRA_COMMON_CONSTANT_H_

#ifndef __in
#define __in
#endif // __in

#ifndef __in_opt
#define __in_opt
#endif // __in_opt

#ifndef __inout
#define __inout
#endif // __inout

#ifndef __inout_opt
#define __inout_opt
#endif // __inout_opt

#ifndef __out
#define __out
#endif // __out

#ifndef __out_opt
#define __out_opt
#endif // __out_opt

#define COLUMN_WIDTH 32

#define FLOAT_PRECISION 2

enum {
	LEVEL_NONE = 0,
	LEVEL_ERROR,
	LEVEL_WARNING,
	LEVEL_INFORMATION,
	LEVEL_VERBOSE,
};

#define LEVEL_MAX LEVEL_VERBOSE

static const std::string LEVEL_COLOR_STR[] = {
	"\x1b[0m", // LEVEL_NONE
	"\x1b[91m", // LEVEL_ERROR
	"\x1b[93m", // LEVEL_WARNING
	"\x1b[94m", // LEVEL_INFORMATION
	"\x1b[90m", // LEVEL_VERBOSE
	};

static const std::string LEVEL_STR[] = {
	"", // LEVEL_NONE
	"Error", // LEVEL_ERROR
	"Warning", // LEVEL_WARNING
	"Information", // LEVEL_INFORMATION
	"Verbose", // LEVEL_VERBOSE
	};

#define STRING_EMPTY ""
#define STRING_UNKNOWN "Unknown"

#define TERRA "Terra"
#define TERRA_NOTICE "Copyright (C) 2019 David Jolly"

#define VERSION_MAJOR 0
#define VERSION_MINOR 1
#define VERSION_RELEASE "alpha"
#define VERSION_REVISION 1
#define VERSION_WEEK 1932

#endif // TERRA_COMMON_CONSTANT_H_
