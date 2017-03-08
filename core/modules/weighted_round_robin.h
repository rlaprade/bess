/*
 * weighted_round_robin.h
 *
 *  Created on: Mar 8, 2017
 *      Author: rlaprade
 */

#ifndef BESS_MODULES_WEIGHTED_ROUND_ROBIN_H_
#define BESS_MODULES_WEIGHTED_ROUND_ROBIN_H_


#include "../module.h"
#include "../module_msg.pb.h"
#include "round_robin.h"

class WeightedRoundRobin final : public RoundRobin {
	public:
	  WeightedRoundRobin()
	      : Module(), gates_(), ngates_(), current_gate_(), per_packet_() {}

	  void ProcessBatch(bess::PacketBatch *batch) override;

	private:
	  double weights_[MAX_RR_GATES];
	  double min_weight;
	  int packets_on_current_gate = 0;
};

#endif /* CORE_MODULES_WEIGHTED_ROUND_ROBIN_H_ */
