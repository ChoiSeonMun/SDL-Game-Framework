// Macro.h : ������ ��ũ�� ����
#pragma once

// �����ϰ� �ڿ��� �����Ѵ�.
#define SafeFree(p) { free(p); p = NULL; }

// �����ڵ�� ���� �α׸� ����Ѵ�.
#define LogWithErrorCode(msg, errorMsg) SDL_Log("[%s:%d] %s : %s\n", __FILE__, __LINE__, msg, errorMsg)
// �α׸� ����Ѵ�.
#define LogInfo(fmt, ...) SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, fmt, __VA_ARGS__)

// �� �� ���� ���� ��ȯ�Ѵ�.
#define Min(lhs, rhs) ((lhs < rhs) ? (lhs) : (rhs))
// �� �� ū ���� ��ȯ�Ѵ�.
#define Max(lhs, rhs) ((lhs > rhs) ? (lhs) : (rhs))
// value�� [minValue, maxValue]�� �����.
#define Clamp(minValue, value, maxValue) (Max(minValue, Min(value, maxValue)))
