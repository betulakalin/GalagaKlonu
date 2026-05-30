# GalagaKlonu (C++ & SFML)
Bu proje, C++ dili ve SFML kütüphanesi kullanılarak geliştirilmiş 2 boyutlu bir nişan oyunudur.
Klasik Galaga oyununun temellerini içerir.

## Oyun Özellikleri 
* **Düşmanlar:** Uzaylılar ekrana süzülerek sürüler halinde dizilir ve rastgele şekilde en fazla iki tanesi oyuncuya doğru hareket eder.
* **Çarpışma Kontrolü:** Oyuncunun mermilerinin uzaylılara, uzaylıların mermilerinin oyuncuya ve uzaylıların oyuncuya çarpması kontrol edilir.
* **Kalıcı Rekor Sistemi:** Oyuncunun yaptığı en yüksek skor `<fstream>` kütüphanesi kullanılarak `skor.txt` dosyasına kaydedilir
* **Oyun Döngüsü:** Can sayısı, skor göstergeleri, oyunun bittiğini gösteren yazı ve 'R' tuşu ile oyunu sıfırlayıp baştan başlatan restart sistemi vardır.
* **Dinamik Arayüz:** Dışarıdan dosya indirmeden, doğrudan Windows'un kendi sistem fontu koda eklenerek can ve skor göstergeleri oluşturulmuştur.
* **Puanlama Sistemi:** Oyuncunun vurduğu her düşman için puanı dinamik olarak artar ve ekrana yansır.

## Kontroller
* **Sol Yön Tuşu:** Sola hareket etmek için kullanılır.
* **Sağ Yön Tuşu:** Sağa hareket etmek için kullanılır.
* **Boşluk (Space) Tuşu:** Ateş etmek için kullanılır.
* **R Tuşu:** Oyunu sıfırlayıp yeniden başlamak için kullanılır.

## Nasıl Çalıştırılır?
Projeyi derlemek için bilgisayarda SFML kütüphanesinin kurulu ve Visual Studio projesine dahil edilmiş olması gerekir. `GalagaKlonu.sln` dosyası üzerinden projeyi açıp derleyerek çalıştırabilirsiniz.
