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

#include "../include/type/singleton.h"
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
				m_configuration(nullptr)
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
				uint32_t seed;
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

				TRACE_MESSAGE(LEVEL_INFORMATION, "Terra initializing");

				seed = m_configuration->seed;
				if(!seed) {
					seed = std::rand();
				}

				// TODO

				TRACE_MESSAGE(LEVEL_INFORMATION, "Terra initialized");

				TRACE_EXIT();
			}

			void on_uninitialize(void) override
			{
				TRACE_ENTRY();

				TRACE_MESSAGE(LEVEL_INFORMATION, "Terra uninitializing");

				// TODO

				TRACE_MESSAGE(LEVEL_INFORMATION, "Terra uninitialized");

				SDL_Quit();

				TRACE_MESSAGE(LEVEL_INFORMATION, "SDL unloaded");

				TRACE_MESSAGE(LEVEL_INFORMATION, "Terra unloaded");

				TRACE_EXIT();
			}

			void loop(void)
			{
				uint32_t begin = 0, current = 0;

				TRACE_ENTRY();

				TRACE_MESSAGE(LEVEL_INFORMATION, "Terra running");

				for(;;) {
					float frequency, rate;
					uint32_t end = SDL_GetTicks();

					rate = (end - begin);
					if(rate >= MILLISECONDS_PER_SECOND) {
						rate = (current - ((rate - MILLISECONDS_PER_SECOND) / FRAME_RATE));

						TRACE_MESSAGE_FORMAT(LEVEL_INFORMATION, "Terra framerate", "%.1f", (rate > 0.f) ? rate : 0.f);

//#ifndef NDEBUG
						//m_display().set_frame_rate((rate > 0.f) ? rate : 0.f);
//#endif // NDEBUG
						begin = end;
						current = 0;
					}

					if(!poll()) {
						TRACE_MESSAGE(LEVEL_INFORMATION, "Terra interrupted");
						break;
					}

					// TODO

					frequency = (SDL_GetTicks() - end);
					if(frequency < FRAME_FREQUENCY) {
						SDL_Delay(FRAME_FREQUENCY - frequency);
					}

					++current;
				}

				TRACE_MESSAGE(LEVEL_INFORMATION, "Terra stopped");

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

			std::string m_error;
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
