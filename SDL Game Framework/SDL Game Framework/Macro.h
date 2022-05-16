#pragma once

#define SafeFree(p) { free(p); p = NULL; }
#define LogWithErrorCode(msg, errorCode) SDL_Log("[%s:%d] %s : %d\n", __FILE__, __LINE__, msg, errorCode)
#define LogInfo(fmt, ...) SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, fmt, __VA_ARGS__)

#define WINDOW_WIDTH	1280
#define WINDOW_HEIGHT	720