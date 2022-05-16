#pragma once

bool Renderer_Init(struct SDL_Window* window);
void Renderer_Cleanup(void);
void Renderer_Prepare(void);
void Renderer_Flip(void);