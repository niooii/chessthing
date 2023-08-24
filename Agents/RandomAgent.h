//
// Created by niooi on 8/22/23.
//

#ifndef OPENGL_RANDOMAGENT_H
#define OPENGL_RANDOMAGENT_H

#include "Agent.h"
#include <algorithm>
#include <iostream>
#include <random>

class RandomAgent : public Agent {
public:
    RandomAgent(TEAM agentTeam);

    Move GetMove(std::vector<Move> legalmoves) override;
};


#endif //OPENGL_RANDOMAGENT_H
