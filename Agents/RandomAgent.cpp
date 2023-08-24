//
// Created by niooi on 8/22/23.
//

#include "RandomAgent.h"

RandomAgent::RandomAgent(TEAM agentTeam) : Agent(agentTeam)
{

}

Move RandomAgent::GetMove(std::vector<Move> legalmoves)
{
    // Seed the random number generator
    std::random_device rd;
    std::mt19937 gen(rd());

    if(legalmoves.empty())
    {
//        std::cout << "NO LEGAL MOVES" << '\n';
        return {nullptr, nullptr};
    }

    std::uniform_int_distribution<> distribution(0, legalmoves.size() - 1);

    return legalmoves.at(distribution(gen));
}