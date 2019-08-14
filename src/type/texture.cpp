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

#include "../../include/type/texture.h"
#include "../../include/type/trace.h"
#include "./texture_type.h"

namespace terra {

	namespace type {

		texture::texture(void)
		{
			TRACE_ENTRY();
			TRACE_EXIT();
		}

		texture::~texture(void)
		{
			TRACE_ENTRY();
			TRACE_EXIT();
		}

		const color_t &
		texture::color(
			__in int type,
			__in uint32_t zoom,
			__in uint32_t x,
			__in uint32_t y
			) const
		{
			size_t index;

			TRACE_ENTRY_FORMAT("Type=%i, Zoom=%u, X=%u, Y=%u", type, zoom, x, y);

			if(zoom >= m_tiles.size()) {
				THROW_TERRA_TYPE_TEXTURE_EXCEPTION_FORMAT(TERRA_TYPE_TEXTURE_EXCEPTION_ZOOM_INVALID, "%u", zoom);
			}

			const std::vector<std::vector<color_t>> &tile = m_tiles.at(zoom);

			if(type >= tile.size()) {
				THROW_TERRA_TYPE_TEXTURE_EXCEPTION_FORMAT(TERRA_TYPE_TEXTURE_EXCEPTION_TYPE_INVALID, "%i", type);
			}

			const std::vector<color_t> &pixels = tile.at(type);

			index = ((y * zoom) + x);
			if(index >= pixels.size()) {
				THROW_TERRA_TYPE_TEXTURE_EXCEPTION_FORMAT(TERRA_TYPE_TEXTURE_EXCEPTION_PIXEL_INVALID, "%u, %u", x, y);
			}

			const color_t &result = pixels.at(index);

			TRACE_EXIT_FORMAT("Result=%p", &result);
			return result;
		}

		void
		texture::load(
			__in const std::string &path
			)
		{
			int zoom;
			SDL_Surface *surface;

			TRACE_ENTRY_FORMAT("Path[%u]=%s", path.size(), STRING(path));

			surface = SDL_LoadBMP(STRING(path));
			if(!surface) {
				THROW_TERRA_TYPE_TEXTURE_EXCEPTION_FORMAT(TERRA_TYPE_TEXTURE_EXCEPTION_EXTERNAL,
					"SDL_LoadBMP failed! %s", SDL_GetError());
			}

			m_tiles.clear();

			for(zoom = ZOOM_MIN; zoom <= ZOOM_MAX; ++zoom) {
				int type = COLOR_MIN;
				uint32_t magnification;
				std::vector<std::vector<color_t>> tiles;

				for(; type <= COLOR_MAX; ++type) {
					std::vector<color_t> tile;
					uint32_t tile_x, tile_y = 0, x, y = 0;

					for(; tile_y < TILE_WIDTH; ++tile_y) {

						for(tile_x = 0; tile_x < TILE_WIDTH; ++tile_x) {
							tile.push_back(pixel(surface, tile_x + (type * TILE_WIDTH), tile_y));
						}
					}

					tiles.push_back(std::vector<color_t>());
					magnification = std::pow(2, zoom);

					for(; y < magnification; ++y) {

						for(x = 0; x < magnification; ++x) {
							color_t color;

							// TODO
							color = tile.at((y * TILE_WIDTH) + x);
							// ---

							tiles.back().push_back(color);
						}
					}
				}

				m_tiles.push_back(tiles);
			}

			SDL_FreeSurface(surface);

			TRACE_EXIT();
		}

		bool
		texture::loaded(void) const
		{
			bool result;

			TRACE_ENTRY();

			result = !m_tiles.empty();

			TRACE_EXIT_FORMAT("Result=%x", result);
			return result;
		}

		color_t
		texture::pixel(
			__in const SDL_Surface *surface,
			__in uint32_t x,
			__in uint32_t y
			)
		{
			color_t result = COLOR_BACKGROUND;

			TRACE_ENTRY_FORMAT("Surface=%p, X=%u, Y=%u", surface, x, y);

			if(surface) {
				result.raw = ((uint32_t *)surface->pixels)[(y * ((COLOR_MAX + 1) * TILE_WIDTH)) + x];
			}

			TRACE_EXIT();
			return result;
		}

		void
		texture::unload(void)
		{
			TRACE_ENTRY();

			m_tiles.clear();

			TRACE_EXIT();
		}
	}
}
