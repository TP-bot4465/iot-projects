# ESP32 Weather Station với OLED SH1106

Trạm thời tiết mini sử dụng **ESP32** và màn hình **OLED SH1106 (1.3" I2C)**, hiển thị **giờ thực (NTP)**, **nhiệt độ** và **độ ẩm** theo thời gian thực, lấy dữ liệu miễn phí từ **Open-Meteo API**.

## Demo hiển thị

Màn hình OLED hiển thị:

<img width="2560" height="1440" alt="image" src="https://github.com/user-attachments/assets/ae206a45-c679-4fd1-9e55-fc6132cf604a" />


## Tính năng

- Kết nối WiFi tự động, hiển thị trạng thái kết nối trên OLED
- Lấy dữ liệu thời tiết (nhiệt độ, độ ẩm) từ [Open-Meteo API](https://open-meteo.com/) — không cần API key
- Đồng bộ giờ thực qua NTP (múi giờ GMT+7)
- Tự động cập nhật dữ liệu thời tiết mỗi 15 giây
- Chân I2C (SDA/SCL) có thể tùy chỉnh dễ dàng trong code
- Nội dung chữ hiển thị trên OLED (tiêu đề, nhãn...) có thể tùy biến theo ý muốn

## Phần cứng sử dụng

| Linh kiện       | Số lượng |
|-----------------|----------|
| ESP32 DevKit V1  | 1        |
| Màn hình OLED SH1106 1.3" (I2C) | 1 |
| Dây jumper       | 4        |

## Sơ đồ đấu nối (Wiring)

| OLED SH1106 | ESP32          | Màu dây (gợi ý) |
|-------------|----------------|-----------------|
| GND         | GND            | Đen             |
| VCC         | 5V (VIN)       | Đỏ              |
| SCL         | GPIO 22        | Xanh lá         |
| SDA         | GPIO 21        | Xanh lá         |

> **Lưu ý:** Đây là chân mặc định của ESP32 cho giao tiếp I2C. Bạn hoàn toàn có thể đổi sang chân GPIO khác phù hợp với board của mình — xem phần [Tùy chỉnh chân SDA/SCL](#tùy-chỉnh-chân-sdascl) bên dưới.


<img width="1010" height="685" alt="image" src="https://github.com/user-attachments/assets/0c2517a8-34de-4f16-87e4-d362ce246a8d" />

## Yêu cầu thư viện (Arduino IDE)

Cài đặt các thư viện sau qua **Library Manager**:

- `WiFi` (có sẵn trong ESP32 core)
- `HTTPClient` (có sẵn trong ESP32 core)
- `WiFiClientSecure` (có sẵn trong ESP32 core)
- `ArduinoJson` (Benoit Blanchon)
- `NTPClient` (Fabrice Weinberg)
- `Adafruit GFX Library`
- `Adafruit SH110X`

## Cài đặt & Sử dụng

1. Clone hoặc tải project về:
   ```bash
   git clone https://github.com/username/esp32-weather-oled.git
   ```
2. Mở file `ESP32_Weather_OLED.ino` bằng Arduino IDE.
3. Cài đặt board **ESP32** trong Arduino IDE (nếu chưa có), chọn đúng board (VD: `ESP32 Dev Module`).
4. Cài đặt đầy đủ các thư viện ở mục trên.
5. Sửa thông tin WiFi trong code:
   ```cpp
   const char* ssid = "TEN_WIFI_CUA_BAN";
   const char* password = "MAT_KHAU_WIFI";
   ```
6. (Tùy chọn) Sửa tọa độ trong `serverPath` để lấy thời tiết đúng vị trí bạn muốn (mặc định đang là Tokyo).
7. Nạp code vào ESP32 và mở Serial Monitor (baud `115200`) để theo dõi.

## Tùy chỉnh chân SDA/SCL

Trong code, phần khai báo chân I2C được đặt ở đầu file để dễ chỉnh sửa:

```cpp
#define I2C_SDA_PIN 21   // Đổi số này nếu bạn nối dây SDA vào chân khác
#define I2C_SCL_PIN 22   // Đổi số này nếu bạn nối dây SCL vào chân khác
```

Và được áp dụng khi khởi tạo I2C trong `setup()`:

```cpp
Wire.begin(I2C_SDA_PIN, I2C_SCL_PIN);
```

Nếu bạn đấu OLED vào các chân khác (ví dụ GPIO 4 và GPIO 5), chỉ cần đổi 2 giá trị trên cho khớp với sơ đồ đấu dây thực tế, không cần sửa chỗ nào khác trong code.

## Tùy chỉnh nội dung hiển thị trên OLED

Toàn bộ chữ hiển thị trên màn hình (tiêu đề, nhãn "Time", "Temp", "Hum"...) nằm trong hàm `setDisplay()`, bạn có thể sửa trực tiếp theo ý muốn:

```cpp
void setDisplay() {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SH110X_WHITE);
  display.setCursor(0, 0);

  display.println("Weather Tokyo");   // Đổi thành tên địa điểm/tiêu đề bạn muốn
  display.print("Time: ");            // Đổi nhãn giờ, ví dụ "Gio: "
  display.println(timeClient.getFormattedTime());
  display.print("Temp: ");            // Đổi nhãn nhiệt độ, ví dụ "Nhiet do: "
  display.print(currentTemp);
  display.println(" C");
  display.print("Hum: ");             // Đổi nhãn độ ẩm, ví dụ "Do am: "
  display.print(currentHum);
  display.println(" %");

  display.display();
}
```

Một vài gợi ý tùy biến thường gặp:

- **Đổi tiêu đề:** sửa chuỗi `"Weather Tokyo"` thành tên bạn muốn, ví dụ `"Tram thoi tiet nha"`.
- **Đổi cỡ chữ:** thay `display.setTextSize(1)` thành `2` hoặc `3` để chữ to hơn (lưu ý màn hình chỉ rộng 128x64px nên chữ to sẽ hiển thị ít nội dung hơn).
- **Đổi bố cục:** dùng `display.setCursor(x, y)` trước mỗi dòng để tự sắp xếp vị trí chữ theo ý muốn thay vì in tuần tự từ trên xuống.
- **Thêm dòng mới:** chỉ cần thêm `display.println("...")` vào bất kỳ đâu trong hàm, miễn không vượt quá chiều cao màn hình (64px, tương đương khoảng 8 dòng chữ cỡ 1).

> **Lưu ý:** Toàn bộ thay đổi ở mục này chỉ ảnh hưởng đến chữ hiển thị trên OLED, không ảnh hưởng đến logic lấy dữ liệu WiFi/thời tiết.

## Cấu hình vị trí thời tiết

Mặc định tọa độ trong code là Tokyo (`latitude=35.6895&longitude=139.6917`). Để đổi sang vị trí khác, thay tọa độ trong biến `serverPath`:

```cpp
const String serverPath = "https://api.open-meteo.com/v1/forecast?latitude=<LAT>&longitude=<LON>&current=temperature_2m,relative_humidity_2m";
```

Bạn có thể tra tọa độ tại [latlong.net](https://www.latlong.net/).

## Cấu trúc thư mục

```
esp32-weather-oled/
├── ESP32_Weather_OLED.ino
├── wiring_diagram.png
└── README.md
```

## License

MIT License — tự do sử dụng, chỉnh sửa và phân phối.
