float SPRITE_HUD_TIME = 5.0;

Handle clientHudSpriteTimer[MAXPLAYERS + 1];

void showHudSprite(int client, char[] sprite) {
  if (clientHudSpriteTimer[client] != INVALID_HANDLE) {
    KillTimer(clientHudSpriteTimer[client]);
    clientHudSpriteTimer[client] = INVALID_HANDLE;
  }

  clientHudSpriteTimer[client] = CreateTimer(SPRITE_HUD_TIME, removeHudSprite, client);

  ClientCommand(client, "r_screenoverlay \"%s\"", sprite);
}

public Action removeHudSprite(Handle timer, any client) {
  clientHudSpriteTimer[client] = INVALID_HANDLE;
  ClientCommand(client, "r_screenoverlay \"\"");
}
