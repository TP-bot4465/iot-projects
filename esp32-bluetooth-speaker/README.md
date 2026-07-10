# ESP32 Bluetooth Speaker (I2S + MAX98357A)

Dự án biến **ESP32** thành loa Bluetooth ở chế độ **A2DP Sink**. Âm thanh từ điện thoại được truyền qua Bluetooth đến ESP32, sau đó xuất qua giao tiếp **I2S** đến module khuếch đại **MAX98357A** và phát ra loa.

Hệ thống không cần ứng dụng điều khiển riêng, phù hợp để tìm hiểu Bluetooth Classic, I2S và các ứng dụng âm thanh nhúng trên ESP32.

---

# Demo hoạt động

1. Cấp nguồn cho ESP32.
2. Mở Bluetooth trên điện thoại.
3. Tìm và kết nối với thiết bị **`ESP32_LOA`**.
4. Phát nhạc hoặc video.
5. Âm thanh sẽ được phát qua loa nối với MAX98357A.

Thông báo trên Serial Monitor:

```text
Khoi dong ESP32 Bluetooth Speaker...
San sang! Hay mo Bluetooth tren dien thoai va ket noi voi 'ESP32_LOA'
```

Video minh họa:

https://github.com/user-attachments/assets/ec027887-4252-4335-9a48-ce9f8d313ffc

---

# Tính năng

* Nhận âm thanh qua Bluetooth A2DP Sink.
* Không cần ứng dụng điều khiển riêng.
* Phát nhạc, video và các nội dung đa phương tiện từ điện thoại.
* Xuất âm thanh số qua giao tiếp I2S.
* Cho phép thay đổi tên Bluetooth, âm lượng và chân I2S.
* Hiển thị trạng thái hoạt động trên Serial Monitor.

---

# Phần cứng sử dụng

| Linh kiện                      |     Số lượng |
| ------------------------------ | -----------: |
| ESP32 hỗ trợ Bluetooth Classic |            1 |
| Module I2S MAX98357A           |            1 |
| Loa 3 W, trở kháng 4–8 Ω       |            1 |
| Dây jumper                     | Theo nhu cầu |

Dự án yêu cầu ESP32 hỗ trợ **Bluetooth Classic A2DP**, chẳng hạn:

* ESP32 DevKit V1.
* ESP32-WROOM-32.
* ESP32-WROVER.
* Các bo mạch dùng chip ESP32 thế hệ đầu.

Các dòng **ESP32-S2**, **ESP32-S3** và **ESP32-C3** không phù hợp vì không hỗ trợ Bluetooth Classic A2DP.

---

# Sơ đồ đấu nối (Wiring)

| MAX98357A   | Vai trò            | ESP32         |
| ----------- | ------------------ | ------------- |
| VIN         | Nguồn cấp          | 5V hoặc VIN   |
| GND         | Nối đất            | GND           |
| DIN         | Dữ liệu I2S        | GPIO 33       |
| BCLK        | Xung nhịp I2S      | GPIO 26       |
| LRC hoặc WS | Chọn kênh âm thanh | GPIO 25       |
| SPK+        | Ngõ ra loa dương   | Cực dương loa |
| SPK−        | Ngõ ra loa âm      | Cực âm loa    |

Hình ảnh sơ đồ đấu nối:

<img width="632" height="597" alt="Sơ đồ kết nối ESP32 với MAX98357A" src="https://github.com/user-attachments/assets/7fd7898b-0f1d-4bac-ae21-9c4ec8e7b68b" />

Có thể thay đổi các chân I2S tùy theo bo mạch, nhưng cần cập nhật lại trong chương trình.

---

# Yêu cầu thư viện

Dự án sử dụng:

* `ESP32-A2DP`
* `arduino-audio-tools`

## Bước 1. Tải thư viện ESP32-A2DP

https://github.com/pschatzmann/ESP32-A2DP

Chọn:

```text
Code → Download ZIP
```

## Bước 2. Tải thư viện arduino-audio-tools

https://github.com/pschatzmann/arduino-audio-tools

Chọn:

```text
Code → Download ZIP
```

## Bước 3. Cài đặt thư viện trong Arduino IDE

Chọn:

```text
Sketch → Include Library → Add .ZIP Library...
```

Sau đó cài đặt lần lượt hai tệp ZIP đã tải.

---

# Cài đặt và sử dụng

## Bước 1. Tải mã nguồn

```bash
git clone https://github.com/username/esp32-bluetooth-speaker.git
```

## Bước 2. Mở dự án

Mở tệp `ESP32_Bluetooth_Speaker.ino` bằng Arduino IDE.

## Bước 3. Chọn bo mạch

