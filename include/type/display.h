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

#ifndef TERRA_TYPE_DISPLAY_H_
#define TERRA_TYPE_DISPLAY_H_

#include "./singleton.h"

namespace terra {

	namespace type {

		class display :
				public terra::type::singleton<terra::type::display> {

			public:

				~display(void);

				void clear(void);

				float frame_frequency(void) const;

				float frame_rate(void) const;

				void set_pixel(
					__in const color_t &color,
					__in size_t x,
					__in size_t y
					);

				void set_frame_rate(
					__in float frame_rate
					);

				void set_title(
					__in const std::string &title
					);

				void show(void);

			protected:

				friend class terra::type::singleton<terra::type::display>;

				display(void);

				display(
					__in const display &other
					) = delete;

				display &operator=(
					__in const display &other
					) = delete;

				void on_initialize(
					__in const void *context
					) override;

				void on_uninitialize(void) override;

				float m_frame_frequency;

				float m_frame_rate;

				std::vector<color_t> m_pixel;

				SDL_Renderer *m_renderer;

				SDL_Texture *m_texture;

				std::string m_title;

				SDL_Window *m_window;
		};
	}
}

#endif // TERRA_TYPE_DISPLAY_H_
