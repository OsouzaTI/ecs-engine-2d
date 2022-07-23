#include <stdio.h>
#include "display.h"
#include "player.h"
#include "assets.h"


void configure() {
    // assets
    addAsset("nave", "Spaceships\\Spaceship#01(24x24).png");
}

int main(int argc, char *argv[]) {
    configure();
    Display* display = initScreen("Teste", 640, 480);
    Player* player = createPlayer(display, 100, 100, 24, 24, getAsset("nave"));

    setClearColor(display, rand()%255, rand()%255, rand()%255, 255);
    while(display->run) {
        clearScreen(display);
        input(display);
        update(display);

        player->transform->x += 0.01;

        // render player
        renderPlayer(display, player);

        render(display);       
    }
    destroyDisplay(&display);
    return 0;
}