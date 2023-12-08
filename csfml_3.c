#include <SFML/Window.h>
#include <SFML/Graphics.h>
#include <SFML/System.h>

#define UP_PLAYER 0
#define RIGHT_PLAYER 1
#define LEFT_PLAYER 2
#define DOWN_PLAYER 3

int main()
{
    sfVideoMode mode = {800, 600, 32};
    sfRenderWindow* window;
    sfTexture* texture;
    sfSprite* sprite;
    sfEvent event;

    sfClock* clock = sfClock_create();

    window = sfRenderWindow_create(mode, "SFML window", sfResize | sfClose, NULL);
    if (!window)
        return 84;

    texture = sfTexture_createFromFile("assets/sprite.png", NULL);
    if (!texture)
        return 84;

    // * PLAYER
    // 1534 x 2000
    // 4 x 4
    sfIntRect rect = {0, 0, 383, 500};

    int player_x = 400;
    int player_y = 300;
    int rotation = 0;
    sprite = sfSprite_create();
    sfSprite_setScale(sprite, (sfVector2f){0.1, 0.1});
    sfSprite_setPosition(sprite, (sfVector2f){player_x, player_y});
    sfSprite_setOrigin(sprite, (sfVector2f){100, 100});
    sfSprite_setRotation(sprite, rotation);
    // sfSprite_setColor(sprite, (sfColor){255, 255, 255, 128});
    sfSprite_setTexture(sprite, texture, sfTrue);
    sfSprite_setTextureRect(sprite, rect);

    sfRenderWindow_setFramerateLimit(window, 60);
    while (sfRenderWindow_isOpen(window)) {
        while (sfRenderWindow_pollEvent(window, &event)) {
            if (event.type == sfEvtClosed)
                sfRenderWindow_close(window);
            if (event.type == sfEvtKeyPressed) {
                if (event.key.code == sfKeyZ) {
                    player_y -= 10;
                    rect.top = 500 * DOWN_PLAYER;
                }
                if (event.key.code == sfKeyS) {
                    player_y += 10;
                    rect.top = 500 * UP_PLAYER;
                }
                if (event.key.code == sfKeyQ) {
                    player_x -= 10;
                    rect.top = 500 * LEFT_PLAYER;
                }
                if (event.key.code == sfKeyD) {
                    player_x += 10;
                    rect.top = 500 * RIGHT_PLAYER;
                }
                if (event.key.code == sfKeyE)
                    rotation += 10;
                if (event.key.code == sfKeyA)
                    rotation -= 10;
            }
            sfVector2i mouse_pos = sfMouse_getPositionRenderWindow(window);
            if (event.type == sfEvtMouseButtonPressed) {
                if (event.mouseButton.button == sfMouseLeft) {
                    player_x = mouse_pos.x;
                    player_y = mouse_pos.y;
                }
            }
        }


        // Get elapsed time from the clock
        sfTime elapsed = sfClock_getElapsedTime(clock);
        float seconds = sfTime_asSeconds(elapsed);


        sfRenderWindow_clear(window, sfBlack);

        // * ANIMATE PLAYER
        if (seconds > 1.0) {
            rect.left += 383;
            if (rect.left >= 1534 - 383)
                rect.left = 0;
            sfSprite_setTextureRect(sprite, rect);
            sfClock_restart(clock);
        }

        // * DRAW PLAYER
        sfSprite_setRotation(sprite, rotation);
        sfSprite_setPosition(sprite, (sfVector2f){player_x, player_y});
        sfRenderWindow_drawSprite(window, sprite, NULL);

        sfRenderWindow_display(window);
    }

    sfSprite_destroy(sprite);
    sfTexture_destroy(texture);
    sfRenderWindow_destroy(window);
    return 0;
}
// gcc csfml_3.c -L/opt/homebrew/Cellar/csfml/2.5.2_1/lib -I/opt/homebrew/Cellar/csfml/2.5.2_1/include
// -lcsfml-graphics -lcsfml-window -Wno-deprecated-declarations -lcsfml-system