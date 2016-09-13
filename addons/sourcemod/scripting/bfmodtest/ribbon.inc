void TestRibbon_init() {
  RegConsoleCmd("bfmod_test_ribbon_info", bfmod_test_ribbon_info);
}

public Action bfmod_test_ribbon_info(int client, int args) {
  for (int i = 0; i < RIBBON_COUNT; ++i) {
    PrintToConsole(client, "%d) [name \"%s\"] [prog %d/%d] [exp %d] [count %d]", i, ribbonName[i], clientRibbonProgress[client][i], ribbonMaxProgress[i], ribbonExp[i], clientRibbonCount[client][i]);
  }
}
