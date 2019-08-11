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

#ifndef TERRA_TYPE_GENERATOR_H_
#define TERRA_TYPE_GENERATOR_H_

#include "../interface/world.h"
#include "./perlin.h"
#include "./singleton.h"

namespace terra {

	namespace type {

		class generator :
				public terra::type::singleton<terra::type::generator>,
				public std::vector<double> {

			public:

				~generator(void);

				void generate(
					__in terra::interface::world &world
					);

				terra::type::perlin &perlin(void);

			protected:

				friend class terra::type::singleton<terra::type::generator>;

				generator(void);

				generator(
					__in const generator &other
					) = delete;

				generator &operator=(
					__in const generator &other
					) = delete;

				void on_initialize(
					__in const void *context
					) override;

				void on_uninitialize(void) override;

				terra::type::perlin m_perlin;
		};
	}
}

#endif // TERRA_TYPE_GENERATOR_H_
