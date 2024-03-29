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

#ifndef TERRA_COMMON_COLOR_H_
#define TERRA_COMMON_COLOR_H_

typedef union {

	struct {
		uint8_t blue;
		uint8_t green;
		uint8_t red;
		uint8_t alpha;
	};

	uint32_t raw;
} __attribute__((packed)) color_t;

enum {
	COLOR_WATER_DEEP = 0,
	COLOR_WATER_SHALLOW,
	COLOR_SAND,
	COLOR_GRASS,
	COLOR_DIRT,
	COLOR_GRAVEL,
	COLOR_STONE,
	COLOR_SNOW,
};

#define COLOR_MAX COLOR_SNOW
#define COLOR_MIN COLOR_WATER_DEEP

static const color_t COL[] = {
	{{ 175, 92, 45, 255 }}, // COLOR_WATER_DEEP
	{{ 201, 115, 68, 255 }}, // COLOR_WATER_SHALLOW
	{{ 145, 212, 216, 255 }}, // COLOR_SAND
	{{ 53, 157, 112, 255 }}, // COLOR_GRASS
	{{ 38, 115, 82, 255 }}, // COLOR_DIRT
	{{ 72, 78, 101, 255 }}, // COLOR_GRAVEL
	{{ 66, 69, 84, 255 }}, // COLOR_STONE
	{{ 255, 255, 255, 255 }}, // COLOR_SNOW
	};

#define COLOR(_TYPE_) \
	(((_TYPE_) > COLOR_MAX) ? COL[COLOR_MIN] : \
		COL[_TYPE_])

static const double COL_RANGE[] = {
	0.35, // COLOR_WATER_DEEP
	0.45, // COLOR_WATER_SHALLOW
	0.5, // COLOR_SAND
	0.65, // COLOR_GRASS
	0.7, // COLOR_DIR
	0.8, // COLOR_GRAVEL
	0.9, // COLOR_STONE_DARK
	1.0, // COLOR_SNOW
	};

#define COLOR_RANGE(_TYPE_) \
	(((_TYPE_) > COLOR_MAX) ? COL_RANGE[COLOR_MIN] : \
		COL_RANGE[_TYPE_])

#endif // TERRA_COMMON_COLOR_H_
