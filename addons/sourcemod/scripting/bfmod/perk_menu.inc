void PerkMenu_init() {
  RegConsoleCmd("sm_perk", cmd_sm_perk);
}

public Action cmd_sm_perk(int client, int args) {
  PerkMenu_openMenu(client);
}

void PerkMenu_openMenu(int client) {
  char buffor[256];

  Menu menu = new Menu(PerkMenu_menuHandler);
  menu.SetTitle("Chooser perk");

  for (int i = 1; i < sizeof(perkName); ++i) {
    Format(buffor, sizeof(buffor), "%s [Request rank %d]", perkName[i], perkLvlMin[i]);
    menu.AddItem(perkName[i], buffor, ClientRank_getLvl(client) >= perkLvlMin[i] ? ITEMDRAW_DEFAULT : ITEMDRAW_DISABLED);
  }

  menu.Display(client, 60);
}

public int PerkMenu_menuHandler(Menu menu, MenuAction action, int param1, int param2) {
  if (action == MenuAction_Select) {
    if (IsValidClient(param1)) {
      Perk_change(param1, view_as<Perk>(param2 + 1));
    }
  } else if (action == MenuAction_End) {
		delete menu;
	}
}
