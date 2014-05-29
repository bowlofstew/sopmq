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

#ifndef __Project__csunauthenticated__
#define __Project__csunauthenticated__

#include "iconnection_state.h"
#include "connection.h"

namespace sopmq {
    namespace node {
        namespace connection {
            
            ///
            /// State before a connection has been authenticated
            ///
            class csunauthenticated : public iconnection_state
            {
            private:
                connection::wptr _conn;
                
            public:
                csunauthenticated(connection::wptr conn);
                virtual ~csunauthenticated();
                
                //
                // iconnection_state
                virtual void start();
                virtual std::string get_description() const;
            };
        }
    }
}

#endif /* defined(__Project__csunauthenticated__) */