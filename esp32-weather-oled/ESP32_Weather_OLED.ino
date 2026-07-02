#include <WiFi.h>
#include <HTTPClient.h>
#include <WiFiClientSecure.h>
#include <ArduinoJson.h>
#include <Wire.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>

// ==================== CẤU HÌNH CHÂN I2C (SDA/SCL) ====================
// Người dùng có thể tự chọn chân GPIO phù hợp với board của mình tại đây.
// Mặc định ESP32 dùng SDA = GPIO21, SCL = GPIO22, nhưng có thể đổi sang
// bất kỳ chân GPIO khả dụng nào khác (ví dụ: 4, 5, 13, 14, 15, 16, 17, 18, 19, 23, 25, 26, 27, 32, 33...)
#define I2C_SDA_PIN 21   // Chân SDA - đổi số này nếu bạn nối dây khác
#define I2C_SCL_PIN 22   // Chân SCL - đổi số này nếu bạn nối dây khác

// ==================== WiFi ====================
const char* ssid = "TEN_WIFI_CUA_BAN";
const char* password = "MAT_KHAU_WIFI";

// ==================== Open-Meteo API ====================
const String serverPath = "https://api.open-meteo.com/v1/forecast?latitude=<LAT>&longitude=<LON>&current=temperature_2m,relative_humidity_2m";

// ==================== NTP ====================
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org", 25200); // GMT+7

// ==================== OLED SH110X ====================
Adafruit_SH1106G display(128, 64, &Wire, -1);

// ==================== Biến toàn cục ====================
unsigned long lastTime = 0;
float currentTemp = 0;
int currentHum = 0;

void setup() {
  Serial.begin(115200);

  // Khởi tạo I2C với chân SDA/SCL do người dùng chọn ở trên
  Wire.begin(I2C_SDA_PIN, I2C_SCL_PIN);

  // Khởi tạo OLED
  display.begin(0x3C, true);
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SH110X_WHITE);
  display.setCursor(0, 0);
  display.println("Dang khoi dong...");
  display.display();

  // Kết nối WiFi
  WiFi.begin(ssid, password);
  Serial.print("Dang ket noi WiFi");
  display.clearDisplay();
  display.setCursor(0, 0);
  display.println("Dang ket noi WiFi...");
  display.display();

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nDa ket noi!");
  display.clearDisplay();
  display.setCursor(0, 0);
  display.println("WiFi da ket noi!");
  display.display();
  delay(1000);

  timeClient.begin();
  timeClient.update();
  getWeatherData();
  setDisplay();
}

void loop() {
  timeClient.update();

  if (millis() - lastTime > 15000) {
    if (WiFi.status() == WL_CONNECTED) {
      getWeatherData();
    }
    lastTime = millis();
  }

  setDisplay();
  delay(1000);
}

void getWeatherData() {
  HTTPClient http;
  WiFiClientSecure client;
  client.setInsecure();

  http.begin(client, serverPath);
  int httpCode = http.GET();

  if (httpCode == 200) {
    String payload = http.getString();
    DynamicJsonDocument doc(2048);
    if (deserializeJson(doc, payload) == DeserializationError::Ok) {
      currentTemp = doc["current"]["temperature_2m"];
      currentHum = doc["current"]["relative_humidity_2m"];
    }
  }

  http.end();
}

void setDisplay() {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SH110X_WHITE);
  display.setCursor(0, 0);

  display.println("Weather Tokyo");
  display.print("Time: ");
  display.println(timeClient.getFormattedTime());
  display.print("Temp: ");
  display.print(currentTemp);
  display.println(" C");
  display.print("Hum: ");
  display.print(currentHum);
  display.println(" %");

  display.display();
}
