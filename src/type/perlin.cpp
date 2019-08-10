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

/**
 * Perlin algorithm implemention based on http://mrl.nyu.edu/~perlin/noise/
 */

#include "../../include/type/perlin.h"
#include "../../include/type/trace.h"
#include "./perlin_type.h"

namespace terra {

	namespace type {

		perlin::perlin(void)
		{
			TRACE_ENTRY();

			std::srand(std::time(nullptr));
			set_seed(std::rand());

			TRACE_EXIT();
		}

		perlin::perlin(
			__in uint32_t seed
			)
		{
			TRACE_ENTRY();

			std::srand(std::time(nullptr));
			set_seed(seed);

			TRACE_EXIT();
		}

		perlin::~perlin(void)
		{
			TRACE_ENTRY();
			TRACE_EXIT();
		}

		double
		perlin::fade(
			__in double t
			) const
		{
			double result;

			TRACE_ENTRY_FORMAT("T=%g", t);

			result = (t * t * t * (t * (t * 6 - 15) + 10));

			TRACE_EXIT_FORMAT("Result=%g", result);
			return result;
		}

		double
		perlin::grad(
			__in int hash,
			__in double x,
			__in double y,
			__in double z
			) const
		{
			int h;
			double result, u, v;

			TRACE_ENTRY_FORMAT("Hash=%i, X=%g, Y=%g, Z=%g}", hash, x, y, z);

			h = (hash & 15);
			u = ((h < 8) ? x : y);
		   	v = ((h < 4) ? y : (((h == 12) || (h == 14)) ? x : z));

			result = (((h & 1) == 0 ? u : -u) + ((h & 2) == 0 ? v : -v));

			TRACE_EXIT_FORMAT("Result=%g", result);
			return result;
		}

		double
		perlin::lerp(
			__in double t,
			__in double a,
			__in double b
			) const
		{
			double result;

			TRACE_ENTRY_FORMAT("T=%g, A=%g, B=%g", t, a, b);

			result = (a + t * (b - a));

			TRACE_EXIT_FORMAT("Result=%g", result);
			return result;
		}

		double
		perlin::noise(
			__in double x,
			__in double y,
			__in double z
			) const
		{
			double result, u, v ,w;
			int a, aa, ab, b, ba, bb, ux, uy, uz;

			TRACE_ENTRY_FORMAT("X=%g, Y=%g, Z=%g}", x, y, z);

			ux = (int) std::floor(x) & UINT8_MAX;
			uy = (int) std::floor(y) & UINT8_MAX;
			uz = (int) std::floor(z) & UINT8_MAX;

			x -= std::floor(x);
			y -= std::floor(y);
			z -= std::floor(z);

			u = fade(x);
			v = fade(y);
			w = fade(z);

			a = (m_permutation.at(ux) + uy);
			aa = (m_permutation.at(a) + uz);
			ab = (m_permutation.at(a + 1) + uz);
			b = (m_permutation.at(ux + 1) + uy);
			ba = (m_permutation.at(b) + uz);
			bb = (m_permutation.at(b + 1) + uz);

			result = lerp(w,
					lerp(v,
						lerp(u, grad(m_permutation.at(aa), x, y, z),
							grad(m_permutation.at(ba), x - 1, y, z)),
						lerp(u, grad(m_permutation.at(ab), x, y - 1, z),
							grad(m_permutation.at(bb), x - 1, y - 1, z))),
					lerp(v, lerp(u, grad(m_permutation.at(aa + 1), x, y, z - 1),
							grad(m_permutation.at(ba + 1), x - 1, y, z - 1)),
						lerp(u, grad(m_permutation.at(ab + 1), x, y - 1, z - 1),
							grad(m_permutation.at(bb + 1), x - 1, y - 1, z - 1))));

			result = ((result + 1.0) / 2.0);

			TRACE_EXIT_FORMAT("Result=%g", result);
			return result;
		}

		void
		perlin::set_seed(
			__in uint32_t seed
			)
		{
			std::mt19937 engine;

			TRACE_ENTRY_FORMAT("Seed=%u(%08x)", seed, seed);

			m_permutation.resize(PERMUTATION_LENGTH);
			std::iota(m_permutation.begin(), m_permutation.end(), 0);

			engine.seed(seed);
			std::shuffle(m_permutation.begin(), m_permutation.end(), engine);

			m_permutation.insert(m_permutation.end(), m_permutation.begin(), m_permutation.end());

			TRACE_EXIT();
		}
	}
}
