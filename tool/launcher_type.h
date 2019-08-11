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

#ifndef TERRA_TOOL_LAUNCHER_TYPE_H_
#define TERRA_TOOL_LAUNCHER_TYPE_H_

#include "../include/type/exception.h"

namespace terra {

	namespace tool {

		#define ARGUMENT_DELIMITER "-"

		enum {
			ARGUMENT_HELP = 0,
			ARGUMENT_VERSION,
		};

		#define ARGUMENT_MAX ARGUMENT_VERSION
		#define ARGUMENT_MIN 1

		static const std::string ARGUMENT_DESC[] = {
			"Display help information", // ARGUMENT_HELP
			"Display version information", // ARGUMENT_VERSION
			};

		#define ARGUMENT_DESCRIPTION(_TYPE_) \
			(((_TYPE_) > ARGUMENT_MAX) ? STRING_UNKNOWN : \
				STRING(ARGUMENT_DESC[_TYPE_]))

		static const std::string ARGUMENT_LNG[] = {
			ARGUMENT_DELIMITER ARGUMENT_DELIMITER "help", // ARGUMENT_HELP
			ARGUMENT_DELIMITER ARGUMENT_DELIMITER "version", // ARGUMENT_VERSION
			};

		#define ARGUMENT_LONG(_TYPE_) \
			(((_TYPE_) > ARGUMENT_MAX) ? STRING_UNKNOWN : \
				STRING(ARGUMENT_LNG[_TYPE_]))

		static const std::string ARGUMENT_SHT[] = {
			ARGUMENT_DELIMITER "h", // ARGUMENT_HELP
			ARGUMENT_DELIMITER "v", // ARGUMENT_VERSION
			};

		#define ARGUMENT_SHORT(_TYPE_) \
			(((_TYPE_) > ARGUMENT_MAX) ? STRING_UNKNOWN : \
				STRING(ARGUMENT_SHT[_TYPE_]))

		static const std::map<std::string, int> ARGUMENT_MAP = {
			std::make_pair(ARGUMENT_LONG(ARGUMENT_HELP), ARGUMENT_HELP), // ARGUMENT_HELP
			std::make_pair(ARGUMENT_LONG(ARGUMENT_VERSION), ARGUMENT_VERSION), // ARGUMENT_VERSION
			// ---
			std::make_pair(ARGUMENT_SHORT(ARGUMENT_HELP), ARGUMENT_HELP), // ARGUMENT_HELP
			std::make_pair(ARGUMENT_SHORT(ARGUMENT_VERSION), ARGUMENT_VERSION), // ARGUMENT_VERSION
			};

		#define ARGUMENT_SUPPORTED(_STRING_) \
			(ARGUMENT_MAP.find(_STRING_) != ARGUMENT_MAP.end())

		#define ARGUMENT_TYPE(_STRING_) \
			ARGUMENT_MAP.find(_STRING_)->second

		#define DISPLAY_HEIGHT 256
		#define DISPLAY_WIDTH 256

		#define GENERATOR_LACUNARITY 2.0
		#define GENERATOR_OCTAVES 4
		#define GENERATOR_OFFSET_X 0
		#define GENERATOR_OFFSET_Y 0
		#define GENERATOR_PERSISTANCE 0.5
		#define GENERATOR_SCALE 50.0

		#define USAGE "terra [args] seed"
	}
}

#endif // TERRA_TOOL_LAUNCHER_TYPE_H_
