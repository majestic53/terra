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
			__in terra::interface::world &world
			)
		{
			std::vector<double> falloff;
			std::default_random_engine engine;
			std::vector<std::pair<double, double>> offsets;
			uint32_t height, octave, octaves, pixel_x, pixel_y, width;
			double center_x, center_y, lacunarity, noise_height_max = DBL_MIN, noise_height_min = DBL_MAX, persistance, scale;

			TRACE_ENTRY_FORMAT("World=%p", &world);

			const terra_t &configuration = world.configuration();

			width = configuration.width;
			height = configuration.height;

			terra::type::generator::resize(width * height);

			center_x = (width / 2.0);
			center_y = (height / 2.0);

			octaves = PERLIN_OCTAVES;
			persistance = PERLIN_PERSISTANCE;
			lacunarity = PERLIN_LACUNARITY;

			scale = PERLIN_SCALE;
			if(scale <= 0) {
				scale = SCALE_MIN;
			}

			offsets.resize(octaves);
			engine.seed(m_perlin.seed());

			for(octave = 0; octave < octaves; ++octave) {
				double offset_x = (engine() + PERLIN_OFFSET_X), offset_y = (engine() + PERLIN_OFFSET_Y);

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

			falloff.resize(width * height, 0);

#ifndef DISABLE_FALLOFF
			for(pixel_y = 0; pixel_y < height; ++pixel_y) {

				for(pixel_x = 0; pixel_x < width; ++pixel_x) {
					double sample, sample_x, sample_y;

					sample_x = (((pixel_x / (double)width) * 2.0) - 1.0);
					sample_y = (((pixel_y / (double)height) * 2.0) - 1.0);

					sample = std::max(std::abs(sample_x), std::abs(sample_y));
					sample = (std::pow(sample, FALLOFF_CURVE) / (std::pow(sample, FALLOFF_CURVE)
							+ std::pow(FALLOFF_SCALE - (sample * FALLOFF_SCALE), FALLOFF_CURVE)));

					falloff.at((pixel_y * width) + pixel_x) = sample;
				}
			}
#endif // DISABLE_FALLOFF

			for(pixel_y = 0; pixel_y < height; ++pixel_y) {

				for(pixel_x = 0; pixel_x < width; ++pixel_x) {
					size_t index = ((pixel_y * width) + pixel_x);
					double amplitude = 1.0, frequency = 1.0, noise_height = 0.0;

					for(octave = 0; octave < octaves; ++octave) {
						double sample, sample_x, sample_y;

						sample_x = ((((pixel_x - center_x) / scale) * frequency) + offsets.at(octave).first);
						sample_y = ((((pixel_y - center_y) / scale) * frequency) + offsets.at(octave).second);

						sample = ((m_perlin.sample(sample_x, sample_y) * 2.0) - 1.0);

						noise_height += (sample * amplitude);

						amplitude *= persistance;
						frequency *= lacunarity;
					}

#ifndef DISABLE_FALLOFF
					noise_height = std::clamp(noise_height - falloff.at(index), -1.0, 1.0);
#endif // DISABLE_FALLOFF
					if(noise_height > noise_height_max) {
						noise_height_max = noise_height;
					} else if(noise_height < noise_height_min) {
						noise_height_min = noise_height;
					}

					terra::type::generator::at(index) = noise_height;
				}
			}

			for(pixel_y = 0; pixel_y < height; ++pixel_y) {

				for(pixel_x = 0; pixel_x < width; ++pixel_x) {
					size_t index = ((pixel_y * width) + pixel_x);

					terra::type::generator::at(index) = ((terra::type::generator::at(index) - noise_height_min)
						* (1.0 / (noise_height_max - noise_height_min)));
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

			terra::type::generator::clear();

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

			terra::type::generator::clear();

			TRACE_MESSAGE(LEVEL_INFORMATION, "Generator uninitialized");

			TRACE_EXIT();
		}

		terra::type::perlin &
		generator::perlin(void)
		{
			TRACE_ENTRY();
			TRACE_EXIT_FORMAT("Result=%p", &m_perlin);
			return m_perlin;
		}
	}
}
