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

#include "../../include/type/generator.h"
#include "../../include/terra.h"
#include "./generator_type.h"

namespace terra {

	namespace type {

		generator::generator(void)
		{
			TRACE_ENTRY();
			TRACE_EXIT();
		}

		generator::~generator(void)
		{
			TRACE_ENTRY();
			TRACE_EXIT();
		}

		void
		generator::generate(
			__in terra::interface::runtime &runtime
			)
		{
			std::mt19937 engine;
			std::vector<double> samples;
			std::vector<std::pair<int32_t, int32_t>> offsets;
			uint32_t octave, octaves, pixel_x, pixel_y, width, height;
			double lacunarity, noise_height_max = DBL_MIN, noise_height_min = DBL_MAX, persistance, scale;

			TRACE_ENTRY_FORMAT("Runtime=%p", &runtime);

			const terra_t &configuration = runtime.configuration();

			width = configuration.width;
			height = configuration.height;
			samples.resize(width * height);

			octaves = configuration.octaves;
			persistance = configuration.persistance;
			lacunarity = configuration.lacunarity;

			scale = configuration.scale;
			if(scale <= 0) {
				scale = SCALE_MIN;
			}

			offsets.resize(octaves);
			engine.seed(configuration.seed);

			for(octave = 0; octave < octaves; ++octave) {
				int32_t offset_x = (engine() + configuration.offset_x), offset_y = (engine() + configuration.offset_y);

				if(offset_x > OCTAVE_OFFSET_MAX) {
					offset_x = OCTAVE_OFFSET_MAX;
				} else if(offset_x < OCTAVE_OFFSET_MIN) {
					offset_x = OCTAVE_OFFSET_MIN;
				}

				if(offset_y > OCTAVE_OFFSET_MAX) {
					offset_y = OCTAVE_OFFSET_MAX;
				} else if(offset_y < OCTAVE_OFFSET_MIN) {
					offset_y = OCTAVE_OFFSET_MIN;
				}

				offsets.at(octave) = std::make_pair(offset_x, offset_y);
			}

			for(pixel_y = 0; pixel_y < height; ++pixel_y) {

				for(pixel_x = 0; pixel_x < width; ++pixel_x) {
					double amplitude = 1.0, frequency = 1.0, noise_height = 0.0;

					for(octave = 0; octave < octaves; ++octave) {
						double sample, sample_x, sample_y;

						sample_x = (((pixel_x / scale) * frequency) + offsets.at(octave).first);
						sample_y = (((pixel_y / scale) * frequency) + offsets.at(octave).second);

						sample = ((m_perlin.sample(sample_x, sample_y) * 2.0) - 1.0);

						noise_height += (sample * amplitude);

						amplitude *= persistance;
						frequency *= lacunarity;
					}

					if(noise_height > noise_height_max) {
						noise_height_max = noise_height;
					} else if(noise_height < noise_height_min) {
						noise_height_min = noise_height;
					}

					samples.at((pixel_y * width) + pixel_x) = noise_height;
				}
			}

			for(pixel_y = 0; pixel_y < height; ++pixel_y) {

				for(pixel_x = 0; pixel_x < width; ++pixel_x) {
					int type = COLOR_WATER_DEEP;
					double sample;

					sample = ((samples.at((pixel_y * width) + pixel_x) - noise_height_min)
							* (1.0 / (noise_height_max - noise_height_min)));

					for(; type <= COLOR_MAX; ++type) {

						if((sample >= COLOR_RANGE(type - 1)) && (sample <= COLOR_RANGE(type))) {
							break;
						}
					}

					runtime.set_pixel(COLOR(type), pixel_x, pixel_y);
				}
			}

			TRACE_EXIT();
		}

		void
		generator::on_initialize(
			__in const void *context
			)
		{
			uint32_t seed;
			const terra_t *configuration;

			TRACE_ENTRY_FORMAT("Context=%p", context);

			configuration = (const terra_t *)context;
			if(!configuration) {
				THROW_TERRA_TYPE_GENERATOR_EXCEPTION(TERRA_TYPE_GENERATOR_EXCEPTION_CONTEXT_INVALID);
			}

			TRACE_MESSAGE(LEVEL_INFORMATION, "Generator initializing");

			seed = configuration->seed;
			if(!seed) {
				seed = std::rand();
			}

			m_perlin.set_seed(seed);

			TRACE_MESSAGE_FORMAT(LEVEL_INFORMATION, "Generator seed", "%u(%08x)", seed, seed);

			TRACE_MESSAGE(LEVEL_INFORMATION, "Generator uninitialized");

			TRACE_EXIT();
		}

		void
		generator::on_uninitialize(void)
		{
			TRACE_ENTRY();

			TRACE_MESSAGE(LEVEL_INFORMATION, "Generator uninitializing");
			TRACE_MESSAGE(LEVEL_INFORMATION, "Generator uninitialized");

			TRACE_EXIT();
		}

		void
		generator::update(
			__in terra::interface::runtime &runtime
			)
		{
			TRACE_ENTRY_FORMAT("Runtime=%p", &runtime);

			generate(runtime);

			TRACE_EXIT();
		}
	}
}
