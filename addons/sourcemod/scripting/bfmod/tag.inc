ConVar cvarRankTagEnable;

void initTag() {
  cvarRankTagEnable = CreateConVar("bfmod_rank_tag_enable", "1", "");
}

void setRankTag(int client) {
  if (!cvarRankTagEnable.BoolValue) {
    return;
  }

  char tag[64];
  Format(tag, sizeof(tag), "[Rank %d]", clientLvl[client]);
  CS_SetClientClanTag(client, tag);
}
