#include <SFML/Window.h>
#include <SFML/Graphics.h>

int main()
{
    sfVideoMode mode = {800, 600, 32};
    sfRenderWindow* window;
    sfEvent event;
    sfTexture *texture;
    sfSprite *sprite;

    window = sfRenderWindow_create(mode, "SFML window", sfResize | sfClose, NULL);
    if (!window)
        return 84;

    texture = sfTexture_createFromFile("assets/sprite.png", NULL);
    if (!texture)
        return 84;

    sprite = sfSprite_create();
    sfSprite_setTexture(sprite, texture, sfTrue);

    sfRenderWindow_setFramerateLimit(window, 60);
    while (sfRenderWindow_isOpen(window)) {
        while (sfRenderWindow_pollEvent(window, &event)) {
            if (event.type == sfEvtClosed)
                sfRenderWindow_close(window);
        }
        sfRenderWindow_clear(window, sfBlack);
        sfRenderWindow_drawSprite(window, sprite, NULL);
        sfRenderWindow_display(window);
    }

    sfSprite_destroy(sprite);
    sfTexture_destroy(texture);
    sfRenderWindow_destroy(window);
    return 0;
}