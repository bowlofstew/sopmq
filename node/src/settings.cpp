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

#include "settings.h"
#include "util.h"

using sopmq::shared::util;

namespace sopmq {
    namespace node {

        const uint32_t settings::DEFAULT_MAX_MESSAGE_SIZE = 10485760;
        const uint32_t settings::DEFAULT_OPERATION_TIMEOUT = 5;
        const float settings::DEFAULT_PHI_FAILURE_THRESHOLD = 8.0f;
        
        
        settings::settings()
        {
            maxMessageSize = DEFAULT_MAX_MESSAGE_SIZE;
            defaultTimeout = DEFAULT_OPERATION_TIMEOUT;
            phiFailureThreshold = DEFAULT_PHI_FAILURE_THRESHOLD;
        }
        
        settings::~settings()
        {
            
        }
        
        settings& settings::instance()
        {
            static settings inst;
            return inst;
        }
        
        const std::string& settings::ring_key_hash() const
        {
            static std::string hash = util::sha256_hex_string(this->ringKey);

            return hash;
        }
    }
}


