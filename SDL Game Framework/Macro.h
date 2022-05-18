// Macro.h : 유용한 매크로 모음
#pragma once

// 안전하게 자원을 해제한다.
#define SafeFree(p) { free(p); p = NULL; }

// 에러코드와 같이 로그를 출력한다.
#define LogWithErrorCode(msg, errorMsg) SDL_Log("[%s:%d] %s : %s\n", __FILE__, __LINE__, msg, errorMsg)
// 로그를 출력한다.
#define LogInfo(fmt, ...) SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, fmt, __VA_ARGS__)

// 둘 중 작은 값을 반환한다.
#define Min(lhs, rhs) ((lhs < rhs) ? (lhs) : (rhs))
// 둘 중 큰 값을 반환한다.
#define Max(lhs, rhs) ((lhs > rhs) ? (lhs) : (rhs))
// value를 [minValue, maxValue]로 만든다.
#define Clamp(minValue, value, maxValue) (Max(minValue, Min(value, maxValue)))
