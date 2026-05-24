#include <SFML/Graphics.hpp>

int main() {
    sf::RenderWindow pencere(sf::VideoMode(800, 600), "Galaga - Baslangic"); //oyunun penceresini olusturduk
    pencere.setFramerateLimit(60); //saniyede 60 kere yenilenmesini sagladik

    while (pencere.isOpen()) {
        sf::Event olay;

        while (pencere.pollEvent(olay)) {
            if (olay.type == sf::Event::Closed) {
                pencere.close();
            }
        }
        //etkilesimleri algilamasi icin yazdik

        pencere.clear(sf::Color::Black); //pencereyi siler ve tekrar siyah yapar
        pencere.display();
    }

    return 0;
}