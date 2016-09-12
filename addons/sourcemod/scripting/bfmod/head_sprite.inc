// This code was copy from https://forums.alliedmods.net/showpost.php?p=2231099&postcount=22
// I only change name var's and fn's

ConVar cvarHeadSpriteHideTime;

int headSprite[MAXPLAYERS + 1] = {-1, ...};
Handle hideHeadSpriteTimer[MAXPLAYERS + 1] = {INVALID_HANDLE, ...}

void HeadSprite_init() {
  cvarHeadSpriteHideTime = CreateConVar("bfmod_head_sprite_hide_timeout", "10.0", "Time (in sec) to autohide rank");
}

void HeadSprite_eventOnPlayerSpawn(int client) {
  CreateTimer(0.1, HeadSprite_createModel, client);
}

void HeadSprite_eventOnPlayerDeath(int victim) {
  HeadSprite_safeDelete(headSprite[victim]);
}

public Action HeadSprite_createModel(Handle timer, any client){
  if (hideHeadSpriteTimer[client] != INVALID_HANDLE) {
    KillTimer(hideHeadSpriteTimer[client]);
    hideHeadSpriteTimer[client] = INVALID_HANDLE;
  }

  HeadSprite_safeDelete(headSprite[client]);
  headSprite[client] = HeadSprite_createIcon(client);
  HeadSprite_placeAndBindIcon(client, headSprite[client]);

  hideHeadSpriteTimer[client] = CreateTimer(cvarHeadSpriteHideTime.FloatValue, HeadSprite_hideTimerCB, client);
}

public Action HeadSprite_hideTimerCB(Handle timer, any client) {
  hideHeadSpriteTimer[client] = INVALID_HANDLE;
  HeadSprite_safeDelete(headSprite[client]);
}

int HeadSprite_createIcon(int client) {
  char spriteBuffer[MAX_RANK_SPRITE_PATH_LENGTH + 1];
  Rank_getSprite(clientLvl[client], spriteBuffer, sizeof(spriteBuffer));

  char buffer[256];
  Format(buffer, sizeof(buffer), "materials/%s.vmt", spriteBuffer);

  new sprite = CreateEntityByName("env_sprite_oriented");

  if(sprite == -1)    return -1;

  DispatchKeyValue(sprite, "classname", "env_sprite_oriented");
  DispatchKeyValue(sprite, "spawnflags", "1");
  DispatchKeyValue(sprite, "scale", "0.3");
  DispatchKeyValue(sprite, "rendermode", "1");
  DispatchKeyValue(sprite, "rendercolor", "255 255 255");
  DispatchKeyValue(sprite, "model", buffer);

  if(DispatchSpawn(sprite)) {
    return sprite;
  }

  return -1;
}

void HeadSprite_placeAndBindIcon(int client, int entity) {
  float origin[3];

  if (IsValidEntity(entity) && IsValidClient(client)) {
    GetClientAbsOrigin(client, origin);
    origin[2] = origin[2] + 30.0;
    TeleportEntity(entity, origin, NULL_VECTOR, NULL_VECTOR);

    SetVariantString("!activator");
    AcceptEntityInput(entity, "SetParent", client);
  }
}

void HeadSprite_safeDelete(int entity) {
  if (IsValidEntity(entity)) {
    AcceptEntityInput(entity, "Kill");
  }
}
