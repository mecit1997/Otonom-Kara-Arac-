# Otonom-Kara-Aracı-
Bu çalışma kapsamında GPS alıcısı ve manyetometre sensörü kullanılarak kara aracının istenilen konuma gitmesi gerçekleştirilmiştir.
Neo 6M GPS alıcısı kullanılarak aracın sürekli olarak konum bilgilerini elde etmesi sağlanmıştır.
HMC5883L Manyetometre sensörü pusula olarak yön bulmak için kullanılmıştır.
ESP32 üzerinde oluşturulan web server üzerinden aracın gitmesi istenilen konum (enlem - boylam) bilgileri alınmaktadır.
Alınan enlem ve boylam bilgileri aracın GPS üzerinden aldığı verilerle kıyaslanarak iki nokta arasındaki mesafe ve açı ölçülmektedir.
Web Server üzerinden veri göndermek için google maps uygulaması üzerinde bir nokta seçilip enlem ve boylam bilgileri aktarılmalıdır.
