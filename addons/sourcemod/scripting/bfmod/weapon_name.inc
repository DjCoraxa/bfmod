static StringMap weaponAlias;

char WEAPON_LIST_PATH[] = "configs/bfmod/weapon_alias.kv";

void WeaponName_init() {
  weaponAlias = new StringMap();
  WeaponName_parse();
}

static void WeaponName_parse() {
  char pathToKV[PLATFORM_MAX_PATH + 1];
  BuildPath(Path_SM, pathToKV, sizeof(pathToKV), WEAPON_LIST_PATH);

  KeyValues kv = new KeyValues("weapon_alias");

  if (!kv.ImportFromFile(pathToKV)) {
    PrintToServer("[BFMod:WeaponName] File \"%s\" not found", pathToKV);
    return;
  }

  char keyBuffer[64];
  char buffer[64];

  if (!kv.GotoFirstSubKey(false)) {
    return;
  }

  do {
    kv.GetSectionName(keyBuffer, sizeof(keyBuffer));
    kv.GetString(NULL_STRING, buffer, sizeof(buffer));

    weaponAlias.SetString(keyBuffer, buffer, true);

    #if defined TEST_ENABLE
      PrintToServer("[BFMod:TestMode:WeaponName] Add alias key=\"%s\" value=\"%s\"", keyBuffer, buffer);
    #endif
  } while (kv.GotoNextKey(false));

  delete kv;
}

void WeaponName_get(char[] weapon, char[] buffer, int maxLength) {
  if (!weaponAlias.GetString(weapon, buffer, maxLength)) {
    Format(buffer, maxLength, weapon);
  }
}
