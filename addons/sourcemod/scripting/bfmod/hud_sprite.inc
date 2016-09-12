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

void HudSprite_onLvlUp(int client, int lvl) {
  char spriteBuffer[MAX_RANK_SPRITE_PATH_LENGTH + 1];
  Rank_getSprite(lvl, spriteBuffer, sizeof(spriteBuffer));
  HudSprite_show(client, spriteBuffer);
}

void HudSprite_show(int client, char[] sprite) {
  clientHudSpriteStack[client].PushString(sprite);

  if (clientHudSpriteTimer[client] == INVALID_HANDLE) {
    clientHudSpriteTimer[client] = CreateTimer(cvarSpriteHudTime.FloatValue, HudSprite_showNextTimer, client, TIMER_REPEAT);
    TriggerTimer(clientHudSpriteTimer[client])
  }
}

public Action HudSprite_showNextTimer(Handle timer, any client) {
  if (!IsValidClient(client)) {
    clientHudSpriteTimer[client] = INVALID_HANDLE;
    return Plugin_Stop;
  }

  if (clientHudSpriteStack[client].Empty) {
    ClientCommand(client, "r_screenoverlay \"\"");
    clientHudSpriteTimer[client] = INVALID_HANDLE;
    return Plugin_Stop;
  }

  char sprite[256];
  clientHudSpriteStack[client].PopString(sprite, sizeof(sprite));
  ClientCommand(client, "r_screenoverlay \"%s\"", sprite);

  #if defined TEST_ENABLE
    PrintToConsole(client, "[BFMod:TestMode:HudSprite] Show hud sprite \"%s\"", sprite);
  #endif

  return Plugin_Continue;
}
