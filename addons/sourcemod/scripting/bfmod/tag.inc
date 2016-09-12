ConVar cvarRankTagEnable;

void Tag_init() {
  cvarRankTagEnable = CreateConVar("bfmod_rank_tag_enable", "1", "");
}

void Tag_onClientPutInServer(int client) {
  Tag_setRankTag(client);
}

void Tag_eventOnPlayerSpawn(int client) {
  Tag_setRankTag(client);
}

void Tag_eventOnPlayerTeam(int client) {
  Tag_setRankTag(client);
}

void Tag_setRankTag(int client) {
  if (!cvarRankTagEnable.BoolValue) {
    return;
  }

  char tag[64];
  Format(tag, sizeof(tag), "[Rank %d]", clientLvl[client]);
  CS_SetClientClanTag(client, tag);
}
