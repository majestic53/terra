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

#ifndef TERRA_INTERFACE_RUNTIME_H_
#define TERRA_INTERFACE_RUNTIME_H_

#include "../common.h"
#include "../terra.h"

namespace terra {

	namespace interface {

		class runtime {

			public:

				virtual const terra_t &configuration(void) = 0;

				virtual void set_pixel(
					__in const color_t &color,
					__in size_t x,
					__in size_t y
					) = 0;
		};
	}
}

#endif // TERRA_INTERFACE_RUNTIME_H_
