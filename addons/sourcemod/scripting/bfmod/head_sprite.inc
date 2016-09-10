// This code was copy from https://forums.alliedmods.net/showpost.php?p=2231099&postcount=22
// I only change name var's and fn's

new headSprite[MAXPLAYERS + 1] = {-1, ...};

void initHeadSprite() {
  HookEvent("player_spawn", headSpriteSpawn);
  HookEvent("player_death", headSpriteDeath);
}

public Action headSpriteSpawn(Event event, const char[] name, bool dontBroadcast) {
  int client = GetClientOfUserId(event.GetInt("userid"));
  if(IsClientInGame(client) && IsPlayerAlive(client)) {
    CreateTimer(0.1, createModel, client);
  }
}

public Action headSpriteDeath(Event event, const char[] name, bool dontBroadcast) {
  int client = GetClientOfUserId(event.GetInt("userid"));
  safeDelete(headSprite[client]);
}

public Action createModel(Handle timer, any client)
{
    safeDelete(headSprite[client]);
    headSprite[client] = createIcon(client);
    placeAndBindIcon(client, headSprite[client]);
}

createIcon(int client)
{
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

placeAndBindIcon(int client, int entity) {
    new Float:origin[3];

    if (IsValidEntity(entity)) {
        GetClientAbsOrigin(client, origin);
        origin[2] = origin[2] + 30.0;
        TeleportEntity(entity, origin, NULL_VECTOR, NULL_VECTOR);

        SetVariantString("!activator");
        AcceptEntityInput(entity, "SetParent", client);
    }
}

safeDelete(int entity) {
    if (IsValidEntity(entity)) {
        AcceptEntityInput(entity, "Kill");
    }
}
