const int RIBBON_COUNT = 7;
const int MAX_RIBBON_SPRITE_PATH_LENGTH = 256;

char RIBBON_PATH[] = "configs/bfmod/ribbon.kv"

enum Ribbon {
  Ribbon_Assault = 0,
  Ribbon_Carabine,
  Ribbon_Knife,
  Ribbon_LMG,
  Ribbon_Pistol,
  Ribbon_SG,
  Ribbon_Sniper
};

char ribbonName[RIBBON_COUNT][] = {
  "Assault Rifle Ribbon",
  "Carbine Ribbon",
  "Melee Ribbon",
  "Light Machine Gun Ribbon",
  "Hand Gun Ribbon",
  "Shotgun Ribbon",
  "Sniper Rifle Ribbon"
};

int ribbonMaxProgress[RIBBON_COUNT];
int ribbonExp[RIBBON_COUNT];
char ribbonSprite[RIBBON_COUNT][MAX_RIBBON_SPRITE_PATH_LENGTH + 1];
StringMap ribbonWeapons[RIBBON_COUNT];

int clientRibbonProgress[MAXPLAYERS + 1][RIBBON_COUNT];
int clientRibbonCount[MAXPLAYERS + 1][RIBBON_COUNT];

void Ribbon_init() {
  for (int i = 0; i < sizeof(ribbonWeapons); ++i) {
    ribbonWeapons[i] = new StringMap();
  }

  Ribbon_parse();
}

void Ribbon_parse() {
  char pathToKV[PLATFORM_MAX_PATH + 1];
  BuildPath(Path_SM, pathToKV, sizeof(pathToKV), RIBBON_PATH);
  KeyValues kv = new KeyValues("ribbon");

  if (!kv.ImportFromFile(pathToKV)) {
    PrintToServer("[BFMod:Ribbon] File \"%s\" not found", pathToKV);
    return;
  }

  char weaponBuffer[64];

  for (int i = 0; i < sizeof(ribbonWeapons); ++i) {
    if (kv.JumpToKey(ribbonName[i])) {
      ribbonExp[i] = kv.GetNum("exp");
      ribbonMaxProgress[i] = kv.GetNum("max_progress");
      kv.GetString("sprite", ribbonSprite[i], sizeof(ribbonSprite[]));
      if (kv.JumpToKey("weapons")) {
        if (!kv.GotoFirstSubKey(false)) {
          continue;
        }

        do {
          kv.GetString(NULL_STRING, weaponBuffer, sizeof(weaponBuffer));
          ribbonWeapons[i].SetValue(weaponBuffer, 1);
          #if defined TEST_ENABLE
            PrintToServer("[BFMod:TestMod:Ribbon] Add \"%s\" to \"%s\"", weaponBuffer, ribbonName[i]);
          #endif
        } while (kv.GotoNextKey(false));
      }
      kv.Rewind();
    }
  }

  delete kv;
}

void Ribbon_incClientProgress(int client, Ribbon ribbon) {
  ++clientRibbonProgress[client][ribbon];

  if (clientRibbonProgress[client][ribbon] >= ribbonMaxProgress[ribbon]) {
    ++clientRibbonCount[client][ribbon];
    clientRibbonProgress[client][ribbon] = 0;
    ClientRank_giveExp(client, ribbonExp[ribbon]);
    PrintToChat(client, "ribbon complete %s you got %d", ribbonName[ribbon], ribbonExp[ribbon]);
  }
}

void Ribbon_eventOnPlayerDeath(int attacker, char[] weapon) {
  int nope;
  for (int i = 0; i < sizeof(ribbonWeapons); ++i) {
    if (ribbonWeapons[i].GetValue(weapon, nope)) {
      Ribbon_incClientProgress(attacker, view_as<Ribbon>(i));
    }
  }
}
