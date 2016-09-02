void initPerkMenu() {
  RegConsoleCmd("sm_perk", cmd_sm_perk);
}

public Action cmd_sm_perk(int client, int args) {
  openPerkMenu(client);
}

void openPerkMenu(int client) {
  char buffor[256];

  Menu menu = new Menu(perkMenuHandler);
  menu.SetTitle("Chooser perk");

  for (int i = 1; i < sizeof(perkName); ++i) {
    Format(buffor, sizeof(buffor), "%s [Request rank %d]", perkName[i], perkLvlMin[i]);
    menu.AddItem(perkName[i], buffor, clientLvl[client] >= perkLvlMin[i] ? ITEMDRAW_DEFAULT : ITEMDRAW_DISABLED);
  }

  menu.Display(client, 60);
}

public int perkMenuHandler(Menu menu, MenuAction action, int param1, int param2) {
  if (action == MenuAction_Select) {
    if (IsValidClient(param1)) {
      changePerk(param1, view_as<Perk>(param2 + 1));
    }
  } else if (action == MenuAction_End) {
		delete menu;
	}
}
