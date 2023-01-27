# Otonom-Kara-Aracı-
Bu çalışma kapsamında GPS alıcısı ve manyetometre sensörü kullanılarak kara aracının istenilen konuma gitmesi gerçekleştirilmiştir.
Neo 6M GPS alıcısı kullanılarak aracın sürekli olarak konum bilgilerini elde etmesi sağlanmıştır.
HMC5883L Manyetometre sensörü pusula olarak yön bulmak için kullanılmıştır.
ESP32 üzerinde oluşturulan web server üzerinden aracın gitmesi istenilen konum (enlem - boylam) bilgileri alınmaktadır.
Alınan enlem ve boylam bilgileri aracın GPS üzerinden aldığı verilerle kıyaslanarak iki nokta arasındaki mesafe ve açı ölçülmektedir.
Web Server üzerinden veri göndermek için google maps uygulaması üzerinde bir nokta seçilip enlem ve boylam bilgileri aktarılmalıdır.

Neo 6M GPS:
Neo 6M GPS modülü aracın sürekli olarak konum tespiti yapması için kullanılacaktır. Bu modül uydulardan elde ettiğin sinyalleri NMEA (National Marine Electronics Association) standartlarına göre işlemektedir. Bu çalışmada sadece GPS'ten elde edilecek enlem ve boylam bilgileri kullanılacağı için $GPGGA cümlesi seçilmiştir. $GPGGA,1235719,4807.038,N,01131.000,E,1,08,0.9,545.4,M,46.9,M,,*47 örnek satırı ele alınacak olursa;
4807.038 enlemi temsil eder
01131.000 boylamı temsil eder.
fakat bu veriler ddmm.mm formatındadır. Harita üzerinde konum tespiti yapmak için GPS resminde bulunan örnek işlem yapılmalıdır. Daha sonra elde edilen veriler konum tespiti yapmak için kullanılabilir.
HMC5883L:
HMC5883L bir manyetometre sensörüdür ve aracın pusula görevini üstlenmektedir. 0-360 derece arasında değer vermektedir. Hedef konuma gitmek için aracın manyetik kuzey ile yaptığı açıyı tespit eder. Daha sonra manyetik kuzey açısı ile hedef konum ile arasında bulunan açı haversine formülü ile elde edilir ve aracın doğru yönde hareket etmesi sağlanır. 
ESP32:
ESP32 mikrodenetleyicisi aracın kontrolünü sağlamaktadır. ESP32 üzerinde bir webserver kurularak hedef konum bilgileri bu arayüz üzerinden iletilmektedir. Mikrodenetleyici üzerinden motor kontrolleri, konum verilerinin işlenmesi, hedefe olan mesafe ölçümü, açı ölçümleri yapılmaktadır.
L298N:
L298N motor sürücüsü aracın motorlarının hareket etmesini sağlamaktadır.Üzerinde bulundurduğu H köprüsü ile motorların çift yönlü hareket edebilmesini sağladığı gibi açı tespit edildikten sonra aracın doğru yönü bulmasını ve hareket etmesini sağlar.

Video Linkleri:
https://youtu.be/0Ap6bzg-jPk
https://youtu.be/xjIi3h4CWLg
