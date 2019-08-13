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

#ifndef TERRA_KEY_H_
#define TERRA_KEY_H_

enum {
	KEY_ARROW_RIGHT = 0,
	KEY_ARROW_LEFT,
	KEY_ARROW_UP,
	KEY_ARROW_DOWN,
	// ---
	KEY_WASD_RIGHT,
	KEY_WASD_LEFT,
	KEY_WASD_UP,
	KEY_WASD_DOWN,
};

#define KEY_MAX KEY_WASD_DOWN

#define KEY_VALUE(_TYPE_) \
	(((_TYPE_) > KEY_MAX) ? SDL_SCANCODE_UNKNOWN : \
		KEY_VAL[_TYPE_])

#endif // TERRA_KEY_H_
