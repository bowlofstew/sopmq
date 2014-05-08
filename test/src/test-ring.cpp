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

#include "gtest/gtest.h"

#include "ring.h"
#include "endpoint.h"

#include <boost/multiprecision/random.hpp>

using namespace sopmq::node;
using namespace sopmq::node::net;
using namespace boost::multiprecision;
using namespace boost::random;

typedef independent_bits_engine<mt19937, 128, uint128_t> generator_type;
generator_type gen;

TEST(RingTest, TestEmptyRingFind)
{
    ring r;
    uint128_t num = gen();
    
    ASSERT_EQ(r.find_primary_node_for_key(num), node_ptr()) ;
}

TEST(RingTest, TestSingleNodeRingFind)
{
    ring r;
    uint128_t num = gen();
    
    node_ptr node(new sopmq::node::node(0, endpoint("sopmq1://localhost:1")));
    r.add_node(node);
    
    ASSERT_EQ(r.find_primary_node_for_key(num), node) ;
}

TEST(RingTest, TestSingleNodeRingFindWithSameKey)
{
    ring r;
    
    node_ptr node(new sopmq::node::node(20, endpoint("sopmq1://localhost:1")));
    r.add_node(node);
    
    ASSERT_EQ(r.find_primary_node_for_key(20), node) ;
}

TEST(RingTest, TestDoubleNodeRingFind)
{
    ring r;
    
    node_ptr node1(new sopmq::node::node(10, endpoint("sopmq1://localhost:1")));
    node_ptr node2(new sopmq::node::node(20, endpoint("sopmq1://localhost:2")));
    r.add_node(node1);
    r.add_node(node2);
    
    ASSERT_EQ(r.find_primary_node_for_key(1), node2);
    ASSERT_EQ(r.find_primary_node_for_key(21), node2);
    ASSERT_EQ(r.find_primary_node_for_key(11), node1);
    ASSERT_EQ(r.find_primary_node_for_key(19), node1);
}

TEST(RingTest, TestDoubleNodeRingFindWithSameKey)
{
    ring r;
    
    node_ptr node1(new sopmq::node::node(10, endpoint("sopmq1://localhost:1")));
    node_ptr node2(new sopmq::node::node(20, endpoint("sopmq1://localhost:2")));
    r.add_node(node1);
    r.add_node(node2);
    
    ASSERT_EQ(r.find_primary_node_for_key(10), node1);
    ASSERT_EQ(r.find_primary_node_for_key(20), node2);
}

TEST(RingTest, TestFindPrimaryAndSecondary)
{
    ring r;
    
    node_ptr node1(new sopmq::node::node(10, endpoint("sopmq1://localhost:1")));
    node_ptr node2(new sopmq::node::node(20, endpoint("sopmq1://localhost:2")));
    r.add_node(node1);
    r.add_node(node2);
    
    auto nodes = r.find_nodes_for_key(10);
    
    ASSERT_EQ(nodes[0], node1);
    ASSERT_EQ(nodes[1], node2);
    
    nodes = r.find_nodes_for_key(20);
    
    ASSERT_EQ(nodes[0], node2);
    ASSERT_EQ(nodes[1], node1);
    
    nodes = r.find_nodes_for_key(11);
    
    ASSERT_EQ(nodes[0], node1);
    ASSERT_EQ(nodes[1], node2);
    
    nodes = r.find_nodes_for_key(21);
    
    ASSERT_EQ(nodes[0], node2);
    ASSERT_EQ(nodes[1], node1);
}

TEST(RingTest, TestFindPrimaryAndSecondaryWith4Nodes)
{
    ring r;
    
    node_ptr node1(new sopmq::node::node(10, endpoint("sopmq1://localhost:1")));
    node_ptr node2(new sopmq::node::node(20, endpoint("sopmq1://localhost:2")));
    node_ptr node3(new sopmq::node::node(30, endpoint("sopmq1://localhost:3")));
    node_ptr node4(new sopmq::node::node(40, endpoint("sopmq1://localhost:4")));
    r.add_node(node1);
    r.add_node(node2);
    r.add_node(node3);
    r.add_node(node4);
    
    auto nodes = r.find_nodes_for_key(10);
    
    ASSERT_EQ(nodes[0], node1);
    ASSERT_EQ(nodes[1], node2);
    
    nodes = r.find_nodes_for_key(20);
    
    ASSERT_EQ(nodes[0], node2);
    ASSERT_EQ(nodes[1], node3);
    
    nodes = r.find_nodes_for_key(30);
    
    ASSERT_EQ(nodes[0], node3);
    ASSERT_EQ(nodes[1], node4);
    
    nodes = r.find_nodes_for_key(40);
    
    ASSERT_EQ(nodes[0], node4);
    ASSERT_EQ(nodes[1], node1);
    
    nodes = r.find_nodes_for_key(1);
    
    ASSERT_EQ(nodes[0], node4);
    ASSERT_EQ(nodes[1], node1);
    
    nodes = r.find_nodes_for_key(11);
    
    ASSERT_EQ(nodes[0], node1);
    ASSERT_EQ(nodes[1], node2);
    
    nodes = r.find_nodes_for_key(21);
    
    ASSERT_EQ(nodes[0], node2);
    ASSERT_EQ(nodes[1], node3);
    
    nodes = r.find_nodes_for_key(31);
    
    ASSERT_EQ(nodes[0], node3);
    ASSERT_EQ(nodes[1], node4);
    
    nodes = r.find_nodes_for_key(41);
    
    ASSERT_EQ(nodes[0], node4);
    ASSERT_EQ(nodes[1], node1);
}