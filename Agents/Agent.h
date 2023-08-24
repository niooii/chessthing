//
// Created by niooi on 8/22/23.
//

#ifndef OPENGL_AGENT_H
#define OPENGL_AGENT_H

#include "../Enums.h"
#include "../Structs.h"
#include <vector>

class Agent {
public:
    Agent(TEAM AgentTeam) : team(AgentTeam) {};
    TEAM team;
    virtual Move GetMove(std::vector<Move> legalmoves) = 0;
};


#endif //OPENGL_AGENT_H
