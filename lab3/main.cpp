#include <stdlib.h>
#include <SDL2/SDL.h>

int LANG_MODE = 1;
/*
 * 0 -> bilingual
 * 1 -> english
 * 2 -> russian
 * 
*/

void fillScreen(SDL_Window *window)
{
  SDL_Surface *screen = SDL_GetWindowSurface(window);

  SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, rand() % 255, rand() % 255, rand() % 255));

  SDL_UpdateWindowSurface(window);
}

int asmFunction(void)
{
  static int internalValue = 1;

#ifdef __GNUC__
  __asm__("movl %0, %%eax\n\t"
          "add %%eax, %0"
          : "=r"(internalValue)
          : "r"(internalValue));
#elif _MSC_VER
  _asm {
		mov eax, internalValue
			add internalValue, eax
  }
  ;
#endif

  return internalValue;
}

int eventFilter(void *userdata, SDL_Event *event)
{
  switch (event->type)
  {
  case SDL_KEYDOWN:
    if (event->key.keysym.sym == SDLK_q && event->key.keysym.mod == KMOD_LCTRL)
    {
      SDL_Event exitEvent = {SDL_QUIT};
      SDL_PushEvent(&exitEvent);
    }

    if (LANG_MODE == 2 || LANG_MODE == 0)
    {
      SDL_Log("Нажатие клавиши %d", event->key.keysym.sym);
    }
    if (LANG_MODE == 1 || LANG_MODE == 0)
    {
      SDL_Log("key Down %d", event->key.keysym.sym);
    }
    break;
  case SDL_KEYUP:
    if (LANG_MODE == 2 || LANG_MODE == 0)
    {
      SDL_Log("Поднятие клавиши %d", event->key.keysym.sym);
    }
    if (LANG_MODE == 1 || LANG_MODE == 0)
    {
      SDL_Log("key Up %d", event->key.keysym.sym);
    }
    break;
  case SDL_TEXTEDITING:
    if (LANG_MODE == 2 || LANG_MODE == 0)
    {
      SDL_Log("Редактирование текста с клавиатуры (композиция). Композиция - %s, курсор начинается с %d, а длина выделения - %d", event->edit.text, event->edit.start, event->edit.length);
    }
    if (LANG_MODE == 1 || LANG_MODE == 0)
    {
      SDL_Log("Keyboard text editing (composition). Composition is '%s', cursor start from %d and selection lenght is %d", event->edit.text, event->edit.start, event->edit.length);
    }
    break;
  case SDL_TEXTINPUT:
    if (LANG_MODE == 2 || LANG_MODE == 0)
    {
      SDL_Log("Ввод текста с клавиатуры. Текст '%s'", event->text.text);
    }
    if (LANG_MODE == 1 || LANG_MODE == 0)
    {
      SDL_Log("Keyboard text input. Text is '%s'", event->text.text);
    }
    break;
  case SDL_FINGERMOTION:
    if (LANG_MODE == 2 || LANG_MODE == 0)
    {
      SDL_Log("Палец: %i, x: %i, y: %i", event->tfinger.fingerId, event->tfinger.x, event->tfinger.y);
    }
    if (LANG_MODE == 1 || LANG_MODE == 0)
    {
      SDL_Log("Finger: %i, x: %i, y: %i", event->tfinger.fingerId, event->tfinger.x, event->tfinger.y);
    }
    break;
  case SDL_FINGERDOWN:
    if (LANG_MODE == 2 || LANG_MODE == 0)
    {
      SDL_Log("Палец: %lld вниз - x: %i, y: %i",
              event->tfinger.fingerId, event->tfinger.x, event->tfinger.y);
    }
    if (LANG_MODE == 1 || LANG_MODE == 0)
    {
      SDL_Log("Finger: %lld down - x: %i, y: %i",
              event->tfinger.fingerId, event->tfinger.x, event->tfinger.y);
    }
    break;
  case SDL_FINGERUP:
    if (LANG_MODE == 2 || LANG_MODE == 0)
    {
      SDL_Log("Палец: %lld вверх - x: %i, y: %i", event->tfinger.fingerId, event->tfinger.x, event->tfinger.y);
    }
    if (LANG_MODE == 1 || LANG_MODE == 0)
    {
      SDL_Log("Finger: %lld up - x: %i, y: %i", event->tfinger.fingerId, event->tfinger.x, event->tfinger.y);
    }
    break;
  case SDL_MULTIGESTURE:
    if (LANG_MODE == 2 || LANG_MODE == 0)
    {
      SDL_Log("Мульти-жест: x = %f, y = %f, dAng = %f, dR = %f", event->mgesture.x, event->mgesture.y, event->mgesture.dTheta, event->mgesture.dDist);
      SDL_Log("Мульти-жест: количествоПрикосновений = %i", event->mgesture.numFingers);
    }
    if (LANG_MODE == 1 || LANG_MODE == 0)
    {
      SDL_Log("Multi Gesture: x = %f, y = %f, dAng = %f, dR = %f", event->mgesture.x, event->mgesture.y, event->mgesture.dTheta, event->mgesture.dDist);
      SDL_Log("Multi Gesture: numDownTouch = %i", event->mgesture.numFingers);
    }
    break;
  case SDL_DOLLARGESTURE:
    if (LANG_MODE == 2 || LANG_MODE == 0)
    {
      SDL_Log("Жест %lld выполнено, ошибка: %f", event->dgesture.gestureId, event->dgesture.error);
    }
    if (LANG_MODE == 1 || LANG_MODE == 0)
    {
      SDL_Log("Gesture %lld performed, error: %f", event->dgesture.gestureId, event->dgesture.error);
    }
    break;
  case SDL_DOLLARRECORD:
    if (LANG_MODE == 2 || LANG_MODE == 0)
    {
      SDL_Log("Записанный жест: %lld", event->dgesture.gestureId);
    }
    if (LANG_MODE == 1 || LANG_MODE == 0)
    {
      SDL_Log("Recorded gesture: %lld", event->dgesture.gestureId);
    }
    break;
  case SDL_MOUSEMOTION:
    if (LANG_MODE == 2 || LANG_MODE == 0)
    {
      SDL_Log("Движение мыши. X=%d, Y=%d, смещениеX=%d, смещениеY=%d", event->motion.x, event->motion.y, event->motion.xrel, event->motion.yrel);
    }
    if (LANG_MODE == 1 || LANG_MODE == 0)
    {
      SDL_Log("Mouse Move. X=%d, Y=%d, RelativeX=%d, RelativeY=%d", event->motion.x, event->motion.y, event->motion.xrel, event->motion.yrel);
    }
    break;
  case SDL_MOUSEBUTTONDOWN:
    if (event->button.button == SDL_BUTTON_LEFT)
      asmFunction();

    if (LANG_MODE == 2 || LANG_MODE == 0)
    {
      SDL_Log("Нажатие кнопки мыши %u", event->button.button);
    }
    if (LANG_MODE == 1 || LANG_MODE == 0)
    {
      SDL_Log("Mouse Button Down %u", event->button.button);
    }
    break;
  case SDL_MOUSEBUTTONUP:
    if (LANG_MODE == 2 || LANG_MODE == 0)
    {
      SDL_Log("Поднятие кнопки мыши %u", event->button.button);
    }
    if (LANG_MODE == 1 || LANG_MODE == 0)
    {
      SDL_Log("Mouse Button Up %u", event->button.button);
    }
    break;
  case SDL_MOUSEWHEEL:
    if (LANG_MODE == 2 || LANG_MODE == 0)
    {
      SDL_Log("Колесо мыши X=%d, Y=%d", event->wheel.x, event->wheel.y);
    }
    if (LANG_MODE == 1 || LANG_MODE == 0)
    {
      SDL_Log("Mouse Wheel X=%d, Y=%d", event->wheel.x, event->wheel.y);
    }
    break;
  case SDL_QUIT:
    if (LANG_MODE == 2 || LANG_MODE == 0)
    {
      SDL_Log("Пользовательский запрос выхода");
    }
    if (LANG_MODE == 1 || LANG_MODE == 0)
    {
      SDL_Log("User-requested quit");
    }
    return 1;
  case SDL_WINDOWEVENT:
    switch (event->window.event)
    {
    case SDL_WINDOWEVENT_SHOWN:
      if (LANG_MODE == 2 || LANG_MODE == 0)
      {
        SDL_Log("Окно %d показано", event->window.windowID);
      }
      if (LANG_MODE == 1 || LANG_MODE == 0)
      {
        SDL_Log("Window %d shown", event->window.windowID);
      }
      break;
    case SDL_WINDOWEVENT_HIDDEN:
    {
      if (LANG_MODE == 2 || LANG_MODE == 0)
      {
        SDL_Log("Окно %d спрятано", event->window.windowID);
      }
      if (LANG_MODE == 1 || LANG_MODE == 0)
      {
        SDL_Log("Window %d hidden", event->window.windowID);
      }
      break;
    }
    case SDL_WINDOWEVENT_EXPOSED:
      fillScreen(SDL_GetWindowFromID(event->window.windowID));
      if (LANG_MODE == 2 || LANG_MODE == 0)
      {
        SDL_Log("Окно %d выставлено", event->window.windowID);
      }
      if (LANG_MODE == 1 || LANG_MODE == 0)
      {
        SDL_Log("Window %d exposed", event->window.windowID);
      }
      break;
    case SDL_WINDOWEVENT_MOVED:
      if (LANG_MODE == 2 || LANG_MODE == 0)
      {
        SDL_Log("Окно %d сдвинуто на %d,%d", event->window.windowID, event->window.data1, event->window.data2);
      }
      if (LANG_MODE == 1 || LANG_MODE == 0)
      {
        SDL_Log("Window %d moved to %d,%d", event->window.windowID, event->window.data1, event->window.data2);
      }
      break;
    case SDL_WINDOWEVENT_RESIZED:
      if (LANG_MODE == 2 || LANG_MODE == 0)
      {
        SDL_Log("Окно %d изменен размер на %dx%d", event->window.windowID, event->window.data1, event->window.data2);
      }
      if (LANG_MODE == 1 || LANG_MODE == 0)
      {
        SDL_Log("Window %d resized to %dx%d", event->window.windowID, event->window.data1, event->window.data2);
      }
      break;
    case SDL_WINDOWEVENT_SIZE_CHANGED:
      if (LANG_MODE == 2 || LANG_MODE == 0)
      {
        SDL_Log("Окно %d размер изменен на %dx%d", event->window.windowID, event->window.data1, event->window.data2);
      }
      if (LANG_MODE == 1 || LANG_MODE == 0)
      {
        SDL_Log("Window %d size changed to %dx%d", event->window.windowID, event->window.data1, event->window.data2);
      }
      break;
    case SDL_WINDOWEVENT_MINIMIZED:
      if (LANG_MODE == 2 || LANG_MODE == 0)
      {
        SDL_Log("Окно %d минимизировано", event->window.windowID);
      }
      if (LANG_MODE == 1 || LANG_MODE == 0)
      {
        SDL_Log("Window %d minimized", event->window.windowID);
      }
      break;
    case SDL_WINDOWEVENT_MAXIMIZED:
      if (LANG_MODE == 2 || LANG_MODE == 0)
      {
        SDL_Log("Окно %d максимизировано", event->window.windowID);
      }
      if (LANG_MODE == 1 || LANG_MODE == 0)
      {
        SDL_Log("Window %d maximized", event->window.windowID);
      }
      break;
    case SDL_WINDOWEVENT_RESTORED:
      if (LANG_MODE == 2 || LANG_MODE == 0)
      {
        SDL_Log("Окно %d восстановлено", event->window.windowID);
      }
      if (LANG_MODE == 1 || LANG_MODE == 0)
      {
        SDL_Log("Window %d restored", event->window.windowID);
      }
      break;
    case SDL_WINDOWEVENT_ENTER:
      if (LANG_MODE == 2 || LANG_MODE == 0)
      {
        SDL_Log("Мышь над окном %d", event->window.windowID);
      }
      if (LANG_MODE == 1 || LANG_MODE == 0)
      {
        SDL_Log("Mouse entered window %d", event->window.windowID);
      }
      break;
    case SDL_WINDOWEVENT_LEAVE:
      if (LANG_MODE == 2 || LANG_MODE == 0)
      {
        SDL_Log("Мышь ушла с окна %d", event->window.windowID);
      }
      if (LANG_MODE == 1 || LANG_MODE == 0)
      {
        SDL_Log("Mouse left window %d", event->window.windowID);
      }
      break;
    case SDL_WINDOWEVENT_FOCUS_GAINED:
      if (LANG_MODE == 2 || LANG_MODE == 0)
      {
        SDL_Log("Окно %d получил фокус клавиатуры", event->window.windowID);
      }
      if (LANG_MODE == 1 || LANG_MODE == 0)
      {
        SDL_Log("Window %d gained keyboard focus", event->window.windowID);
      }
      break;
    case SDL_WINDOWEVENT_FOCUS_LOST:
      if (LANG_MODE == 2 || LANG_MODE == 0)
      {
        SDL_Log("Окно %d потеряло фокус клавиатуры", event->window.windowID);
      }
      if (LANG_MODE == 1 || LANG_MODE == 0)
      {
        SDL_Log("Window %d lost keyboard focus", event->window.windowID);
      }
      break;
    case SDL_WINDOWEVENT_CLOSE:
      if (LANG_MODE == 2 || LANG_MODE == 0)
      {
        SDL_Log("Окно %d закрыто", event->window.windowID);
      }
      if (LANG_MODE == 1 || LANG_MODE == 0)
      {
        SDL_Log("Window %d closed", event->window.windowID);
      }
      break;
    default:
      if (LANG_MODE == 2 || LANG_MODE == 0)
      {
        SDL_Log("Окно %d получило неизвестное событие %d", event->window.windowID, event->window.event);
      }
      if (LANG_MODE == 1 || LANG_MODE == 0)
      {
        SDL_Log("Window %d got unknown event %d", event->window.windowID, event->window.event);
      }
      break;
    }
    break;
  default:
    if (LANG_MODE == 2 || LANG_MODE == 0)
    {
      SDL_Log("Получено неизвестное событие %d", event->type);
    }
    if (LANG_MODE == 1 || LANG_MODE == 0)
    {
      SDL_Log("Got unknown event %d", event->type);
    }
    break;
  }

  return 0;
}

