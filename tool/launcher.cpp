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
#include "./launcher_type.h"

namespace terra {

	namespace tool {

		class launcher :
				public terra::type::singleton<terra::tool::launcher> {

			public:

				~launcher(void)
				{
					TRACE_ENTRY();
					TRACE_EXIT();
				}

				int run(
					__in const std::vector<std::string> &arguments
					)
				{
					int result;

					TRACE_ENTRY_FORMAT("Argument[%u]=%p", arguments.size(), &arguments);

					std::memset(&m_configuration, 0, sizeof(m_configuration));
					m_help = false;
					m_seed = false;
					m_version = false;

					result = parse(arguments);
					if(result == EXIT_SUCCESS) {

						if(m_help) {
							std::cout << usage(true) << std::endl;
						} else if(m_version) {
							std::cout << version(false) << std::endl;
						} else {
							m_configuration.width = DISPLAY_WIDTH;
							m_configuration.height = DISPLAY_HEIGHT;

							m_configuration.scale = GENERATOR_SCALE;
							m_configuration.octaves = GENERATOR_OCTAVES;
							m_configuration.persistance = GENERATOR_PERSISTANCE;
							m_configuration.lacunarity = GENERATOR_LACUNARITY;
							m_configuration.offset_x = GENERATOR_OFFSET_X;
							m_configuration.offset_y = GENERATOR_OFFSET_Y;

							result = terra_run(&m_configuration);
							if(result != EXIT_SUCCESS) {
								std::cerr << "Error: " << terra_error() << std::endl;
							}
						}
					}

					TRACE_EXIT_FORMAT("Result=%i(%x)", result, result);
					return result;
				}

			protected:

				friend class terra::type::singleton<terra::tool::launcher>;

				launcher(void) :
					m_configuration({}),
					m_help(false),
					m_seed(false),
					m_version(false)
				{
					TRACE_ENTRY();
					TRACE_EXIT();
				}

				launcher(
					__in const launcher &other
					) = delete;

				launcher &operator=(
					__in const launcher &other
					) = delete;

				int parse(
					__in const std::vector<std::string> &arguments
					)
				{
					int result = EXIT_SUCCESS;

					TRACE_ENTRY_FORMAT("Argument[%u]=%p", arguments.size(), &arguments);

					if(arguments.size() >= ARGUMENT_MIN) {
						std::vector<std::string>::const_iterator argument;

						for(argument = (arguments.begin() + 1); argument != arguments.end(); ++argument) {

							if(result != EXIT_SUCCESS) {
								break;
							}

							if(argument->front() == std::string(ARGUMENT_DELIMITER).front()) {

								if(ARGUMENT_SUPPORTED(*argument)) {

									switch(ARGUMENT_TYPE(*argument)) {
										case ARGUMENT_HELP:
											m_help = true;
											break;
										case ARGUMENT_VERSION:
											m_version = true;
											break;
										default:
											result = EXIT_FAILURE;
											continue;
									}
								} else {
									result = EXIT_FAILURE;
								}
							} else if(!m_seed) {
								std::stringstream stream;

								stream << std::dec << *argument;
								stream >> m_configuration.seed;

								m_seed = true;
							} else {
								result = EXIT_FAILURE;
							}
						}
					} else {
						result = EXIT_FAILURE;
					}

					if(result != EXIT_SUCCESS) {
						std::cerr << usage(false) << std::endl;
					}

					TRACE_EXIT_FORMAT("Result=%i(%x)", result, result);
					return result;
				}

				std::string usage(
					__in bool verbose
					)
				{
					std::stringstream result;

					TRACE_ENTRY_FORMAT("Verbose=%x", verbose);

					if(verbose) {
						result << version(true) << std::endl << std::endl;
					}

					result << USAGE;

					if(verbose) {
						int argument = 0;

						result << std::endl;

						for(; argument <= ARGUMENT_MAX; ++argument) {
							std::stringstream stream;

							stream << ARGUMENT_SHORT(argument) << "|" << ARGUMENT_LONG(argument);
							result << std::endl << STRING_COLUMN() << stream.str() << ARGUMENT_DESCRIPTION(argument);
						}
					}

					TRACE_EXIT();
					return result.str();
				}

				std::string version(
					__in bool verbose
					)
				{
					std::stringstream result;

					TRACE_ENTRY_FORMAT("Verbose=%x", verbose);

					if(verbose) {
						result << TERRA << " ";
					}

					result << VERSION_STRING();

					if(verbose) {
						result << std::endl << TERRA_NOTICE;
					}

					TRACE_EXIT();
					return result.str();
				}

				terra_t m_configuration;

				bool m_help;

				bool m_seed;

				bool m_version;
		};
	}
}

int
main(
	__in int argc,
	__in const char *argv[]
	)
{
	int result = EXIT_SUCCESS;

	TRACE_ENTRY_FORMAT("Argument[%i]=%p", argc, argv);

	result = terra::tool::launcher::instance().run(std::vector<std::string>(argv, argv + argc));

	TRACE_EXIT_FORMAT("Result=%i(%x)", result, result);
	return result;
}
