#include <SFML/Window.h>
#include <SFML/Graphics.h>

int main()
{
    sfVideoMode mode = {800, 600, 32};
    sfRenderWindow* window;
    sfTexture* texture;
    sfSprite* sprite;
    sfEvent event;

    window = sfRenderWindow_create(mode, "SFML window", sfResize | sfClose, NULL);
    if (!window)
        return 84;

    texture = sfTexture_createFromFile("assets/sprite.png", NULL);
    if (!texture)
        return 84;

    // * PLAYER
    int player_x = 400;
    int player_y = 300;
    sprite = sfSprite_create();
    sfSprite_setScale(sprite, (sfVector2f){0.1, 0.1});
    sfSprite_setPosition(sprite, (sfVector2f){player_x, player_y});
    sfSprite_setOrigin(sprite, (sfVector2f){100, 100});
    sfSprite_setRotation(sprite, 45);
    // sfSprite_setColor(sprite, (sfColor){255, 255, 255, 128});
    sfSprite_setTexture(sprite, texture, sfTrue);

    sfRenderWindow_setFramerateLimit(window, 60);
    while (sfRenderWindow_isOpen(window)) {
        while (sfRenderWindow_pollEvent(window, &event)) {
            if (event.type == sfEvtClosed)
                sfRenderWindow_close(window);
            if (event.type == sfEvtKeyPressed) {
                if (event.key.code == sfKeyZ)
                    player_y -= 10;
                if (event.key.code == sfKeyS)
                    player_y += 10;
                if (event.key.code == sfKeyQ)
                    player_x -= 10;
                if (event.key.code == sfKeyD)
                    player_x += 10;
            }
        }
        sfRenderWindow_clear(window, sfBlack);

        // * DRAW PLAYER
        sfSprite_setPosition(sprite, (sfVector2f){player_x, player_y});
        sfRenderWindow_drawSprite(window, sprite, NULL);

        sfRenderWindow_display(window);
    }

    sfSprite_destroy(sprite);
    sfTexture_destroy(texture);
    sfRenderWindow_destroy(window);
    return 0;
}