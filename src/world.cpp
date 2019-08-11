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

#include "../include/world.h"
#include "./world_type.h"

namespace terra {

	world::world(void) :
		m_configuration(nullptr),
		m_display(terra::type::display::instance()),
		m_generator(terra::type::generator::instance()),
		m_update(false),
		m_zoom(ZOOM_MIN)
	{
		TRACE_ENTRY();
		TRACE_EXIT();
	}

	world::~world(void)
	{
		TRACE_ENTRY();
		TRACE_EXIT();
	}

	const terra_t &
	world::configuration(void)
	{
		TRACE_ENTRY();

		if(!m_configuration) {
			THROW_TERRA_WORLD_EXCEPTION(TERRA_WORLD_EXCEPTION_CONTEXT_INVALID);
		}

		TRACE_EXIT_FORMAT("Result=%p", m_configuration);
		return *m_configuration;
	}

	terra::type::display &
	world::display(void)
	{
		TRACE_ENTRY();
		TRACE_EXIT_FORMAT("Result=%p", &m_display);
		return m_display;
	}

	terra::type::generator &
	world::generator(void)
	{
		TRACE_ENTRY();
		TRACE_EXIT_FORMAT("Result=%p", &m_generator);
		return m_generator;
	}

	void
	world::move(
		__in int32_t x,
		__in int32_t y
		)
	{
		TRACE_ENTRY_FORMAT("X=%i, Y=%i", x, y);

		// TODO: SET m_position/m_range

		m_update = true;

		TRACE_EXIT();
	}

	void
	world::on_initialize(
		__in const void *context
		)
	{
		std::stringstream title;

		TRACE_ENTRY_FORMAT("Context=%p", context);

		TRACE_MESSAGE(LEVEL_INFORMATION, "World initializing");

		m_configuration = (const terra_t *)context;
		if(!m_configuration) {
			THROW_TERRA_WORLD_EXCEPTION(TERRA_WORLD_EXCEPTION_CONTEXT_INVALID);
		}

		m_position = std::make_pair(m_configuration->width / 2, m_configuration->height / 2);
		m_range = std::make_pair(std::make_pair(0, m_configuration->width), std::make_pair(0, m_configuration->height));
		m_zoom = ZOOM_MIN;

		m_generator.initialize(m_configuration);
		m_height = m_generator.generate(*this);

		m_display.initialize(m_configuration);

		title << TERRA << " " << VERSION_STRING() << " (Seed:" << m_generator.perlin().seed() << ")";

		m_display.set_title(title.str());
		m_update = true;

		TRACE_MESSAGE(LEVEL_INFORMATION, "World initialized");

		TRACE_EXIT();
	}

	void
	world::on_uninitialize(void)
	{
		TRACE_ENTRY();

		TRACE_MESSAGE(LEVEL_INFORMATION, "World uninitializing");

		m_update = false;
		m_display.uninitialize();

		m_height.clear();
		m_generator.uninitialize();

		m_zoom = ZOOM_MIN;
		m_range = std::make_pair(std::make_pair(0, 0), std::make_pair(0, 0));
		m_position = std::make_pair(0, 0);

		m_configuration = nullptr;

		TRACE_MESSAGE(LEVEL_INFORMATION, "World uninitialized");

		TRACE_EXIT();
	}

	void
	world::render(void)
	{
		uint32_t pixel_x, pixel_y;

		TRACE_ENTRY();

		for(pixel_y = m_range.second.first; pixel_y < m_range.second.second; ++pixel_y) {

			for(pixel_x = m_range.first.first; pixel_x < m_range.first.second; ++pixel_x) {
				double sample;
				color_t color = {};
				int type = COLOR_WATER_DEEP;
				uint32_t subpixel_x, subpixel_y = 0;

				if((pixel_x != m_position.first) || (pixel_y != m_position.second)) {
					sample = m_height.at((pixel_y * m_configuration->width) + pixel_x);

					for(; type <= COLOR_MAX; ++type) {

						if((sample >= COLOR_RANGE(type - 1)) && (sample <= COLOR_RANGE(type))) {
							break;
						}
					}
				} else {
					type = COLOR_PLAYER;
				}

				color = COLOR(type);

				for(; subpixel_y < m_zoom; ++subpixel_y) {

					for(subpixel_x = 0; subpixel_x < m_zoom; ++subpixel_x) {
						m_display.set_pixel(color, ((pixel_x - m_range.first.first) * m_zoom) + subpixel_x,
							((pixel_y - m_range.second.first) * m_zoom) + subpixel_y);
					}
				}
			}
		}

		TRACE_EXIT();
	}

	void
	world::update(void)
	{
		TRACE_ENTRY();

		if(m_update) {
			m_update = false;
			render();
		}

		m_display.show(*this);

		TRACE_EXIT();
	}

	void
	world::zoom(
		__in int32_t z
		)
	{
		uint32_t center_x, center_y, height, width;

		TRACE_ENTRY_FORMAT("Z=%i", z);

		m_zoom += z;
		if(m_zoom > ZOOM_MAX) {
			m_zoom = ZOOM_MAX;
		} else if(m_zoom < ZOOM_MIN) {
			m_zoom = ZOOM_MIN;
		}

		width = (m_configuration->width / m_zoom);
		height = (m_configuration->height / m_zoom);

		center_x = (width / 2);
		center_y = (height / 2);

		m_range = std::make_pair(std::make_pair(m_position.first - center_x, m_position.first + center_x),
				std::make_pair(m_position.second - center_y, m_position.second + center_y));

		m_update = true;

		TRACE_EXIT();
	}
}
