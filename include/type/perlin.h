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

#ifndef TERRA_TYPE_PERLIN_H_
#define TERRA_TYPE_PERLIN_H_

#include "../common.h"

namespace terra {

	namespace type {

		class perlin {

			public:

				perlin(void);

				explicit perlin(
					__in uint32_t seed
					);

				virtual ~perlin(void);

				double sample(
					__in double x,
					__in double y,
					__in_opt double z = 0
					) const;

				void set_seed(
					__in uint32_t seed
					);

			protected:

				perlin(
					__in const perlin &other
					) = delete;

				perlin &operator=(
					__in const perlin &other
					) = delete;

				double fade(
					__in double t
					) const;

				double grad(
					__in int hash,
					__in double x,
					__in double y,
					__in double z
					) const;

				double lerp(
					__in double t,
					__in double a,
					__in double b
					) const;

				std::vector<int> m_permutation;
		};
	}
}

#endif // TERRA_TYPE_PERLIN_H_
