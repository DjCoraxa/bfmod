new g_Models[MAXPLAYERS + 1] = {-1, ...};

void initHeadSprite() {
  HookEvent("player_spawn", headSpriteSpawn);
  HookEvent("player_death", headSpriteDeath);
}

public Action headSpriteSpawn(Event event, const char[] name, bool dontBroadcast) {
  int client = GetClientOfUserId(event.GetInt("userid"));
  if(IsClientInGame(client) && IsPlayerAlive(client)) {
    CreateTimer(0.1, Create_Model, client);
  }
}

public Action headSpriteDeath(Event event, const char[] name, bool dontBroadcast) {
  int client = GetClientOfUserId(event.GetInt("userid"));
  SafeDelete(g_Models[client]);
}

public Action:Create_Model(Handle:iTimer, any:client)
{
    SafeDelete(g_Models[client]);
    g_Models[client] = CreateIcon(client);
    PlaceAndBindIcon(client, g_Models[client]);
}

CreateIcon(int client)
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
    if(DispatchSpawn(sprite))    return sprite;

    return -1;
}

PlaceAndBindIcon(client, entity)
{
    new Float:origin[3];

    if(IsValidEntity(entity)) {
        GetClientAbsOrigin(client, origin);
        origin[2] = origin[2] + 30.0;
        TeleportEntity(entity, origin, NULL_VECTOR, NULL_VECTOR);

        SetVariantString("!activator");
        AcceptEntityInput(entity, "SetParent", client);
    }
}

SafeDelete(entity)
{
    if(IsValidEntity(entity)) {
        AcceptEntityInput(entity, "Kill");
    }
}
