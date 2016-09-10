float SPRITE_HUD_TIME = 5.0;

Handle clientHudSpriteTimer[MAXPLAYERS + 1];

//TODO: revrite code to "FIFO stack"
ArrayStack clientHudSpriteStack[MAXPLAYERS + 1];

void initHudSprite() {
  for (int i = 0; i < MAXPLAYERS; ++i) {
    clientHudSpriteStack[i] = new ArrayStack(90);
  }
}


void showHudSprite(int client, char[] sprite) {
  if (clientHudSpriteTimer[client] == INVALID_HANDLE) {
    clientHudSpriteTimer[client] = CreateTimer(SPRITE_HUD_TIME, showNextHudSprite, client, TIMER_REPEAT);
    ClientCommand(client, "r_screenoverlay \"%s\"", sprite);
  } else {
    clientHudSpriteStack[client].PushString(sprite);
  }
}

public Action showNextHudSprite(Handle timer, any client) {
  if (clientHudSpriteStack[client].Empty || !IsValidClient(client)) {
    ClientCommand(client, "r_screenoverlay \"\"");
    clientHudSpriteTimer[client] = INVALID_HANDLE;
    return Plugin_Stop;
  }

  char sprite[256];
  clientHudSpriteStack[client].PopString(sprite, sizeof(sprite));
  ClientCommand(client, "r_screenoverlay \"%s\"", sprite);

  return Plugin_Continue;
}
