ConVar cvarSpriteHudTime;

Handle clientHudSpriteTimer[MAXPLAYERS + 1];

//TODO: revrite code to "FIFO stack"
ArrayStack clientHudSpriteStack[MAXPLAYERS + 1];

void HudSprite_init() {
  cvarSpriteHudTime = CreateConVar("bfmod_hud_sprite_time", "5.0", "");
  for (int i = 0; i < MAXPLAYERS; ++i) {
    clientHudSpriteStack[i] = new ArrayStack(90);
  }
}


void HudSprite_show(int client, char[] sprite) {
  if (clientHudSpriteTimer[client] == INVALID_HANDLE) {
    clientHudSpriteTimer[client] = CreateTimer(cvarSpriteHudTime.FloatValue, HudSprite_showNextTimer, client, TIMER_REPEAT);
    ClientCommand(client, "r_screenoverlay \"%s\"", sprite);
  } else {
    clientHudSpriteStack[client].PushString(sprite);
  }
}

public Action HudSprite_showNextTimer(Handle timer, any client) {
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
