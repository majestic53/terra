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

#ifndef TERRA_COMMON_CONFIGURATION_H_
#define TERRA_COMMON_CONFIGURATION_H_

static const color_t COLOR_BACKGROUND = {{ 0, 0, 0, 255 }};

static const color_t COLOR_CROSSHAIR = {{ 0, 0, 255, 255 }};

#define CROSSHAIR_WIDTH 2

//#define DISABLE_COLOR
//#define DISABLE_CROSSHAIR
//#define DISABLE_OCCLUSION
#define DISABLE_TEXTURE

#define DISPLAY_HEIGHT 512
#define DISPLAY_SCALE 2
#define DISPLAY_WIDTH 512

#define GENERATOR_LACUNARITY 2.5
#define GENERATOR_OCTAVES 5
#define GENERATOR_OFFSET_X 0
#define GENERATOR_OFFSET_Y 0
#define GENERATOR_PERSISTANCE 0.6
#define GENERATOR_SCALE 100.0

static const SDL_Scancode KEY_VAL[] = {
	SDL_SCANCODE_RIGHT, // KEY_ARROW_RIGHT
	SDL_SCANCODE_LEFT, // KEY_ARROW_LEFT
	SDL_SCANCODE_UP, // KEY_ARROW_UP
	SDL_SCANCODE_DOWN, // KEY_ARROW_DOWN
	// ---
	SDL_SCANCODE_D, // KEY_WASD_RIGHT
	SDL_SCANCODE_A, // KEY_WASD_LEFT
	SDL_SCANCODE_W, // KEY_WASD_UP
	SDL_SCANCODE_S, // KEY_WASD_DOWN
	};

#define KEY_REGENERATE SDL_SCANCODE_R
#define KEY_RESET SDL_SCANCODE_SPACE

#define MOVE_SPEED 1

#define OCCLUSION_LIMIT COLOR_RANGE(COLOR_WATER_SHALLOW)
#define OCCLUSION_RADIUS 1
#define OCCLUSION_SCALE 16

#define TEXTURE_PATH "./asset/texture_flat.bmp"

#define TILE_WIDTH 16

#define ZOOM_MAX 4
#define ZOOM_MIN 0

#define ZOOM_SPEED 1

#endif // TERRA_COMMON_CONFIGURATION_H_
