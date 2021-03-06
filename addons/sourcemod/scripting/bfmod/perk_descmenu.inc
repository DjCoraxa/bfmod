void PerkDescMenu_init() {
  RegConsoleCmd("sm_perks", cmd_sm_perks);
}

public Action cmd_sm_perks(int client, int args) {
  PerkDescMenu_openMenu(client);
}

void PerkDescMenu_openMenu(int client) {
  char buffor[256];

  Menu menu = new Menu(PerkDescMenu_menuHandler);
  menu.SetTitle("Perk Description");

  for (int i = 1; i < sizeof(perkName); ++i) {
    Format(buffor, sizeof(buffor), "%s [Request rank %d]", perkName[i], perkLvlMin[i]);
    menu.AddItem(perkName[i], buffor);
  }

  menu.Display(client, 60);
}

public int PerkDescMenu_menuHandler(Menu menu, MenuAction action, int param1, int param2) {
  if (action == MenuAction_Select) {
    if (IsValidClient(param1)) {
      CPrintToChat(param1, "%s {purple}%s", MOD_NAME, perkDesc[param2 + 1]);
    }
  } else if (action == MenuAction_End) {
		delete menu;
	}
}
