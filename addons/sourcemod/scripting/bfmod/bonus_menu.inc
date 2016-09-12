void BonusMenu_init() {
  RegConsoleCmd("sm_bonus", cmd_sm_bonus);
}

public Action cmd_sm_bonus(int client, int args) {
  BonusMenu_openMenu(client);
}

void BonusMenu_openMenu(int client) {
  char buffer[256];

  Menu menu = new Menu(BonusMenu_menuHandler);
  menu.SetTitle("Bonus list");

  Format(buffer, sizeof(buffer), "Bonus %d HP / RANK [On]", HEALTH_PER_RANK)
  menu.AddItem("hp", buffer);

  Format(buffer, sizeof(buffer), "Bonus %d xp [%s]", VIP_BONUS_EXP, GetUserFlagBits(client) & ADMFLAG_RESERVATION ? "On" : "Off, only VIP");
  menu.AddItem("vip_exp", buffer, GetUserFlagBits(client) & ADMFLAG_RESERVATION ? ITEMDRAW_DEFAULT : ITEMDRAW_DISABLED);

  Format(buffer, sizeof(buffer), "Free HE on spawn [%s]", clientLvl[client] >= 10 ? "On" : "Off, need rank 10");
  menu.AddItem("10lvl", buffer, clientLvl[client] >= 10 ? ITEMDRAW_DEFAULT : ITEMDRAW_DISABLED);

  Format(buffer, sizeof(buffer), "Free INC on spawn [%s]", clientLvl[client] >= 20 ? "On" : "Off, need rank 20");
  menu.AddItem("20lvl", buffer, clientLvl[client] >= 20 ? ITEMDRAW_DEFAULT : ITEMDRAW_DISABLED);

  Format(buffer, sizeof(buffer), "Free FlashBang on spawn [%s]", clientLvl[client] >= 30 ? "On" : "Off, need rank 30");
  menu.AddItem("30lvl", buffer, clientLvl[client] >= 30 ? ITEMDRAW_DEFAULT : ITEMDRAW_DISABLED);

  menu.Display(client, 60);
}

public int BonusMenu_menuHandler(Menu menu, MenuAction action, int param1, int param2) {
	if (action == MenuAction_End) {
		delete menu;
	}
}
