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

#include "../../include/type/display.h"
#include "./display_type.h"

namespace terra {

	namespace type {

		display::display(void) :
			m_frame_frequency(0.f),
			m_frame_rate(0.f),
			m_renderer(nullptr),
			m_texture(nullptr),
			m_width(0),
			m_window(nullptr)
		{
			TRACE_ENTRY();
			TRACE_EXIT();
		}

		display::~display(void)
		{
			TRACE_ENTRY();
			TRACE_EXIT();
		}

		void
		display::clear(
			__in terra::interface::world &world
			)
		{
			TRACE_ENTRY_FORMAT("World=%p", &world);

			m_pixel.resize(m_width * world.configuration().height, COLOR_BACKGROUND);
			show(world);

			TRACE_EXIT();
		}

		float
		display::frame_frequency(void) const
		{
			TRACE_ENTRY();
			TRACE_EXIT_FORMAT("Result=%.01f", m_frame_frequency);
			return m_frame_frequency;
		}

		float
		display::frame_rate(void) const
		{
			TRACE_ENTRY();
			TRACE_EXIT_FORMAT("Result=%.01f", m_frame_rate);
			return m_frame_rate;
		}

		void
		display::on_initialize(
			__in const void *context
			)
		{
			uint32_t height;
			SDL_DisplayMode mode = {};
			const terra_t *configuration;

			TRACE_ENTRY_FORMAT("Context=%p", context);

			TRACE_MESSAGE(LEVEL_INFORMATION, "Display initializing");

			configuration = (const terra_t *)context;
			if(!configuration || !configuration->width || !configuration->height) {
				THROW_TERRA_TYPE_DISPLAY_EXCEPTION(TERRA_TYPE_DISPLAY_EXCEPTION_CONTEXT_INVALID);
			}

			m_width = configuration->width;
			height = configuration->height;

			m_pixel.resize(m_width * height, COLOR_BACKGROUND);
			m_title = TERRA " " VERSION_STRING();

			m_window = SDL_CreateWindow(STRING(m_title), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
					m_width * DISPLAY_SCALE, height * DISPLAY_SCALE, SDL_WINDOW_FLAGS);

			if(!m_window) {
				THROW_TERRA_TYPE_DISPLAY_EXCEPTION_FORMAT(TERRA_TYPE_DISPLAY_EXCEPTION_EXTERNAL,
					"SDL_CreateWindow failed! %s", SDL_GetError());
			}

			m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_FLAGS);
			if(!m_renderer) {
				THROW_TERRA_TYPE_DISPLAY_EXCEPTION_FORMAT(TERRA_TYPE_DISPLAY_EXCEPTION_EXTERNAL,
					"SDL_CreateRenderer failed! %s", SDL_GetError());
			}

			if(SDL_RenderSetLogicalSize(m_renderer, m_width, height)) {
				THROW_TERRA_TYPE_DISPLAY_EXCEPTION_FORMAT(TERRA_TYPE_DISPLAY_EXCEPTION_EXTERNAL,
					"SDL_RenderSetLogicalSize failed! %s", SDL_GetError());
			}

			if(SDL_SetRenderDrawColor(m_renderer,
					COLOR_BACKGROUND.red, COLOR_BACKGROUND.green, COLOR_BACKGROUND.blue, COLOR_BACKGROUND.alpha)) {
				THROW_TERRA_TYPE_DISPLAY_EXCEPTION_FORMAT(TERRA_TYPE_DISPLAY_EXCEPTION_EXTERNAL,
					"SDL_SetRenderDrawColor failed! %s", SDL_GetError());
			}

			if(SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, SDL_RENDERER_QUALITY) == SDL_FALSE) {
				THROW_TERRA_TYPE_DISPLAY_EXCEPTION_FORMAT(TERRA_TYPE_DISPLAY_EXCEPTION_EXTERNAL,
					"SDL_SetHint failed! %s", SDL_GetError());
			}

			m_texture = SDL_CreateTexture(m_renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, m_width, height);
			if(!m_texture) {
				THROW_TERRA_TYPE_DISPLAY_EXCEPTION_FORMAT(TERRA_TYPE_DISPLAY_EXCEPTION_EXTERNAL,
					"SDL_CreateTexture failed! %s", SDL_GetError());
			}

			if(SDL_RenderClear(m_renderer)) {
				THROW_TERRA_TYPE_DISPLAY_EXCEPTION_FORMAT(TERRA_TYPE_DISPLAY_EXCEPTION_EXTERNAL,
					"SDL_RenderClear failed! %s", SDL_GetError());
			}

