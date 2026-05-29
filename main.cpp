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

    std::vector<uzaylilar> dusmanlar;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 10; j++) {
            uzaylilar u;
            u.sekil.setPointCount(10);
            u.sekil.setPoint(0, sf::Vector2f(0, -18));   
            u.sekil.setPoint(1, sf::Vector2f(8, -12));   
            u.sekil.setPoint(2, sf::Vector2f(18, -5));   
            u.sekil.setPoint(3, sf::Vector2f(22, 10));   
            u.sekil.setPoint(4, sf::Vector2f(12, 18));   
            u.sekil.setPoint(5, sf::Vector2f(0, 8));     
            u.sekil.setPoint(6, sf::Vector2f(-12, 18));  
            u.sekil.setPoint(7, sf::Vector2f(-22, 10));  
            u.sekil.setPoint(8, sf::Vector2f(-18, -5));  
            u.sekil.setPoint(9, sf::Vector2f(-8, -12));
            u.sekil.setFillColor(sf::Color(9, 25, 145));

            u.hedefYeri = sf::Vector2f(130.f + (j * 60.f), 40.f + (i * 60.f));
            u.sekil.setPosition(u.hedefYeri.x, -100.f - (i * 150.f) - (j * 40.f));
            u.hareketUlasti = false;
            u.aktif = true;
            u.atesZamani = rand() % 400 + 250;
            dusmanlar.push_back(u);
        }
    }
    float dusmanhizi = 2.f;
    float asagiinishizi = 10.f;

    bool oyunBasladi = false;
    //skor ve can sistemi
    int skor = 0;
    int can = 3;
    int saldiransayisi = 0;
    sf::Font font;
    font.loadFromFile("C:/Windows/Fonts/arial.ttf");
    sf::Text skorsayisi;
    skorsayisi.setFont(font);
    skorsayisi.setCharacterSize(20);
    skorsayisi.setFillColor(sf::Color(255, 255, 255));
    skorsayisi.setPosition(20.f, 10.f);
    sf::Text cansayisi;
    cansayisi.setFont(font);
    cansayisi.setCharacterSize(20);
    cansayisi.setFillColor(sf::Color(255, 255, 255));
    cansayisi.setPosition(700.f, 10.f);
    sf::Text gameover;
    gameover.setFont(font);
    gameover.setCharacterSize(65);
    gameover.setFillColor(sf::Color::Red);
    gameover.setString("OYUN BITTI");
    gameover.setPosition(220.f, 235.f);
    sf::Text tekrarbaslama;
    tekrarbaslama.setFont(font);
    tekrarbaslama.setCharacterSize(32);
    tekrarbaslama.setFillColor(sf::Color::White);
    tekrarbaslama.setString("Yeniden baslamak icin R tusuna basiniz");
    tekrarbaslama.setPosition(140.f, 320.f);
    while (pencere.isOpen()) {
        sf::Event olay;

        while (pencere.pollEvent(olay)) {
            if (olay.type == sf::Event::Closed) {
                pencere.close();
            }

            if (olay.type == sf::Event::KeyPressed) {
                if (oyunBasladi &&  olay.key.code == sf::Keyboard::Space && can > 0) {
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
        if (!oyunBasladi) {
            bool hepsiYerinde = true;
            for (auto& d : dusmanlar) {
                if (d.aktif && !d.hareketUlasti) {
                    hepsiYerinde = false;
                    break;
                }
            }
            oyunBasladi = hepsiYerinde;
        }
        //etkilesimleri algilamasi icin yazdik
        for (auto& y : yildizlar) {
            y.sekil.move(0.f, y.hiz);
            if (y.sekil.getPosition().y > 600.f) {
                y.sekil.setPosition(rand() % 800, 0.f);
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && can > 0) {
            if (savasucagi.getPosition().x > 20.f) {
                savasucagi.move(-7.2f, 0.f);
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && can > 0) {
            if (savasucagi.getPosition().x < 780.f) {
                savasucagi.move(7.2f, 0.f);
            }
        }
        
        if (can <= 0 && sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
            can = 3;
            skor = 0;
            oyunBasladi = false;
            
            kursunlar.clear();
            savasucagi.setPosition(380.f, 520.f);
            dusmanlar.clear();
        }

        for (auto& k : kursunlar) {
            if (k.aktif) {
                if (k.bizimMi) {
                    k.sekil.move(0, -15.f);
                    if (k.sekil.getPosition().y < 0) {
                        k.aktif = false;
                    }
                }
                else {
                    k.sekil.move(0, 10.f);
                    if (k.sekil.getPosition().y > 600.f) {
                            k.aktif = false;
                    }
                }
            }
        }

        bool yonDegistir = false;
        
        for (auto& d : dusmanlar) {
            if (d.aktif) {
                if (!d.saldirma) {
                    d.hedefYeri.x += dusmanhizi;
                    if (d.hedefYeri.x <= 30.f || d.hedefYeri.x >= 770.f) {
                        yonDegistir = true;
                    }
                }
                if (!d.hareketUlasti) {
                    float dx = d.hedefYeri.x - d.sekil.getPosition().x;
                    float dy = d.hedefYeri.y - d.sekil.getPosition().y;
                    float mesafe = std::sqrt(dx * dx + dy * dy);

                    if (mesafe > 5.f) {
                        float inisHizi = 6.0f; 
                        float dalga = std::sin(d.sekil.getPosition().y / 30.f) * 4.f;

                        d.sekil.move((dx / mesafe) * inisHizi + dalga, (dy / mesafe) * inisHizi);
                        d.sekil.setRotation(dalga * 5.f);
                    }
                    else {
                       
                        d.hareketUlasti = true;
                    }
                }
                else if (!d.saldirma) {
                    d.sekil.setPosition(d.hedefYeri); 
                    d.sekil.setRotation(0.f);

                    
                    if (oyunBasladi && saldiransayisi < 2 && rand() % 2500 < 2) {
                        d.saldirma = true;
                        saldiransayisi++;
                    }
                }
                else {
                    float dx = savasucagi.getPosition().x - d.sekil.getPosition().x;
                    float dy = savasucagi.getPosition().y - d.sekil.getPosition().y;
                    float uzunluk = std::sqrt(dx * dx + dy * dy);
                    if (uzunluk > 0) {
                        d.sekil.move((dx / uzunluk) * 2.5f, (dy / uzunluk) * 2.5f);
                        float aci = std::atan2(dy, dx) * 180.f / 3.1415f;
                        d.sekil.setRotation(aci + 90.f);
                    }
                    if (d.sekil.getPosition().y > 600.f) {
                        d.aktif = false;
                        saldiransayisi--;
                    }
                }
                if (oyunBasladi && d.hareketUlasti) {
                    d.atesZamani--;
                    if (d.atesZamani <= 0) {
                        kursun yeniMermi;
                        yeniMermi.sekil.setSize(sf::Vector2f(6.f, 16.f));
                        yeniMermi.sekil.setFillColor(sf::Color::Red);
                        yeniMermi.sekil.setPosition(d.sekil.getPosition().x - 3.f, d.sekil.getPosition().y + 20.f);
                        yeniMermi.aktif = true;
                        yeniMermi.bizimMi = false;
                        kursunlar.push_back(yeniMermi);
                        d.atesZamani = rand() % 400 + 250;
                    }
                }
            }
        }
        if (yonDegistir) {
            dusmanhizi = -dusmanhizi;
        }

        for (auto& k : kursunlar) {
            if (k.aktif) {
                if (k.bizimMi) {
                    k.sekil.move(0, -10);
               }
                else {
                    k.sekil.move(0, 2.f);
                }
                if (k.sekil.getPosition().y < 0.f || k.sekil.getPosition().y > 800.f) {
                    k.aktif = false;
                 }

                if (k.bizimMi) {
                    for (auto& d : dusmanlar) {
                        if (d.aktif && k.sekil.getGlobalBounds().intersects(d.sekil.getGlobalBounds())) {
                            d.aktif = false;
                            k.aktif = false;
                            skor += 20;
                            if (d.saldirma) {
                                saldiransayisi--;
                            }
                            break;
                        }
                    }
                }
                else {
                    if (k.sekil.getGlobalBounds().intersects(savasucagi.getGlobalBounds())) {
                        k.aktif = false;
                        savasucagi.setPosition(380.f, 520.f);
                        can--;
                    }
                }
            }
        }
        for (auto& d : dusmanlar) {
            if (d.aktif && d.saldirma) {
                if (d.sekil.getGlobalBounds().intersects(savasucagi.getGlobalBounds())) {
                    d.aktif = false;
                    savasucagi.setPosition(380.f, 520.f);
                    can--;
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

        for (const auto& u : dusmanlar) {
            if (u.aktif) {
                pencere.draw(u.sekil);
            }
        }
        pencere.draw(savasucagi);

        skorsayisi.setString("SKOR: " + std::to_string(skor));
        cansayisi.setString("CAN: " + std::to_string(can));
        pencere.draw(skorsayisi);
        pencere.draw(cansayisi);
        if (can <= 0) {
            pencere.clear(sf::Color::Black);
            pencere.draw(gameover);
            pencere.draw(tekrarbaslama);
        }

        pencere.display();
    }

    return 0;
}