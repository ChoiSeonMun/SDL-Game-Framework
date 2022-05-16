#pragma once

#define SafeFree(p) { free(p); p = NULL; }
#define SDL_LOG_WITH_ERRORCODE(msg) SDL_Log("[%s:%d] %s : %d\n", __FILE__, __LINE__, msg, SDL_GetError())

#define WINDOW_WIDTH	1280
#define WINDOW_HEIGHT	720