* Chọn bo mạch có hỗ trợ Bluetooth Classic.
* Ví dụ: **ESP32 Dev Module**.
* Chọn đúng cổng COM.

## Bước 4. Cài đặt thư viện

Cài đặt:

* `ESP32-A2DP`
* `arduino-audio-tools`

## Bước 5. Kiểm tra chân I2S

Cấu hình mặc định:

```cpp
#define I2S_BCLK_PIN 26
#define I2S_LRC_PIN  25
#define I2S_DOUT_PIN 33
```

## Bước 6. Nạp chương trình

1. Kết nối ESP32 với máy tính.
2. Chọn đúng bo mạch và cổng COM.
3. Nhấn **Upload**.
4. Mở Serial Monitor với baudrate `115200`.

## Bước 7. Kết nối Bluetooth

1. Mở Bluetooth trên điện thoại.
2. Tìm thiết bị **`ESP32_LOA`**.
3. Kết nối và phát nhạc hoặc video.
4. Âm thanh sẽ phát qua loa.

---

# Tùy chỉnh chân I2S

Các chân I2S được khai báo ở đầu chương trình:

```cpp
#define I2S_BCLK_PIN 26
#define I2S_LRC_PIN  25
#define I2S_DOUT_PIN 33
```

| Hằng số        | Chức năng                    |
| -------------- | ---------------------------- |
| `I2S_BCLK_PIN` | Chân Bit Clock của MAX98357A |
| `I2S_LRC_PIN`  | Chân Word Select hoặc LRC    |
| `I2S_DOUT_PIN` | Chân dữ liệu âm thanh DIN    |

Cấu hình I2S:

```cpp
auto cfg = i2s.defaultConfig();

cfg.pin_bck  = I2S_BCLK_PIN;
cfg.pin_ws   = I2S_LRC_PIN;
cfg.pin_data = I2S_DOUT_PIN;

i2s.begin(cfg);
```

Khi đổi sơ đồ đấu nối, chỉ cần thay đổi ba giá trị `#define`.

Không nên dùng các chân chỉ hỗ trợ đầu vào như GPIO 34, 35, 36 và 39.

---

# Tùy chỉnh tên thiết bị và âm lượng

Tên Bluetooth và âm lượng mặc định được thiết lập trong `setup()`:

```cpp
a2dp_sink.set_volume(80);
a2dp_sink.start("ESP32_LOA");
```

## Thay đổi âm lượng

```cpp
a2dp_sink.set_volume(80);
```

Giá trị âm lượng nằm trong khoảng `0–127`:

* `0`: tắt âm thanh.
* `127`: âm lượng lớn nhất.

Ví dụ:

```cpp
a2dp_sink.set_volume(60);
```

## Thay đổi tên thiết bị Bluetooth

```cpp
a2dp_sink.start("ESP32_LOA");
```

Có thể đổi thành:

```cpp
a2dp_sink.start("TEKY_SPEAKER");
```

Sau khi nạp lại chương trình, thiết bị sẽ xuất hiện với tên mới.

---

# Nguyên lý hoạt động

```text
Điện thoại
    ↓ Bluetooth A2DP
ESP32
    ↓ Dữ liệu âm thanh I2S
MAX98357A
    ↓ Tín hiệu khuếch đại
Loa
```

Trong đó:

* Điện thoại là **A2DP Source**.
* ESP32 là **A2DP Sink**.
* MAX98357A nhận và khuếch đại tín hiệu âm thanh I2S.
* Loa phát âm thanh đầu ra.

---

# Cấu trúc thư mục

```text
esp32-bluetooth-speaker/
├── ESP32_Bluetooth_Speaker.ino
└── README.md
```

* `ESP32_Bluetooth_Speaker.ino`: chương trình chính.
* `README.md`: hướng dẫn kết nối và sử dụng.

---

# Giới hạn và lưu ý kỹ thuật

* Chỉ sử dụng ESP32 có hỗ trợ Bluetooth Classic.
* Cần nối chung GND giữa ESP32 và MAX98357A.
* Không kết nối loa trực tiếp với GPIO của ESP32.
* Kết nối loa vào hai chân `SPK+` và `SPK−`.
* Không nối một đầu loa xuống GND vì MAX98357A sử dụng ngõ ra cầu BTL.
* Nên sử dụng nguồn ổn định khi phát âm lượng lớn.
* Nên giữ dây tín hiệu I2S ngắn để hạn chế nhiễu.
* Khi đổi tên Bluetooth, có thể cần xóa thiết bị đã ghép đôi trên điện thoại rồi kết nối lại.

---

# License

Dự án được phát hành theo **MIT License**.

Người dùng được phép sử dụng, chỉnh sửa và phân phối dự án theo các điều khoản của giấy phép MIT.
