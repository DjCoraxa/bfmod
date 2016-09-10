void setRankTag(int client) {
  char tag[64];
  Format(tag, sizeof(tag), "[Rank %d]", clientLvl[client]);
  CS_SetClientClanTag(client, tag);
}
