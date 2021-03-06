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

#ifndef __sopmq__connection__
#define __sopmq__connection__

#include "iconnection_state.h"

#include "message_ptrs.h"
#include "message_types.h"
#include "messageutil.h"
#include "connection_base.h"
#include "ring.h"

#include <boost/weak_ptr.hpp>
#include <boost/noncopyable.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/asio.hpp>

#include <memory>
#include <cstdint>

namespace sopmq {
    namespace error {
        class network_error;
    }
}

namespace sopmq {
    namespace node {
        
        class server;
        
        namespace connection {
        
            ///
            /// Connections from clients or other servers into to this server
            ///
            class connection_in :   public boost::noncopyable,
                                    public sopmq::shared::net::connection_base,
                                    public std::enable_shared_from_this<connection_in>
            {
            public:
                typedef std::shared_ptr<connection_in> ptr;
                typedef std::weak_ptr<connection_in> wptr;
                
            public:
                connection_in(boost::asio::io_service& ioService, const ring& ring);
                virtual ~connection_in();
                
                ///
                /// Starts this connection and informs our server we're alive
                ///
                void start(server* server);
                
                ///
                /// Handles an error from a child state. Disconnects the user
                ///
                void handle_error(const sopmq::error::network_error& e);
                
                ///
                /// Changes to the given connection state
                ///
                void change_state(iconnection_state::ptr newState);
                
            private:
                boost::asio::io_service& _io_service;
                const ring& _ring;
                server* _server;
                iconnection_state::wptr _state;
            };
        
        
        }
    }
}

#endif /* defined(__sopmq__connection__) */
