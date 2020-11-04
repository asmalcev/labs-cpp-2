#include <cstdlib>
#include <iostream>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#ifdef __cplusplus
extern "C"
#endif
    int
    main(int argc, char **)
{
  std::cout << "Begin main" << std::endl;
  if (SDL_Init(SDL_INIT_VIDEO) != 0)
  {
    std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
    return 1;
  }

  SDL_Window *win = SDL_CreateWindow("Hello World!", 50, 50, 640, 480, SDL_WINDOW_SHOWN);
  if (win == 0)
  {
    std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
    SDL_Quit();
    return 1;
  }

  SDL_Renderer *ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  if (win == 0)
  {
    SDL_DestroyWindow(win);
    std::cout << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
    SDL_Quit();
    return 1;
  }

  std::string imagePath = "./hello.bmp";
  SDL_Surface *bmp = SDL_LoadBMP(imagePath.c_str());
  if (bmp == 0)
  {
    SDL_DestroyWindow(win);
    SDL_DestroyRenderer(ren);
    std::cout << "SDL_LoadBMP Error: " << SDL_GetError() << std::endl;
    SDL_Quit();
    return 1;
  }

  SDL_Texture *tex = SDL_CreateTextureFromSurface(ren, bmp);
  SDL_FreeSurface(bmp);
  if (tex == 0)
  {
    SDL_DestroyWindow(win);
    SDL_DestroyRenderer(ren);
    std::cout << "SDL_CreateTextureFromSurface Error: " << SDL_GetError() << std::endl;
    SDL_Quit();
    return 1;
  }

  if (TTF_Init() == -1)
  {
    std::cout << "TTF_Init: " << TTF_GetError() << std::endl;
    exit(2);
  }
  TTF_Font *font;
  font = TTF_OpenFont("Ubuntu-M.ttf", 16);
  if (!font)
  {
    std::cout << "TTF_OpenFont: " << TTF_GetError() << std::endl;
  }

  for (int i = 0; i < 3; i++)
  {
    SDL_RenderClear(ren);
    SDL_RenderCopy(ren, tex, NULL, NULL);
    SDL_RenderPresent(ren);
    SDL_Delay(1000);
  }

  SDL_Window *win2 = SDL_CreateWindow("Hello World!", 300, 500, 640, 480, SDL_WINDOW_SHOWN);
  if (win == 0)
  {
    std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
    SDL_Quit();
    return 1;
  }

  SDL_Renderer *ren2 = SDL_CreateRenderer(win2, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  if (win == 0)
  {
    SDL_DestroyWindow(win2);
    std::cout << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
    SDL_Quit();
    return 1;
  }

  bmp = SDL_LoadBMP(imagePath.c_str());
  if (bmp == 0)
  {
    SDL_DestroyWindow(win2);
    SDL_DestroyRenderer(ren2);
    std::cout << "SDL_LoadBMP Error: " << SDL_GetError() << std::endl;
    SDL_Quit();
    return 1;
  }

  SDL_Color color = {0, 0, 0};
  SDL_Surface *text_surface;
  if (!(text_surface = TTF_RenderUTF8_Solid(font, "Привет мир via Ubuntu-M.ttf!", color)))
  {
    return 1;
  }
  else
  {
    SDL_BlitSurface(text_surface, NULL, bmp, NULL);
    SDL_FreeSurface(text_surface);
  }
  SDL_Texture *tex2 = SDL_CreateTextureFromSurface(ren2, bmp);
  SDL_FreeSurface(bmp);
  if (tex2 == 0)
  {
    SDL_DestroyWindow(win2);
    SDL_DestroyRenderer(ren2);
    std::cout << "SDL_CreateTextureFromSurface Error: " << SDL_GetError() << std::endl;
    system("PAUSE");
    SDL_Quit();
    return 1;
  }

  SDL_Rect dst;
  SDL_Rect dst2;
  dst.x = 0;
  dst.y = 0;
  dst.w = 640;
  dst.h = 480;
  dst2.x = 0;
  dst2.y = 0;
  dst2.w = 640;
  dst2.h = 480;
  int i = 0, dirs = 1;

  SDL_Event e;
  bool quit = false;
  while (!quit)
  {
    while (SDL_PollEvent(&e))
    {
      if (e.type == SDL_MOUSEBUTTONDOWN)
      {
        if (e.button.windowID == 1)
        {
          if (e.button.button == SDL_BUTTON_RIGHT && (e.button.clicks >= 2))
          {
            quit = true;
          }
        }
        else
        {
          if (e.button.button == SDL_BUTTON_LEFT && (e.button.clicks >= 2))
            quit = true;
        }
      }
      if (e.type == SDL_WINDOWEVENT)
      {
        if (e.window.event == SDL_WINDOWEVENT_MOVED)
        {
          SDL_SetWindowPosition(win, 50, 50);
          SDL_SetWindowPosition(win2, 300, 500);
        }
      }
    }

    i += dirs;
    if (i > 10)
      dirs = -1;
    if (i < 0)
      dirs = +1;
    SDL_RenderClear(ren);
    dst.x = 10 * i;
    dst.y = 5 * i;
    SDL_RenderCopy(ren, tex, NULL, &dst);
    SDL_RenderPresent(ren);
    SDL_RenderClear(ren2);
    dst2.x = -10 * i;
    dst2.y = -5 * i;
    SDL_RenderCopy(ren2, tex2, NULL, &dst2);
    SDL_RenderPresent(ren2);
  }

  TTF_Quit();

  SDL_DestroyTexture(tex);
  SDL_DestroyRenderer(ren);
  SDL_DestroyWindow(win);

  std::cout << "End main before SDL_Quit" << std::endl;
  SDL_Quit();
  std::cout << "End main after SDL_Quit" << std::endl;
  return EXIT_SUCCESS;
}