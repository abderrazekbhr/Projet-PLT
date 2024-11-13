#include <iostream>

#include "../state.h"

int main() {

    state::Game *game=new state::Game();
    game->setState(new state::InitState());
    game->request();
    game->setState(new state::RoundState());
    game->request();
    game->setState(new state::DistributeCardState());
    game->request();
    game->setState(new state::CountScoreState());
    game->request();

    return 0;
}