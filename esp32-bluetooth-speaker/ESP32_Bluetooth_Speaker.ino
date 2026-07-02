/*
  CÀI THƯ VIỆN (không có trên Library Manager, phải cài bằng ZIP/Git):
  1. Tải ZIP:  https://github.com/pschatzmann/ESP32-A2DP        -> Code > Download ZIP
  2. Tải ZIP:  https://github.com/pschatzmann/arduino-audio-tools -> Code > Download ZIP
  3. Arduino IDE: Sketch > Include Library > Add .ZIP Library... (làm với cả 2 file)
*/

#include "AudioTools.h"
#include "BluetoothA2DPSink.h"

// ----- Cấu hình chân I2S nối với MAX98357A -----
#define I2S_BCLK_PIN   26   
#define I2S_LRC_PIN    25   
#define I2S_DOUT_PIN   33   

I2SStream i2s;
BluetoothA2DPSink a2dp_sink(i2s);

void setup() {
  Serial.begin(115200);
  Serial.println("Khoi dong ESP32 Bluetooth Speaker...");

  // Cấu hình chân I2S tùy chỉnh trước khi start
  auto cfg = i2s.defaultConfig();
  cfg.pin_bck  = I2S_BCLK_PIN;
  cfg.pin_ws   = I2S_LRC_PIN;
  cfg.pin_data = I2S_DOUT_PIN;  
  i2s.begin(cfg);

  a2dp_sink.set_volume(80);
  a2dp_sink.start("ESP32_LOA");

  Serial.println("San sang! Hay mo Bluetooth tren dien thoai va ket noi voi 'ESP32_LOA'");
}

void loop() {
  delay(1000);
}