// This code was copy from https://forums.alliedmods.net/showpost.php?p=2231099&postcount=22
// I only change name var's and fn's

float HIDE_HEAD_SPRITE_TIME = 10.0

int headSprite[MAXPLAYERS + 1] = {-1, ...};
Handle hideHeadSpriteTimer[MAXPLAYERS + 1] = {INVALID_HANDLE, ...}

public Action createModel(Handle timer, any client){
    if (hideHeadSpriteTimer[client] != INVALID_HANDLE) {
      KillTimer(hideHeadSpriteTimer[client]);
      hideHeadSpriteTimer[client] = INVALID_HANDLE;
    }

    safeDelete(headSprite[client]);
    headSprite[client] = createIcon(client);
    placeAndBindIcon(client, headSprite[client]);

    hideHeadSpriteTimer[client] = CreateTimer(HIDE_HEAD_SPRITE_TIME, hideSpriteTimerCB, client);
}

public Action hideSpriteTimerCB(Handle timer, any client) {
  hideHeadSpriteTimer[client] = INVALID_HANDLE;
  safeDelete(headSprite[client]);
}

int createIcon(int client) {
    char buffer[256];
    Format(buffer, sizeof(buffer), "materials/%s.vmt", rankSprite[clientLvl[client]]);

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

void placeAndBindIcon(int client, int entity) {
    float origin[3];

    if (IsValidEntity(entity)) {
        GetClientAbsOrigin(client, origin);
        origin[2] = origin[2] + 30.0;
        TeleportEntity(entity, origin, NULL_VECTOR, NULL_VECTOR);

        SetVariantString("!activator");
        AcceptEntityInput(entity, "SetParent", client);
    }
}

void safeDelete(int entity) {
    if (IsValidEntity(entity)) {
        AcceptEntityInput(entity, "Kill");
    }
}
