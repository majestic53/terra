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

#ifndef TERRA_TYPE_SINGLETON_H_
#define TERRA_TYPE_SINGLETON_H_

#include "./trace.h"

namespace terra {

	namespace type {

		template <class T> class singleton {

			public:

				~singleton(void)
				{
					TRACE_ENTRY();
					TRACE_EXIT();
				}

				void initialize(
					__in const void *context
					)
				{
					TRACE_ENTRY_FORMAT("Context=%p", context);

					if(!m_initialized) {
						m_initialized = true;
						on_initialize(context);
					}

					TRACE_EXIT();
				}

				bool initialized(void) const
				{
					TRACE_ENTRY();
					TRACE_EXIT_FORMAT("Result=%x", m_initialized);
					return m_initialized;
				}

				static T &instance(void)
				{
					static T result;

					TRACE_ENTRY();
					TRACE_EXIT_FORMAT("Result=%p", &result);
					return result;
				}

				void uninitialize(void)
				{
					TRACE_ENTRY();

					if(m_initialized) {
						on_uninitialize();
						m_initialized = false;
					}

					TRACE_EXIT();
				}

			protected:

				singleton(void) :
					m_initialized(false)
				{
					TRACE_ENTRY();
					TRACE_EXIT();
				}

				singleton(
					__in const singleton &other
					) = delete;

				singleton &operator=(
					__in const singleton &other
					) = delete;

				virtual void on_initialize(
					__in const void *context
					)
				{
					TRACE_ENTRY_FORMAT("Context=%p", context);
					TRACE_EXIT();
				}

				virtual void on_uninitialize(void)
				{
					TRACE_ENTRY();
					TRACE_EXIT();
				}

				bool m_initialized;
		};
	}
}

#endif // TERRA_TYPE_SINGLETON_H_