Uint32 customEventFunction(Uint32 interval, void *param)
{
  SDL_Event event = {SDL_WINDOWEVENT};

  if (LANG_MODE == 2 || LANG_MODE == 0)
  {
    SDL_Log("Таймер с интервалом %d ms", interval);
  }
  if (LANG_MODE == 1 || LANG_MODE == 0)
  {
    SDL_Log("Timer signaled with interval %d ms", interval);
  }

  event.window.windowID = SDL_GetWindowID((SDL_Window *)param);
  event.window.event = SDL_WINDOWEVENT_EXPOSED;

  SDL_PushEvent(&event);
  return (interval);
}

Uint32 repeatOnceFunction(Uint32 interval, void *param)
{
  SDL_Event exitEvent = {SDL_QUIT};

  if (LANG_MODE == 2 || LANG_MODE == 0)
  {
    SDL_Log("Таймер с интервалом %d ms", interval);
  }
  if (LANG_MODE == 1 || LANG_MODE == 0)
  {
    SDL_Log("Timer signaled with interval %d ms", interval);
  }

  if (asmFunction() != 0)
  {
    SDL_HideWindow((SDL_Window *)param);

    if (LANG_MODE == 0)
    {
      SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Что-то пошло не так - Something going wrong", "Найди меня! Я напуган - Find me! I'm scared", NULL);

      SDL_Delay(15000); /* 15 sec */
      SDL_LogWarn(SDL_LOG_CATEGORY_APPLICATION, "Ты не нашел меня! Ты разочаровал меня... Я ухожу - You didn't find me! You disappointed me... I'm leaving.");
    }
    else if (LANG_MODE == 1)
    {
      SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Something going wrong", "Find me! I'm scared", NULL);

      SDL_Delay(15000); /* 15 sec */
      SDL_LogWarn(SDL_LOG_CATEGORY_APPLICATION, "You didn't find me! You disappointed me... I'm leaving.");
    }
    else if (LANG_MODE == 2)
    {
      SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Что-то пошло не так", "Найди меня! Я напуган", NULL);

      SDL_Delay(15000); /* 15 sec */
      SDL_LogWarn(SDL_LOG_CATEGORY_APPLICATION, "Ты не нашел меня! Ты разочаровал меня... Я ухожу.");
    }

    SDL_PushEvent(&exitEvent);
  }

  return 0;
}

