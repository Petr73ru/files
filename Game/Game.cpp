#include "Game.h"

bool Game::init()
{
  if(SDL_Init(SDL_INIT_EVERYTHING) == 0)
  {
    std::cout << "SDL init success\n";
    m_pWindow = SDL_CreateWindow("我的游戏", 500, 70, 640, 640, 0);

    if(m_pWindow != 0)
    {
      std::cout << "window creation success\n";

      SDL_Surface* icon = IMG_Load("imgs/icon2.png");
      SDL_SetWindowIcon(m_pWindow, icon);
      SDL_FreeSurface(icon);

      m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, 0);

      if(m_pRenderer != 0)
      {
        std::cout << "renderer creation success\n";
        SDL_SetRenderDrawColor(m_pRenderer, 255, 20, 255, 255);

        m_Presses["UP"] = false;
        m_Presses["DONW"] = false;
        m_Presses["LEFT"] = false;
        m_Presses["RIGHT"] = false;

	m_Pokemon1.x = (9 - 1) * m_TileWidth; m_Pokemon1.y = (3 - 1) * m_TileHeight;
	m_Pokemon2.x = (5 - 1) * m_TileWidth; m_Pokemon2.y = (7 - 1) * m_TileHeight;
      }
      else
      {
        std::cout << "renderer init fail\n";
        return false;
      }
    }
    else
    {
      std::cout << "window init fail\n";
      return false;
    }
  }
  else
  {
    std::cout << "SDL init fail\n";
    return false;
  }

  std::cout << "init success\n";
  return true;
}

bool Game::loadTexture(std::string fileName, std::string id)
{
  SDL_Surface* pTempSurface = IMG_Load(fileName.c_str());

  if(pTempSurface == 0) return false;

  SDL_Texture* pTexture = SDL_CreateTextureFromSurface(m_pRenderer, pTempSurface);

  SDL_FreeSurface(pTempSurface);

  if(pTexture != 0)
  {
    m_TextureMap[id] = pTexture;
    std::cout << "Texture " << id << " loaded!\n";
    return true;
  }

  return false;
}

bool Game::unpressed() {
  if(!m_Presses["UP"] && !m_Presses["DOWN"] && !m_Presses["LEFT"] && !m_Presses["RIGHT"])
  return true;
  return false;
}

void Game::events()
{
  SDL_Event event;
  if(SDL_PollEvent(&event))
  {
    switch (event.type)
    {
      case SDL_QUIT: m_bRun = false; break;
      case SDL_KEYDOWN: switch (event.key.keysym.sym) {
        case SDLK_UP: unpressed() ? m_Presses["UP"] = true : NULL; break;
        case SDLK_DOWN: unpressed() ? m_Presses["DOWN"] = true : NULL; break;
        case SDLK_LEFT: unpressed() ? m_Presses["LEFT"] = true : NULL; break;
        case SDLK_RIGHT: unpressed() ? m_Presses["RIGHT"] = true : NULL; break;
      }
      break;
      case SDL_KEYUP: switch (event.key.keysym.sym) {
        case SDLK_UP: m_Presses["UP"] = false; break;
        case SDLK_DOWN: m_Presses["DOWN"] = false; break;
        case SDLK_LEFT: m_Presses["LEFT"] = false; break;
        case SDLK_RIGHT: m_Presses["RIGHT"] = false; break;
      }
      break;

      default: break;
    }
  }
}

