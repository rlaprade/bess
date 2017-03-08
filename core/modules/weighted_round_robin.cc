#include "weighted_round_robin.h"
#include "round_robin.h"
#include "round_robin.cc"

pb_error_t WeightedRoundRobin::Init(const bess::pb::RoundRobinArg &arg)
: RoundRobin::Init(&arg) {

 }

void WeightedRoundRobin::ProcessBatch(bess::PacketBatch *batch) {
  gate_idx_t out_gates[bess::PacketBatch::kMaxBurst];

  if (per_packet_) {
    for (int i = 0; i < batch->cnt(); i++) {
      out_gates[i] = gates_[current_gate_];
      packets_on_current_gate++;
      if (packets_on_current_gate > weights_[current_gate_] / min_weight) {
          current_gate_ = (current_gate_ + 1) % ngates_;
          packets_on_current_gate = 0;
      }
    }
    RunSplit(out_gates, batch);
  } else {
    gate_idx_t gate = gates_[current_gate_];
    packets_on_current_gate++;
    if (packets_on_current_gate > weights_[current_gate_] / min_weight) {
        current_gate_ = (current_gate_ + 1) % ngates_;
        packets_on_current_gate = 0;
    }
    RunChooseModule(gate, batch);
  }
}




