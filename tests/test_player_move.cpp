// --- tests/test_player_move.cpp ---
#define main game_main_for_tests  // prevent launching the real game loop

#include <catch2/catch_all.hpp>
#include <SFML/Graphics.hpp>
#include <vector>

// Test-controlled input queue and stub:
static std::vector<sf::Vector2f> g_inputs;
sf::Vector2f fetchDir() {                 // same signature as in main.cpp
    if (g_inputs.empty()) return {0.f, 0.f};
    auto d = g_inputs.front();
    g_inputs.erase(g_inputs.begin());
    return d; // supply unit vectors in tests
}

// Pull in Player and the rest of your code (but not the real main(), thanks to the define above)
#include "main.cpp"

TEST_CASE("Player moves right and clamps at window edge") {
    Player p;
    sf::Vector2u win{800u, 600u};

    // 5 steps of Right with dt=1s -> would overshoot, should clamp at x = 800 - 200 = 600
    g_inputs.assign(5, sf::Vector2f{1.f, 0.f});
    for (int i = 0; i < 5; ++i) p.MoveEvent(1.f, win);

    auto postion = p.myBox.getPosition();
    CHECK(postion.x == Catch::Approx(600.f).margin(0.5f));
    CHECK(postion.y == Catch::Approx(25.f).margin(0.5f));
}

TEST_CASE("Up (overshoot) clamps to top, then Down moves to 300") {
    Player p;
    sf::Vector2u win{800u, 600u};

    // Up for 1s (overshoots -> clamps to y=0), then Down for 1s -> y=300
    g_inputs = { {0.f, -1.f}, {0.f, 1.f} };
    p.MoveEvent(1.f, win);
    p.MoveEvent(1.f, win);

    auto postion = p.myBox.getPosition();
    CHECK(postion.x == Catch::Approx(30.f).margin(0.5f));
    CHECK(postion.y == Catch::Approx(300.f).margin(0.5f));
}

TEST_CASE("Small Up then Down returns to start Y (no clamping)") {
    Player p;
    sf::Vector2u win{800u, 600u};

    // Use 0.05s (15px) so we never hit y=0 clamp.
    const float dt = 0.05f; // 15 px per step at speed 300
    g_inputs = { {0.f, -1.f}, {0.f, 1.f} };

    p.MoveEvent(dt, win); // y: 25 -> 10
    p.MoveEvent(dt, win); // y: 10 -> 25

    auto postion = p.myBox.getPosition();
    CHECK(postion.x == Catch::Approx(30.f).margin(0.5f));
    CHECK(postion.y == Catch::Approx(25.f).margin(0.5f));
}
