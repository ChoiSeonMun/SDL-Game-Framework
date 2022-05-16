#pragma once

void Renderer_Init(void);
void Renderer_Cleanup(void);
void Renderer_Prepare(void);
void Renderer_Flip(void);
void Renderer_DrawImage(const struct Image* image, int x, int y);
void Renderer_DrawTextSolid(const struct Text* text, int x, int y, SDL_Color color);
void Renderer_DrawTextShaded(const struct Text* text, int x, int y, SDL_Color foreground, SDL_Color background);
void Renderer_DrawTextBlended(const struct Text* text, int x, int y, SDL_Color foreground);