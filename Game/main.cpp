#include "Game.h"

int main(int argc, char* argv[])
{
  Game game;
  if(game.init())
  {
    if(game.loadTexture("imgs/pokemons.png", "pokemons")
    && game.loadTexture("imgs/grass.jpg", "grass")
    && game.loadTexture("imgs/ash.png", "ash"))
    {
      game.m_bRun = true;
      while(game.m_bRun)
      {
        game.events();
        game.update();
        game.render();
      }
    }
    game.clean();
  }
}
