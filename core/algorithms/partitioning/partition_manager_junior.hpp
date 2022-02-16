/* LSOracle: A learning based Oracle for Logic Synthesis

 * MIT License
 * Copyright 2019 Laboratory for Nano Integrated Systems (LNIS)
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */

#pragma once

#include <algorithm>
#include <vector>
#include <mockturtle/mockturtle.hpp>

namespace oracle
{
// Beware the son of partition manager!
template<typename network_base>
class partition_manager_junior
{
public:
    using network = typename mockturtle::names_view<network_base>;
    using partition_map = typename mockturtle::node_map<int, network>;
    using storage = typename network::storage;
    using node = typename network::node;
    using signal = typename network::signal;
    using window_view = typename mockturtle::window_view<network>;
    using fanout_view = typename mockturtle::fanout_view<network>;
    partition_manager_junior(network ntk, partition_map partitions, int part_num):
        ntk(ntk),
        partitions(partitions),
        partition_count(part_num) {}

    network &get_network()
    {
        return ntk;
    }

                       // {
               //     // Check if all fanin are not in the partition.
               //     bool exterior = true;
               //     std::vector<node> possible_ci;
               //     // Add CI for each non-partition fanin.
               //     ntk.foreach_fanin(n, [&](signal const &f){
               //         node fin = ntk.get_node(f);
               //         if (partitions[fin] != id) {
               //             possible_ci.push_back(fin);
               //         } else {
               //             exterior = false;
               //         }
               //     });
               //     if (exterior) {
               //         // Not a parent network CI, but is a CI in the partition.
               //         inputs.push_back(n);
               //     } else {
               //         // Is in the network, add any external fanin to inputs.
               //         for (auto i = possible_ci.begin(); i != possible_ci.end(); i++) {
               //             inputs.push_back(*i);
               //         }
               //         gates.push_back(n);
               //     }
               // }

    window_view partition(int id)
    {
        std::vector<node> inputs;
        std::vector<signal> outputs;
        std::vector<node> gates;
        fanout_view fanout(ntk);

        ntk.foreach_node([&](node const &n) {
           if (partitions[n] != id || ntk.is_constant(n)) {
               return;
           } else if (ntk.is_ci(n)) {
               inputs.push_back(n);
           } else {
              gates.push_back(n);
              // Add CI for each non-partition fanin.
              ntk.foreach_fanin(n, [&](signal const &f){
                  node fin = ntk.get_node(f);
                  if (partitions[fin] != id && !ntk.is_constant(fin)) {
                      inputs.push_back(fin);
                  }
              });
          }

           // Add output if fans out to non-partition.
           fanout.foreach_fanout(n, [&](node const &s) {
               if (partitions[s] != id) {
                  outputs.push_back(ntk.make_signal(n));
               }
           });
           // Add output if is a CO source.
           ntk.foreach_co([&](signal const &s) {
               if (ntk.get_node(s) == n) {
                   outputs.push_back(ntk.make_signal(n));
               }
           });
        });
        std::sort(inputs.begin(), inputs.end());
        auto iend = std::unique(inputs.begin(), inputs.end());
        inputs.resize(std::distance(inputs.begin(),iend));
        std::sort(outputs.begin(), outputs.end());
        auto oend = std::unique(outputs.begin(), outputs.end());
        outputs.resize(std::distance(outputs.begin(),oend));
        return mockturtle::window_view(ntk, inputs, outputs, gates);
    }

    template<class optimized_network>
    void integrate(int id, mockturtle::names_view<optimized_network> &opt)
    {
        window_view part = partition(id);
        integrate<optimized_network>(id, part, opt);
    }

    template<class optimized_network>
    void integrate(int partition_id, window_view &part, mockturtle::names_view<optimized_network> &opt)
    {
        std::cout << "Running integration" << std::endl;
        assert(opt.num_cis() == part.num_cis());
        assert(opt.num_cos() == part.num_cos());
        mockturtle::node_map<signal, mockturtle::names_view<optimized_network>> old_to_new(opt);

        // WARNING!!!! This works by assuming that PIs and POs in the
        // optimized network were created in the same order as in the partition.
        // This does not deal with other types of inputs/outputs, window_view treats all
        // inputs/outputs as generic PI/PO.
        part.foreach_ci([&](auto n, auto i) {
            auto o = opt.ci_at(i);
            old_to_new[o] = ntk.make_signal(n);
        });
        std::cout << "Setup PIs" << std::endl;
        mockturtle::topo_view opt_topo{opt};

        opt_topo.foreach_gate([&](auto node) {
            // Insert node into original network.
            std::vector<signal> children;
            opt.foreach_fanin(node, [&](auto child) {
                signal mapped = old_to_new[child];
                signal fanin = opt.is_complemented(child) ? ntk.create_not(mapped) : mapped;
                children.push_back(fanin);
            });

            old_to_new[node] = ntk.clone_node(opt, node, children);
            // Clone names if present.
            auto signal = opt.make_signal(node);
            if (opt.has_name(signal)) {
                ntk.set_name(old_to_new[node], opt.get_name(signal));
            }
        });
        std::cout << "Inserted new nodes " << partition_id << std::endl;
        partitions.resize();
        opt_topo.foreach_gate([&](auto node) {
            partitions[old_to_new[node]] = partition_id;
        });

        // Calculate substitutions from partition outputs.
        // std::unordered_map<node, signal> substitutions;
        opt.foreach_co([&](auto opt_signal, auto index) {
            auto opt_node = opt.get_node(opt_signal);
            signal new_out = old_to_new[opt_node];
            if (opt.is_complemented(opt_signal)) {
                new_out = ntk.create_not(new_out);
            }
            signal part_signal = part.co_at(index);
            node orig_node = ntk.get_node(part_signal);
            if (!opt.is_constant(opt_node) && !opt.is_ci(opt_node)) {
                substitutions[orig_node] = new_out;
            }
        });
        std::cout << "Calculated substitutions" << std::endl;
        // std::list<std::pair<node, signal>> substitution_list(substitutions.begin(),
        //                                                        substitutions.end());
        // ntk.substitute_nodes(substitution_list);
        for (auto substitution = substitutions.begin(); substitution != substitutions.end(); substitution++) {
            ntk.substitute_node(substitution->first, substitution->second);
        }
        std::cout << "Substituted nodes." << std::endl;
        //ntk = mockturtle::cleanup_dangling_with_registers(ntk);
    }

    int node_partition(const node &n)
    {
        return partitions[n];
    }

    int count()
    {
        return partition_count;
    }

private:
    network ntk;
    partition_map partitions;
    int partition_count;
    std::unordered_map<node, signal> substitutions;
};
}