			SDL_RenderPresent(m_renderer);

			if(!SDL_GetWindowDisplayMode(m_window, &mode)) {
				m_frame_rate = (mode.refresh_rate ? mode.refresh_rate : DISPLAY_FRAME_RATE);
			} else {
				m_frame_rate = DISPLAY_FRAME_RATE;
			}

			m_frame_frequency = (MILLISECONDS_PER_SECOND / m_frame_rate);

			TRACE_MESSAGE_FORMAT(LEVEL_INFORMATION, "Display dimensions", "%ux%ux%u", m_width, height, DISPLAY_SCALE);
			TRACE_MESSAGE_FORMAT(LEVEL_INFORMATION, "Display frequency", "%.1f Hz", m_frame_frequency);
			TRACE_MESSAGE_FORMAT(LEVEL_INFORMATION, "Display rate", "%.1f ms", m_frame_rate);

			TRACE_MESSAGE(LEVEL_INFORMATION, "Display initialized");

			TRACE_EXIT();
		}

		void
		display::on_uninitialize(void)
		{
			TRACE_ENTRY();

			TRACE_MESSAGE(LEVEL_INFORMATION, "Display uninitializing");

			if(m_texture) {
				SDL_DestroyTexture(m_texture);
				m_texture = nullptr;
			}

			if(m_renderer) {
				SDL_DestroyRenderer(m_renderer);
				m_renderer = nullptr;
			}

			if(m_window) {
				SDL_DestroyWindow(m_window);
				m_window = nullptr;
			}

			m_frame_frequency = 0.f;
			m_frame_rate = 0.f;
			m_pixel.clear();
			m_title.clear();

			TRACE_MESSAGE(LEVEL_INFORMATION, "Display uninitialized");

			TRACE_EXIT();
		}

		void
		display::set_pixel(
			__in const color_t &color,
			__in size_t x,
			__in size_t y
			)
		{
			size_t index;

			TRACE_ENTRY_FORMAT("Color=%u(%08x), Position={%u,%u}", color.raw, color.raw, x, y);

			index = ((y * m_width) + x);
			if(index >= m_pixel.size()) {
				THROW_TERRA_TYPE_DISPLAY_EXCEPTION_FORMAT(TERRA_TYPE_DISPLAY_EXCEPTION_PIXEL_INVALID,
					"{%u, %u}", x, y);
			}

			m_pixel.at(index).raw = color.raw;

			TRACE_EXIT();
		}

		void
		display::set_frame_rate(
			__in float frame_rate
			)
		{
			std::stringstream result;

			TRACE_ENTRY_FORMAT("Frame-Rate=%.01f", frame_rate);

			result << m_title << " [" << STRING_FLOAT(frame_rate) << " fps]";
			SDL_SetWindowTitle(m_window, STRING(result.str()));

			TRACE_EXIT();
		}

		void
		display::set_title(
			__in const std::string &title
			)
		{
			TRACE_ENTRY_FORMAT("Title[%u]=%s", title.size(), STRING(title));

			m_title = title;
			SDL_SetWindowTitle(m_window, STRING(m_title));

			TRACE_EXIT();
		}

		void
		display::show(
			__in terra::interface::world &world
			)
		{
			TRACE_ENTRY_FORMAT("World=%p", &world);

			if(SDL_UpdateTexture(m_texture, nullptr, &m_pixel[0], m_width * sizeof(color_t))) {
				THROW_TERRA_TYPE_DISPLAY_EXCEPTION_FORMAT(TERRA_TYPE_DISPLAY_EXCEPTION_EXTERNAL,
					"SDL_UpdateTexture failed! %s", SDL_GetError());
			}

			if(SDL_RenderClear(m_renderer)) {
				THROW_TERRA_TYPE_DISPLAY_EXCEPTION_FORMAT(TERRA_TYPE_DISPLAY_EXCEPTION_EXTERNAL,
					"SDL_RenderClear failed! %s", SDL_GetError());
			}

			if(SDL_RenderCopy(m_renderer, m_texture, nullptr, nullptr)) {
				THROW_TERRA_TYPE_DISPLAY_EXCEPTION_FORMAT(TERRA_TYPE_DISPLAY_EXCEPTION_EXTERNAL,
					"SDL_RenderCopy failed! %s", SDL_GetError());
			}

			SDL_RenderPresent(m_renderer);

			TRACE_EXIT();
		}
	}
}
