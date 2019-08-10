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

#ifndef TERRA_TYPE_EXCEPTION_H_
#define TERRA_TYPE_EXCEPTION_H_

#include "../common.h"

namespace terra {

	namespace type {

		class exception :
				public std::runtime_error {

			public:

				exception(void);

				exception(
					__in const std::string &message,
					__in const std::string &file,
					__in const std::string &function,
					__in size_t line
					);

				exception(
					__in const exception &other
					);

				virtual ~exception(void);

				exception &operator=(
					__in const exception &other
					);

				void clear(void);

				bool empty(void) const;

				std::string file(void) const;

				std::string function(void) const;

				static void generate(
					__in const std::string &message,
					__in const std::string &file,
					__in const std::string &function,
					__in size_t line,
					__in const char *format,
					...
					);

				size_t line(void) const;

				std::string to_string(void) const;

			protected:

				bool m_empty;

				std::string m_file;

				std::string m_function;

				size_t m_line;
		};
	}
}

#endif // TERRA_TYPE_EXCEPTION_H_
