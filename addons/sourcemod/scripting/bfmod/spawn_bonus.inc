int HEALTH_PER_RANK = 1;

void giveSpawnBonus(int client) {
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
