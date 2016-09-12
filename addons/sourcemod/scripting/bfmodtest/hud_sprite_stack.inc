void TestHudSpriteStack_init() {
  RegConsoleCmd("bfmod_test_hud_sprite_stack", bfmod_test_hud_sprite_stack);
}

public Action bfmod_test_hud_sprite_stack(int client, int args) {
  for (int i = 0; i < sizeof(rankSprite); ++i) {
    HudSprite_show(client, rankSprite[i]);
  }
}