void Game::update()
{
  if(m_Presses["UP"])
  {
    m_Ash.direction = 4;
    m_Ash.move = UP;
  }
  if(m_Presses["DOWN"])
  {
    m_Ash.direction = 1;
    m_Ash.move = DOWN;
  }
  if(m_Presses["LEFT"])
  {
    m_Ash.direction = 2;
    m_Ash.move = LEFT;
  }
  if(m_Presses["RIGHT"])
  {
    m_Ash.direction = 3;
    m_Ash.move = RIGHT;
  }

  if(m_Ash.move != NONE) m_Ash.frame = int(((SDL_GetTicks() / 100) % 4)) + 1;
  else m_Ash.frame = 1;

  if(unpressed()) m_Ash.move = NONE;

  switch (m_Ash.move)
  {
  case UP: --m_Ash.y; break;
  case DOWN: ++m_Ash.y; break;
  case LEFT: --m_Ash.x; break;
  case RIGHT: ++m_Ash.x; break;
  }

  if(m_Ash.move != NONE)
  {
    int PlayerCenterX = m_Ash.x + 32;
    int PlayerCenterY = m_Ash.y + 32;
    int Pokemon1CenterX = m_Pokemon1.x + 32;
    int Pokemon1CenterY = m_Pokemon1.y + 32;
    int Pokemon2CenterX = m_Pokemon2.x + 32;
    int Pokemon2CenterY = m_Pokemon2.y + 32;

    int V1X = Pokemon1CenterX - PlayerCenterX;
    int V1Y = Pokemon1CenterY - PlayerCenterY;
    int V2X = Pokemon2CenterX - PlayerCenterX;
    int V2Y = Pokemon2CenterY - PlayerCenterY;

    m_vP1.length = sqrt((V1X * V1X) + (V1Y * V1Y));
    m_vP2.length = sqrt((V2X * V2X) + (V2Y * V2Y));

    bool move = true;
    if(m_vP1.length <= 50 || m_vP2.length <= 50) move = false;
    if(!move)
    {
      switch (m_Ash.move)
      {
        case UP: ++m_Ash.y; break;
        case DOWN: --m_Ash.y; break;
        case LEFT: ++m_Ash.x; break;
        case RIGHT: --m_Ash.x; break;
      }
    }
  }
}

void Game::render()
{
  SDL_RenderClear(m_pRenderer);

  for(int i = 1; i <= 10; i++)
  {
    for(int j = 1; j <= 10; j++)
    {
      drawObject("grass", 1, 1, 1024, 1024, (i - 1) * 64, (j - 1) * 64);
    }
  }

  //if(m_vP1.length > 50)
  drawObject("pokemons", 11, 4, 80, 80, m_Pokemon1.x, m_Pokemon1.y);
  //if(m_vP2.length > 50)
  drawObject("pokemons", 9, 3, 80, 80, m_Pokemon2.x, m_Pokemon2.y);

  drawObject("ash", m_Ash.frame, m_Ash.direction, 272 / 4, 288 / 4, m_Ash.x, m_Ash.y);
  
  SDL_RenderPresent(m_pRenderer);
}
/*
void Game::drawObject(std::string id, int item, int row, int width, int height, int x, int y)
{
  SDL_Rect srcRect;
  SDL_Rect destRect;

  srcRect.x = (item - 1) * width;
  srcRect.y = (row - 1) * height;
  srcRect.w = width;
  srcRect.h = height;
  destRect.w = m_TileWidth;
  destRect.h = m_TileHeight;
  destRect.x = (x - 1) * m_TileWidth;
  destRect.y = (y - 1) * m_TileHeight;

  SDL_RenderCopyEx(m_pRenderer, m_TextureMap[id], &srcRect, &destRect, 0, 0, SDL_FLIP_NONE);
}*/

void Game::drawObject(std::string id, int item, int row, int width, int height, int x, int y)
{
  SDL_Rect srcRect;
  SDL_Rect destRect;

  srcRect.x = (item - 1) * width;
  srcRect.y = (row - 1) * height;
  srcRect.w = width;
  srcRect.h = height;
  destRect.w = m_TileWidth;
  destRect.h = m_TileHeight;
  destRect.x = x;
  destRect.y = y;

  SDL_RenderCopyEx(m_pRenderer, m_TextureMap[id], &srcRect, &destRect, 0, 0, SDL_FLIP_NONE);
}

void Game::clean()
{
  std::cout << "cleaning game\n";
  SDL_DestroyWindow(m_pWindow);
  SDL_DestroyRenderer(m_pRenderer);
  SDL_Quit();
}
