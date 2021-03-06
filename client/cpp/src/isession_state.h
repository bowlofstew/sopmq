/*
 * SOPMQ - Scalable optionally persistent message queue
 * Copyright 2014 InWorldz, LLC
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef __sopmq__isession_state__
#define __sopmq__isession_state__

#include "session_callbacks.h"

#include <memory>

namespace sopmq {
    namespace client {
        namespace impl {
            
            ///
            /// Interface to a state that a client session can be in
            ///
            class isession_state
            {
            public:
                typedef std::shared_ptr<isession_state> ptr;
                
            public:
                isession_state();
                virtual ~isession_state();
                
                virtual void state_entry() = 0;
                
                virtual void publish_message(const std::string& queueId, bool storeIfCantPipe, int ttl,
                                             const std::string& data, publish_message_callback callback) = 0;
            };
            
        }
    }
}

#endif /* defined(__sopmq__isession_state__) */
