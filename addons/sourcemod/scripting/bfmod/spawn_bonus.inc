int HEALTH_PER_RANK = 1;

void initRankBonus() {
  HookEvent("player_spawn", rankBonusSpawn);
}

public Action rankBonusSpawn(Event event, const char[] name, bool dontBroadcast) {
  int client = GetClientOfUserId(event.GetInt("userid"));

  if (IsValidClient(client)) {
    SetEntityHealth(client, GetClientHealth(client) + HEALTH_PER_RANK * clientLvl[client]);

    switch (clientLvl[client]) {
      case 10:
        GivePlayerItem(client, "weapon_hegrenade");
      case 20:
        GivePlayerItem(client, "weapon_incgrenade");
      case 30:
        GivePlayerItem(client, "weapon_flashbang");
    }
  }
}
