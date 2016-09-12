void BFMenu_init() {
  RegConsoleCmd("sm_bfmenu", cmd_sm_bfmenu);
}

public Action cmd_sm_bfmenu(int client, int args) {
  BFMenu_openMenu(client);
}

void BFMenu_openMenu(int client) {
  Menu menu = new Menu(BFMenu_MenuHandler);
  menu.SetTitle("BFMod menu");
  menu.AddItem("perk", "Choose perk [!perk]");
  menu.AddItem("perkdesc", "Perk desc [!perks]");
  menu.AddItem("bonus", "Bonus list [!bonus]");
  menu.AddItem("top", "Top15 rank [!bftop]");
  menu.AddItem("shop", "Shop menu [!shop]");
  menu.Display(client, 60);
}

public int BFMenu_MenuHandler(Menu menu, MenuAction action, int param1, int param2) {
  if (action == MenuAction_Select) {
    if (IsValidClient(param1)) {
      switch (param2) {
        case 0: PerkMenu_openMenu(param1);
        case 1: PerkDescMenu_openMenu(param1);
        case 2: BonusMenu_openMenu(param1);
        case 3: BFTop_openMenu(param1);
        case 4: openShopMenu(param1);
      }
    }
  } else if (action == MenuAction_End) {
		delete menu;
	}
}
