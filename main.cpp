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
        y.sekil.setFillColor(sf::Color(146, 215, 224, rand() % 200 + 40));
        y.sekil.setPosition(rand() % 800, rand() % 600);
        y.hiz = (rand() % 3) + 2.f;
        yildizlar.push_back(y);
    }

    sf::ConvexShape savasucagi;
    savasucagi.setPointCount(8); 

    savasucagi.setPoint(0, sf::Vector2f(0, -30));   
    savasucagi.setPoint(1, sf::Vector2f(8, -10));    
    savasucagi.setPoint(2, sf::Vector2f(20, 5));   
    savasucagi.setPoint(3, sf::Vector2f(10, 20));    
    savasucagi.setPoint(4, sf::Vector2f(0, 15));  
    savasucagi.setPoint(5, sf::Vector2f(-10, 20));   
    savasucagi.setPoint(6, sf::Vector2f(-20, 5));
    savasucagi.setPoint(7, sf::Vector2f(-8, -10));
    savasucagi.setFillColor(sf::Color(224, 7, 160));
    savasucagi.setOrigin(0, 0);
    savasucagi.setPosition(398, 528); 

    std::vector<kursun> kursunlar;

    while (pencere.isOpen()) {
        sf::Event olay;

        while (pencere.pollEvent(olay)) {
            if (olay.type == sf::Event::Closed) {
                pencere.close();
            }
            if (olay.type == sf::Event::KeyPressed) {
                if (olay.key.code == sf::Keyboard::Space) {
                    kursun k;
                    k.sekil.setSize(sf::Vector2f(4, 15));
                    k.sekil.setFillColor(sf::Color(102, 4, 4));
                    k.sekil.setPosition(savasucagi.getPosition().x, savasucagi.getPosition().y - 25);
                    k.aktif = true;
                    k.bizimMi = true;
                    kursunlar.push_back(k);
                  }
                }
            }
        //etkilesimleri algilamasi icin yazdik
        for (auto& y : yildizlar) {
            y.sekil.move(0.f, y.hiz);
            if (y.sekil.getPosition().y > 600.f) {
                y.sekil.setPosition(rand() % 800, 0.f);
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            if (savasucagi.getPosition().x > 20.f) {
                savasucagi.move(-7.2f, 0.f);
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            if (savasucagi.getPosition().x < 780.f) {
                savasucagi.move(7.2f, 0.f);
            }
        }
        for (auto& k : kursunlar) {
            if (k.aktif) {
                k.sekil.move(0, -15.f);
                if (k.sekil.getPosition().y < 0) {
                    k.aktif = false;
                }
            }
        }

        pencere.clear(sf::Color::Black); //ekrani temizledik
        for (const auto& y : yildizlar) {
            pencere.draw(y.sekil);
        }

        for (const auto& k : kursunlar) {
            if (k.aktif) {
                pencere.draw(k.sekil);
            }
        }

        pencere.draw(savasucagi);

        pencere.display();
    }

    return 0;
}