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

#ifndef TERRA_TYPE_TEXTURE_H_
#define TERRA_TYPE_TEXTURE_H_

#include "../common.h"

namespace terra {

	namespace type {

		class texture {

			public:

				texture(void);

				virtual ~texture(void);

				const color_t &color(
					__in int type,
					__in uint32_t zoom,
					__in uint32_t x,
					__in uint32_t y
					) const;

				void load(
					__in const std::string &path
					);

				bool loaded(void) const;

				void unload(void);

			protected:

				texture(
					__in const texture &other
					) = delete;

				texture &operator=(
					__in const texture &other
					) = delete;

				color_t pixel(
					__in const SDL_Surface *surface,
					__in uint32_t x,
					__in uint32_t y
					);

				std::vector<std::vector<std::vector<color_t>>> m_tiles;
		};
	}
}

#endif // TERRA_TYPE_TEXTURE_H_
