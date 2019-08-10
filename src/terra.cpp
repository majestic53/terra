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

#include "../include/type/display.h"
#include "../include/terra.h"
#include "./terra_type.h"

namespace terra {

	class runtime :
			public terra::type::singleton<terra::runtime> {

		public:

			~runtime(void)
			{
				TRACE_ENTRY();
				TRACE_EXIT();
			}

			const char *error(void)
			{
				const char *result;

				TRACE_ENTRY();

				result = STRING(m_error);

				TRACE_EXIT_FORMAT("Result=%p", result);
				return result;
			}

			int run(
				const terra_t *configuration
				)
			{
				int result = EXIT_SUCCESS;

				TRACE_ENTRY_FORMAT("Context=%p", configuration);

				try {
					initialize(configuration);
					loop();
				} catch(terra::type::exception &exc) {
					m_error = exc.to_string();
					result = EXIT_FAILURE;
				} catch(std::exception &exc) {
					m_error = exc.what();
					result = EXIT_FAILURE;
				}

				uninitialize();

				TRACE_EXIT_FORMAT("Result=%i(%x)", result, result);
				return result;
			}

		protected:

			friend class terra::type::singleton<terra::runtime>;

			runtime(void) :
				m_configuration(nullptr),
				m_display(terra::type::display::instance()),
				m_seed(0)
			{
				TRACE_ENTRY();
				TRACE_EXIT();
			}

			runtime(
				__in const runtime &other
				) = delete;

			runtime &operator=(
				__in const runtime &other
				) = delete;

			void on_initialize(
				__in const void *context
				) override
			{
				SDL_version version = {};

				TRACE_ENTRY_FORMAT("Context=%p", context);

				m_configuration = (const terra_t *)context;
				if(!m_configuration) {
					THROW_TERRA_EXCEPTION(TERRA_EXCEPTION_CONFIGURATION_INVALID);
				}

				std::srand(std::time(nullptr));

				TRACE_MESSAGE_FORMAT(LEVEL_INFORMATION, "Terra loaded", "%s", VERSION_STRING());

				if(SDL_Init(SDL_FLAGS)) {
					THROW_TERRA_EXCEPTION_FORMAT(TERRA_EXCEPTION_EXTERNAL, "SDL_Init failed! %s", SDL_GetError());
				}

				SDL_GetVersion(&version);
				TRACE_MESSAGE_FORMAT(LEVEL_INFORMATION, "SDL loaded", "%u.%u.%u", version.major, version.minor, version.patch);

				TRACE_MESSAGE(LEVEL_INFORMATION, "Runtime initializing");

				m_seed = m_configuration->seed;
				if(!m_seed) {
					m_seed = std::rand();
				}

				TRACE_MESSAGE_FORMAT(LEVEL_INFORMATION, "Runtime seed", "%u(%08x)", m_seed, m_seed);

				// TODO

				m_display.initialize(nullptr);

				TRACE_MESSAGE(LEVEL_INFORMATION, "Runtime initialized");

				TRACE_EXIT();
			}

			void on_uninitialize(void) override
			{
				TRACE_ENTRY();

				TRACE_MESSAGE(LEVEL_INFORMATION, "Runtime uninitializing");

				m_display.uninitialize();

				// TODO

				TRACE_MESSAGE(LEVEL_INFORMATION, "Runtime uninitialized");

				SDL_Quit();

				TRACE_MESSAGE(LEVEL_INFORMATION, "SDL unloaded");
				TRACE_MESSAGE(LEVEL_INFORMATION, "Terra unloaded");

				TRACE_EXIT();
			}

			void loop(void)
			{
				uint32_t begin = 0, current = 0;
				float frame_frequency, frame_rate;

				TRACE_ENTRY();

				TRACE_MESSAGE(LEVEL_INFORMATION, "Runtime running");

				frame_frequency = m_display.frame_frequency();
				frame_rate = m_display.frame_rate();

				for(;;) {
					float frequency, rate;
					uint32_t end = SDL_GetTicks();

					rate = (end - begin);
					if(rate >= MILLISECONDS_PER_SECOND) {
						rate = (current - ((rate - MILLISECONDS_PER_SECOND) / frame_rate));

						TRACE_MESSAGE_FORMAT(LEVEL_INFORMATION, "Runtime framerate", "%.1f", (rate > 0.f) ? rate : 0.f);

#ifndef NDEBUG
						m_display.set_frame_rate((rate > 0.f) ? rate : 0.f);
#endif // NDEBUG
						begin = end;
						current = 0;
					}

					if(!poll()) {
						TRACE_MESSAGE(LEVEL_INFORMATION, "Runtime interrupted");
						break;
					}

					// TODO

					m_display.show();

					frequency = (SDL_GetTicks() - end);
					if(frequency < frame_frequency) {
						SDL_Delay(frame_frequency - frequency);
					}

					++current;
				}

				TRACE_MESSAGE(LEVEL_INFORMATION, "Runtime stopped");

				TRACE_EXIT();
			}

			bool poll(void)
			{
				bool result = true;
				SDL_Event event = {};

				TRACE_ENTRY();

				while(SDL_PollEvent(&event)) {

					switch(event.type) {
						case SDL_QUIT:
							result = false;
							break;
						default:
							break;
					}

					if(!result) {
						break;
					}
				}

				TRACE_EXIT_FORMAT("Result=%x", result);
				return result;
			}

			const terra_t *m_configuration;

			terra::type::display &m_display;

			std::string m_error;

			uint32_t m_seed;
	};
}

const char *
terra_error(void)
{
	const char *result;

	TRACE_ENTRY();

	result = terra::runtime::instance().error();

	TRACE_EXIT_FORMAT("Result=%p", result);
	return result;
}

int
terra_run(const terra_t *config)
{
	int result;

	TRACE_ENTRY_FORMAT("Config=%p", config);

	result = terra::runtime::instance().run(config);

	TRACE_EXIT_FORMAT("Result=%i(%x)", result, result);
	return result;
}

const char *
terra_version(void)
{
	const char *result;

	TRACE_ENTRY();

	result = VERSION_STRING();

	TRACE_EXIT();
	return result;
}
