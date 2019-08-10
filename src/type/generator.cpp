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
		generator::on_initialize(
			__in const void *context
			)
		{
			uint32_t seed;

			TRACE_ENTRY_FORMAT("Context=%p", context);

			if(!context) {
				THROW_TERRA_TYPE_GENERATOR_EXCEPTION(TERRA_TYPE_GENERATOR_EXCEPTION_CONTEXT_INVALID);
			}

			TRACE_MESSAGE(LEVEL_INFORMATION, "Generator initializing");

			seed = ((const terra_t *)context)->seed;
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

			// TODO

			TRACE_EXIT();
		}
	}
}
