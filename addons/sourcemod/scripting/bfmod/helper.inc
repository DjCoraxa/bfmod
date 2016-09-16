void Helper_precacheSprite(char[] sprite) {
  char buffer[256];
  Format(buffer, sizeof(buffer), "%s.vtf", sprite);
  PrecacheDecal(buffer, true);
  Format(buffer, sizeof(buffer), "materials/%s.vtf", sprite);
  AddFileToDownloadsTable(buffer);
  Format(buffer, sizeof(buffer), "%s.vmt", sprite);
  PrecacheDecal(buffer, true);
  Format(buffer, sizeof(buffer), "materials/%s.vmt", sprite);
  AddFileToDownloadsTable(buffer);

  #if defined TEST_MODE
    PrintToServer("[BFMod:TestMode:Helper] Precache sprite \"%s\"", sprite);
  #endif
}