void clearFunction(void)
{
  SDL_Quit();
}

int main(int argc, char *argv[])
{
  if (argc > 1)
  {
    if (!strcmp("bilingual", argv[1]))
    {
      LANG_MODE = 0;
    }
    else if (!strcmp("russian", argv[1]))
    {
      LANG_MODE = 2;
    }
  }
  SDL_Window *windowContext = NULL;
  SDL_TimerID repeatOnceFunctionTimer;
  SDL_TimerID customEventFunctionTimer;

  atexit(clearFunction);
  srand((unsigned int)NULL);

  if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) < 0)
  {
    if (LANG_MODE == 0)
    {
      SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Ошибка - Error", "Невозможно запустить SDL2. Дополнительную информацию смотрите в логах - Unable to init SDL2. See the log for more info. ", NULL);
      SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION, "Невозможно запустить SDL2, ошибка - Unable to init SDL2, error: %s", SDL_GetError());
    }
    else if (LANG_MODE == 1)
    {
      SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", "Unable to init SDL2. See the log for more info. ", NULL);
      SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION, "Unable to init SDL2, error: %s", SDL_GetError());
    }
    else if (LANG_MODE == 2)
    {
      SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Ошибка", "Невозможно запустить SDL2. Дополнительную информацию смотрите в логах. ", NULL);
      SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION, "Невозможно запустить SDL2, ошибка: %s", SDL_GetError());
    }
    return 1;
  }

  SDL_SetEventFilter(eventFilter, NULL);

  if (LANG_MODE == 2 || LANG_MODE == 0)
  {
    SDL_Log("Начало создания окна");
  }
  if (LANG_MODE == 1 || LANG_MODE == 0)
  {
    SDL_Log("Start creating window");
  }
  if (!(windowContext = SDL_CreateWindow("SDL2: Magic Events", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_ALLOW_HIGHDPI | SDL_WINDOW_RESIZABLE)))
  {
    if (LANG_MODE == 0)
    {
      SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Ошибка - Error", "Невозможно создать окно. Дополнительную информацию смотрите в логах - Unable to create window. See the log for more info.", NULL);
      SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION, "Невозможно создать окно, ошибка - Unable to create window, error: %s", SDL_GetError());
    }
    else if (LANG_MODE == 1)
    {
      SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", "Unable to create window. See the log for more info.", NULL);
      SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION, "Unable to create window, error: %s", SDL_GetError());
    }
    else if (LANG_MODE == 2)
    {
      SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Ошибка", "Невозможно создать окно. Дополнительную информацию смотрите в логах. ", NULL);
      SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION, "Невозможно создать окно, ошибка: %s", SDL_GetError());
    }
    return 1;
  }
  else
  {
    if (LANG_MODE == 2 || LANG_MODE == 0)
    {
      SDL_Log("Создание окна - успешно");
    }
    if (LANG_MODE == 1 || LANG_MODE == 0)
    {
      SDL_Log("Creating window - succeeded");
    }
  }

  if (!(customEventFunctionTimer = SDL_AddTimer(2000 /* 2 sec */, customEventFunction, windowContext)))
  {
    if (LANG_MODE == 0)
    {
      SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Ошибка - Error", "Невозможно создать таймер пользовательского события. Дополнительную информацию смотрите в логах - Unable to create custom event timer. See the log for more info.", windowContext);
      SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION, "Невозможно создать таймер пользовательского события - Unable to create custom event timer, error: %s", SDL_GetError());
    }
    else if (LANG_MODE == 1)
    {
      SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", "Unable to create custom event timer. See the log for more info.", windowContext);
      SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION, "Unable to create custom event timer, error: %s", SDL_GetError());
    }
    else if (LANG_MODE == 2)
    {
      SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Ошибка", "Невозможно создать таймер пользовательского события. Дополнительную информацию смотрите в логах. ", NULL);
      SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION, "Невозможно создать таймер пользовательского события, ошибка: %s", SDL_GetError());
    }
  }

  if (!(repeatOnceFunctionTimer = SDL_AddTimer(10000 /* 10 sec */, repeatOnceFunction, windowContext)))
  {
    if (LANG_MODE == 0)
    {
      SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Ошибка - Error", "Невозможно создать одноразовый таймер. Дополнительную информацию смотрите в логах - Unable to create repeat once timer. See the log for more info.", windowContext);
      SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION, "Невозможно создать одноразовый таймер, ошибка - Unable to create repeat once timer, error: %s", SDL_GetError());
    }
    else if (LANG_MODE == 1)
    {
      SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", "Unable to create repeat once timer. See the log for more info.", windowContext);
      SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION, "Unable to create repeat once timer, error: %s", SDL_GetError());
    }
    else if (LANG_MODE == 2)
    {
      SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Ошибка", "Невозможно создать одноразовый таймер. Дополнительную информацию смотрите в логах. ", NULL);
      SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION, "Невозможно создать одноразовый таймер, ошибка: %s", SDL_GetError());
    }
  }

  SDL_WaitEvent(NULL);

  SDL_RemoveTimer(repeatOnceFunctionTimer);
  SDL_RemoveTimer(customEventFunctionTimer);

  if (LANG_MODE == 2 || LANG_MODE == 0)
  {
    SDL_Log("Начало разрушения окон");
  }
  if (LANG_MODE == 1 || LANG_MODE == 0)
  {
    SDL_Log("Start destroing window");
  }
  SDL_DestroyWindow(windowContext);
  windowContext = NULL;
  if (LANG_MODE == 2 || LANG_MODE == 0)
  {
    SDL_Log("разрушение окна - успешно");
  }
  if (LANG_MODE == 1 || LANG_MODE == 0)
  {
    SDL_Log("destroing window - succeeded");
  }

  return 0;
}