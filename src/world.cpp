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

	void
	world::crosshair(void)
	{
		int32_t center_x, center_y, x, y = -CROSSHAIR_WIDTH;

		TRACE_ENTRY();

		center_x = (m_configuration->width / 2);
		center_y = (m_configuration->height / 2);

		for(; y <= CROSSHAIR_WIDTH; ++y) {

			for(x = -CROSSHAIR_WIDTH; x <= CROSSHAIR_WIDTH; ++x) {

				if(!x || !y) {
					m_display.set_pixel(COLOR_CROSSHAIR, x + center_x, y + center_y);
				}
			}
		}

		TRACE_EXIT();
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
		std::pair<int32_t, int32_t> position;

		TRACE_ENTRY_FORMAT("X=%i, Y=%i", x, y);

		position.first = (m_position.first + x);
		if(position.first < 0) {
			m_position.first = 0;
		} else if(position.first >= m_configuration->width) {
			m_position.first = (m_configuration->width - 1);
		} else {
			m_position.first = position.first;
		}

		position.second = (m_position.second + y);
		if(position.second < 0) {
			m_position.second = 0;
		} else if(position.second >= m_configuration->height) {
			m_position.second = (m_configuration->height - 1);
		} else {
			m_position.second = position.second;
		}

		m_update = true;

		TRACE_EXIT();
	}

	void
	world::occlude(
		__inout color_t &color,
		__in double height,
		__in int32_t x,
		__in int32_t y
		)
	{
		TRACE_ENTRY_FORMAT("Color=%p, Height=%g, X=%i, Y=%i", &color, height, x, y);

		if(height >= OCCLUSION_LIMIT) {
			double average = 0, count = 0;
			int32_t radius_x, radius_x_high, radius_x_low, radius_y, radius_y_high, radius_y_low;

			if(x <= (OCCLUSION_RADIUS - 1)) {

				if(y <= (OCCLUSION_RADIUS - 1)) {
					radius_x_low = 0;
					radius_x_high = OCCLUSION_RADIUS;
					radius_y_low = 0;
					radius_y_high = OCCLUSION_RADIUS;
				} else if(y >= (m_configuration->height - OCCLUSION_RADIUS)) {
					radius_x_low = 0;
					radius_x_high = OCCLUSION_RADIUS;
					radius_y_low = -OCCLUSION_RADIUS;
					radius_y_high = 0;
				} else {
					radius_x_low = 0;
					radius_x_high = OCCLUSION_RADIUS;
					radius_y_low = -OCCLUSION_RADIUS;
					radius_y_high = OCCLUSION_RADIUS;
				}
			} else if(x >= (m_configuration->width - OCCLUSION_RADIUS)) {

				if(y <= (OCCLUSION_RADIUS - 1)) {
					radius_x_low = -OCCLUSION_RADIUS;
					radius_x_high = 0;
					radius_y_low = 0;
					radius_y_high = OCCLUSION_RADIUS;
				} else if(y >= (m_configuration->height - OCCLUSION_RADIUS)) {
					radius_x_low = -OCCLUSION_RADIUS;
					radius_x_high = 0;
					radius_y_low = -OCCLUSION_RADIUS;
					radius_y_high = 0;
				} else {
					radius_x_low = -OCCLUSION_RADIUS;
					radius_x_high = 0;
					radius_y_low = -OCCLUSION_RADIUS;
					radius_y_high = OCCLUSION_RADIUS;
				}
			} else if(y <= (OCCLUSION_RADIUS - 1)) {
				radius_x_low = -OCCLUSION_RADIUS;
				radius_x_high = OCCLUSION_RADIUS;
				radius_y_low = 0;
				radius_y_high = OCCLUSION_RADIUS;
			} else if(y >= (m_configuration->height - OCCLUSION_RADIUS)) {
				radius_x_low = -OCCLUSION_RADIUS;
				radius_x_high = OCCLUSION_RADIUS;
				radius_y_low = -OCCLUSION_RADIUS;
				radius_y_high = 0;
			} else {
				radius_x_low = -OCCLUSION_RADIUS;
				radius_x_high = OCCLUSION_RADIUS;
				radius_y_low = -OCCLUSION_RADIUS;
				radius_y_high = OCCLUSION_RADIUS;
			}

			for(radius_y = radius_y_low; radius_y < radius_y_high; ++radius_y) {

				for(radius_x = radius_x_low; radius_x < radius_x_high; ++radius_x) {

					if(!radius_x && !radius_y) {
						continue;
					}

					average += m_generator.at(((y + radius_y) * m_configuration->width) + (x + radius_x));
					++count;
				}
			}

			average /= count;

			if(height < average) {
				height /= average;
				height *= OCCLUSION_SCALE;

				color.red -= height;
				color.green -= height;
				color.blue -= height;
			}
		}

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
#ifndef DISABLE_TEXTURE
		m_texture.load(TEXTURE_PATH);
#endif // DISABLE_TEXTURE
		m_zoom = ZOOM_MIN;

		m_generator.initialize(m_configuration);
		m_generator.generate(*this);

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

		m_generator.uninitialize();

		m_zoom = ZOOM_MIN;
#ifndef DISABLE_TEXTURE
		m_texture.unload();
#endif // DISABLE_TEXTURE
		m_range = std::make_pair(std::make_pair(0, 0), std::make_pair(0, 0));
		m_position = std::make_pair(0, 0);

		m_configuration = nullptr;

		TRACE_MESSAGE(LEVEL_INFORMATION, "World uninitialized");

		TRACE_EXIT();
	}

	void
	world::render(
		__in uint32_t magnification
		)
	{
		int32_t pixel_x, pixel_y;

		TRACE_ENTRY_FORMAT("Magnification=%u", magnification);

		for(pixel_y = 0; pixel_y < m_configuration->height; ++pixel_y) {

			for(pixel_x = 0; pixel_x < m_configuration->width; ++pixel_x) {
				m_display.set_pixel(COLOR_BACKGROUND, pixel_x, pixel_y);
			}
		}

		for(pixel_y = m_range.second.first; pixel_y < m_range.second.second; ++pixel_y) {

			for(pixel_x = m_range.first.first; pixel_x < m_range.first.second; ++pixel_x) {
				double height;
				color_t color = {};
				int32_t subpixel_x, subpixel_y = 0;

				if((pixel_x < 0) || (pixel_x >= m_configuration->width)
						|| (pixel_y < 0) || (pixel_y >= m_configuration->height)) {
					continue;
				}

				height = m_generator.at((pixel_y * m_configuration->width) + pixel_x);

				for(; subpixel_y < magnification; ++subpixel_y) {

					for(subpixel_x = 0; subpixel_x < magnification; ++subpixel_x) {
						texture(color, height, subpixel_x, subpixel_y);
#ifndef DISABLE_OCCLUSION
						occlude(color, height, pixel_x, pixel_y);
#endif // DISABLE_OCCLUSION
						m_display.set_pixel(color, ((pixel_x - m_range.first.first) * magnification) + subpixel_x,
							((pixel_y - m_range.second.first) * magnification) + subpixel_y);
					}
				}
			}
		}

#ifndef DISABLE_CROSSHAIR
		crosshair();
#endif // DISABLE_CROSSHAIR

		TRACE_EXIT();
	}

	void
	world::regenerate(
		__in uint32_t seed
		)
	{
		std::stringstream title;

		TRACE_ENTRY_FORMAT("Seed=%u(%08x)", seed, seed);

		m_generator.perlin().set_seed(seed);
		m_generator.generate(*this);

		title << TERRA << " " << VERSION_STRING() << " (Seed:" << m_generator.perlin().seed() << ")";
		m_display.set_title(title.str());

		m_update = true;

		TRACE_EXIT();
	}

	void
	world::reset(void)
	{
		TRACE_ENTRY();

		m_position = std::make_pair(m_configuration->width / 2, m_configuration->height / 2);
		m_zoom = ZOOM_MIN;

		m_update = true;

		TRACE_EXIT();
	}

	void
	world::texture(
		__inout color_t &color,
		__in double height,
		__in int32_t x,
		__in int32_t y
		)
	{
		int type = 0;

		TRACE_ENTRY_FORMAT("Color=%p, Height=%g, X=%i, Y=%i", &color, height, x, y);

		for(; type <= COLOR_MAX; ++type) {

			if((height >= COLOR_RANGE(type - 1)) && (height <= COLOR_RANGE(type))) {
				break;
			}
		}

#ifndef DISABLE_TEXTURE
		color = m_texture.color((type <= COLOR_MAX) ? type : COLOR_MIN, m_zoom, x, y);
#else
#ifndef DISABLE_COLOR
		color = COLOR((type <= COLOR_MAX) ? type : COLOR_MIN);
#else
		uint8_t channel = (UINT8_MAX * height);

		color = {{ channel, channel, channel, UINT8_MAX }};
#endif // DISABLE_COLOR
#endif // DISABLE_TEXTURE

		TRACE_EXIT();
	}

	void
	world::update(void)
	{
		TRACE_ENTRY();

		if(m_update) {
			uint32_t magnification;
			int32_t center_x, center_y;

			m_update = false;

			magnification = std::pow(2, m_zoom);
			center_x = ((m_configuration->width / magnification) / 2);
			center_y = ((m_configuration->height / magnification) / 2);

			m_range = std::make_pair(std::make_pair(m_position.first - center_x, m_position.first + center_x),
					std::make_pair(m_position.second - center_y, m_position.second + center_y));

			render(magnification);
		}

		m_display.show(*this);

		TRACE_EXIT();
	}

	void
	world::zoom(
		__in int32_t z
		)
	{
		TRACE_ENTRY_FORMAT("Z=%i", z);

		m_zoom += z;
		if(m_zoom > ZOOM_MAX) {
			m_zoom = ZOOM_MAX;
		} else if(m_zoom < ZOOM_MIN) {
			m_zoom = ZOOM_MIN;
		}

		m_update = true;

		TRACE_EXIT();
	}
}
