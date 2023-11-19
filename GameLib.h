#ifndef __GAMELIB_H
#define __GAMELIB_H


CGame * pGame;



// Cursor Functions //

void AttachCursorToMouse(BOOL Attach);

int GetCursorX();
int GetCursorY();
int GetCursorZ();

void SetCursorSpeed(int Speed);
void SetCursorSprite(CSprite * pSprite);

void ShowCursor(BOOL Show);



#endif