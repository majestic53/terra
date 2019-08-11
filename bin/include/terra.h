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

#ifndef TERRA_H_
#define TERRA_H_

#include <stdint.h>

#define TERRA_API_VERSION_1 1
#define TERRA_API_VERSION TERRA_API_VERSION_1

/**********************************************
 * TYPES
 **********************************************/

/**
 * Terra configuration
 */
typedef struct {

	// Initial seed value
	uint32_t seed;

	// Window dimensions
	uint32_t width;
	uint32_t height;

	// Generator parameters
	double scale;
	uint32_t octaves;
	double persistance;
	double lacunarity;
	int32_t offset_x;
	int32_t offset_y;
} terra_t;

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

/**********************************************
 * RUNTIME
 **********************************************/

/**
 * Run Terra
 * @param config Terra configuration
 * @return STATUS_SUCCESS on success
 */
int terra_run(const terra_t *config);

/**********************************************
 * MISC.
 **********************************************/

/**
 * Retrieve Terra error
 * @return Terra error as string
 */
const char *terra_error(void);

/**
 * Retrieve Terra version
 * @return Terra version as string
 */
const char *terra_version(void);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // TERRA_H_
