void TestHudSpriteStack_init() {
  RegConsoleCmd("bfmod_test_hud_sprite_stack", bfmod_test_hud_sprite_stack);
}

public Action bfmod_test_hud_sprite_stack(int client, int args) {
  for (int i = 0; i < Rank_getCount(); ++i) {
    char spriteBuffer[MAX_RANK_SPRITE_PATH_LENGTH + 1];
    Rank_getSprite(i, spriteBuffer, sizeof(spriteBuffer));
    HudSprite_show(client, spriteBuffer);
  }
}
