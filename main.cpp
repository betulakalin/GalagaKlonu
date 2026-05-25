#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <cmath>

struct yildiz {
    sf::CircleShape sekil;
    float hiz = 0.f;
};
struct kursun {
    sf::RectangleShape sekil;
    bool aktif = false;
    bool bizimMi = false;
};
struct uzaylilar {
    sf::ConvexShape sekil;
    sf::Vector2f hedefYeri;
    std::vector<sf::Vector2f> yolnoktalari;
    int suankiNokta = 0;
    bool aktif = false;
    int atesZamani = 0;
    bool saldirma = false;
    bool hareketUlasti = false;
};

struct parcalar {
    sf::RectangleShape sekil;
    float hizX = 0.f;
    float hizY = 0.f;
    int can = 0;
};
int main() {
    sf::RenderWindow pencere(sf::VideoMode(800, 600), "Galaga - Baslangic"); //oyunun penceresini olusturduk
    pencere.setFramerateLimit(60); //saniyede 60 kere yenilenmesini sagladik

    srand(time(NULL));
    std::vector<yildiz> yildizlar;
    for (int i = 0; i < 70; i++) {
        yildiz y;
        y.sekil.setRadius((rand() % 3) + 1.f);
        y.sekil.setFillColor(sf::Color(245, 240, 250, rand() % 200 + 40));
        y.sekil.setPosition(rand() % 800, rand() % 600);
        y.hiz = (rand() % 3) + 2.f;
        yildizlar.push_back(y);
    }
    while (pencere.isOpen()) {
        sf::Event olay;

        while (pencere.pollEvent(olay)) {
            if (olay.type == sf::Event::Closed) {
                pencere.close();
            }
        }
        //etkilesimleri algilamasi icin yazdik
        for (auto& y : yildizlar) {
            y.sekil.move(0.f, y.hiz);
            if (y.sekil.getPosition().y > 600.f) {
                y.sekil.setPosition(rand() % 800, 0.f);
            }
        }

        pencere.clear(sf::Color::Black); //ekrani temizledik
        for (const auto& y : yildizlar) {
            pencere.draw(y.sekil);
        }
        pencere.display();
    }

    return 0;
}