#pragma once

void Renderer_Init(void);
void Renderer_Cleanup(void);
void Renderer_Prepare(void);
void Renderer_Flip(void);
void Renderer_DrawImage(const struct Image* image, int x, int y);