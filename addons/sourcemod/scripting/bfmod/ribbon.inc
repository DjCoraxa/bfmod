const int RIBBON_COUNT = 7;

enum Ribbon {
  Ribbon_Assault = 0,
  Ribbon_Carabine,
  Ribbon_Knife,
  Ribbon_LMG,
  Ribbon_Pistol,
  Ribbon_SG,
  Ribbon_Sniper
};

char ribbonName[][] = {
  "Assault Rifle Ribbon",
  "Carbine Ribbon",
  "Melee Ribbon",
  "Light Machine Gun Ribbon",
  "Hand Gun Ribbon",
  "Shotgun Ribbon",
  "Sniper Rifle Ribbon"
};

int ribbonMaxProgress[RIBBON_COUNT] = {
  5,
  5,
  5,
  5,
  5,
  5,
  5
};

int ribbonExp[RIBBON_COUNT];
StringMap ribbonWeapons[RIBBON_COUNT];

int clientRibbonProgress[MAXPLAYERS + 1][RIBBON_COUNT];
int clientRibbonCount[MAXPLAYERS + 1][RIBBON_COUNT];

void Ribbon_init() {
  for (int i = 0; i < sizeof(ribbonWeapons); ++i) {
    ribbonWeapons[i] = new StringMap();
    ribbonWeapons[0].SetValue("deagle", 1);
  }
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
