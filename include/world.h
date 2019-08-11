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

#ifndef TERRA_WORLD_H_
#define TERRA_WORLD_H_

#include "./interface/world.h"
#include "./type/display.h"
#include "./type/generator.h"

namespace terra {

	class world :
			public terra::type::singleton<terra::world>,
			public terra::interface::world {

		public:

			~world(void);

			terra::type::display &display(void);

			terra::type::generator &generator(void);

			void move(
				__in int32_t x,
				__in int32_t y
				);

			void reset(void);

			void update(void);

			void zoom(
				__in int32_t z
				);

		protected:

			friend class terra::type::singleton<terra::world>;

			world(void);

			world(
				__in const world &other
				) = delete;

			world &operator=(
				__in const world &other
				) = delete;

			const terra_t &configuration(void) override;

			void occlude(
				__inout color_t &color,
				__in double height,
				__in int32_t x,
				__in int32_t y
				);

			void on_initialize(
				__in const void *context
				) override;

			void on_uninitialize(void) override;

			void render(void);

			void texture(
				__inout color_t &color,
				__in double height,
				__in int32_t x,
				__in int32_t y
				);

			const terra_t *m_configuration;

			terra::type::display &m_display;

			terra::type::generator &m_generator;

			std::pair<int32_t, int32_t> m_position;

			std::pair<std::pair<int32_t, int32_t>, std::pair<int32_t, int32_t>> m_range;

			bool m_update;

			int32_t m_zoom;
	};
}

#endif // TERRA_WORLD_H_
