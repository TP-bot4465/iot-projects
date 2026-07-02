
# ESP32 Bluetooth Speaker (I2S + MAX98357A)

Biến ESP32 thành một loa Bluetooth (A2DP Sink) đơn giản: điện thoại kết nối Bluetooth tới ESP32, âm thanh được xuất ra loa qua giao tiếp **I2S** thông qua ampli **MAX98357A**.

## Demo hoạt động

1. Cấp nguồn cho ESP32
2. Mở Bluetooth trên điện thoại, tìm và kết nối thiết bị tên **`ESP32_LOA`**
3. Phát nhạc/video trên điện thoại như bình thường → âm thanh phát ra qua loa gắn với ESP32

```
Khoi dong ESP32 Bluetooth Speaker...
San sang! Hay mo Bluetooth tren dien thoai va ket noi voi 'ESP32_LOA'
```


https://github.com/user-attachments/assets/ec027887-4252-4335-9a48-ce9f8d313ffc



## Tính năng

- Nhận âm thanh qua Bluetooth A2DP (Sink) — không cần app riêng, dùng Bluetooth mặc định của điện thoại
- Xuất âm thanh chất lượng qua giao tiếp số I2S (không qua DAC analog trung gian, ít nhiễu hơn PWM)
- Tên thiết bị Bluetooth (`ESP32_LOA`) và mức âm lượng mặc định có thể chỉnh trong code
- **Chân I2S (BCLK, LRC, DIN) hoàn toàn có thể tùy chỉnh** theo board và cách đấu dây thực tế của bạn

## Phần cứng sử dụng

| Linh kiện                        | Số lượng |
|-----------------------------------|----------|
| ESP32 DevKit (có Bluetooth Classic) | 1      |
| Ampli I2S MAX98357A                | 1        |
| Loa 3W 4-8Ω                         | 1        |
| Dây jumper                         | 7        |

> **Lưu ý board:** Dự án dùng **Bluetooth Classic (A2DP)**, chỉ hoạt động trên các dòng ESP32 có hỗ trợ Bluetooth Classic (ESP32, ESP32-S0WD, ESP32-WROOM...). **ESP32-S3/S2/C3 không hỗ trợ Bluetooth Classic** nên không chạy được code này.

## Sơ đồ đấu nối (Wiring)

**QUAN TRỌNG:** Sơ đồ dây thực tế của bạn (trong ảnh) **khác với số chân mặc định đang khai báo trong code** (`BCLK=26, LRC=25, DIN=33`). Bảng dưới đây mô tả theo **màu dây** trong sơ đồ — bạn cần đối chiếu với đúng số GPIO in trên board ESP32 của mình tại vị trí dây cắm vào, rồi cập nhật lại trong code (xem mục [Tùy chỉnh chân I2S](#tùy-chỉnh-chân-i2s) bên dưới).

| MAX98357A | Vai trò | Nối tới ESP32 | Màu dây trong sơ đồ |
|-----------|---------|----------------|----------------------|
| SPK+ / SPK− | Ngõ ra loa | Loa (2 chân) | Đỏ / Đen |
| VIN | Nguồn 3.3V/5V | Chân nguồn ESP32 | Cam nhạt |
| GND | Nối đất | Chân GND ESP32 | Xanh dương đậm / Xanh lá đậm |
| DIN | Data In (I2S) | GPIO (theo sơ đồ) | Vàng |
| BCLK | Bit Clock (I2S) | GPIO (theo sơ đồ) | Cam |
| LRC (WS) | Word Select (I2S) | GPIO (theo sơ đồ) | — (theo sơ đồ) |

>  Vì chữ số GPIO trên board trong ảnh khá nhỏ và có thể khó đọc chính xác 100%, **bạn nên tự kiểm tra lại trực tiếp trên board ESP32 thật của mình** xem mỗi dây màu đang cắm vào chân GPIO số mấy, rồi điền đúng số đó vào code — tránh cấp nhầm chân gây lỗi không lên tiếng hoặc chập mạch.

<img width="632" height="597" alt="wiring_diagram_1" src="https://github.com/user-attachments/assets/7fd7898b-0f1d-4bac-ae21-9c4ec8e7b68b" />


## Yêu cầu thư viện (cài thủ công bằng ZIP — không có trên Library Manager)

1. Tải ZIP: [ESP32-A2DP](https://github.com/pschatzmann/ESP32-A2DP) → **Code → Download ZIP**
2. Tải ZIP: [arduino-audio-tools](https://github.com/pschatzmann/arduino-audio-tools) → **Code → Download ZIP**
3. Trong Arduino IDE: **Sketch → Include Library → Add .ZIP Library...** — làm lần lượt với cả 2 file ZIP vừa tải

## Cài đặt & Sử dụng

1. Clone hoặc tải project về:
   ```bash
   git clone https://github.com/username/esp32-bluetooth-speaker.git
   ```
2. Mở file `.ino` bằng Arduino IDE.
3. Cài đặt board **ESP32** trong Arduino IDE (nếu chưa có), chọn đúng board hỗ trợ Bluetooth Classic.
4. Cài 2 thư viện ZIP như hướng dẫn ở mục trên.
5. **Đối chiếu và cập nhật lại chân I2S** cho khớp với cách bạn đấu dây thực tế (xem mục dưới).
6. Nạp code vào ESP32 và mở Serial Monitor (baud `115200`) để theo dõi.
7. Mở Bluetooth trên điện thoại, kết nối với thiết bị **`ESP32_LOA`**, phát nhạc và nghe qua loa.

## Tùy chỉnh chân I2S

Chân I2S được khai báo ở đầu file để dễ chỉnh sửa — **đây là phần bạn chắc chắn cần đổi** vì sơ đồ đấu dây của bạn khác với giá trị mặc định:

```cpp
#define I2S_BCLK_PIN   26   // ⚠️ Đổi theo đúng GPIO bạn đã nối dây BCLK trong sơ đồ
#define I2S_LRC_PIN    25   // ⚠️ Đổi theo đúng GPIO bạn đã nối dây LRC trong sơ đồ
#define I2S_DOUT_PIN   33   // ⚠️ Đổi theo đúng GPIO bạn đã nối dây DIN trong sơ đồ
```

Và được áp dụng khi cấu hình I2S trong `setup()`:

```cpp
auto cfg = i2s.defaultConfig();
cfg.pin_bck  = I2S_BCLK_PIN;
cfg.pin_ws   = I2S_LRC_PIN;
cfg.pin_data = I2S_DOUT_PIN;
i2s.begin(cfg);
```

Chỉ cần sửa 3 giá trị số ở phần `#define` cho khớp với board/sơ đồ dây thật của bạn — không cần sửa gì thêm ở chỗ khác trong code. Có thể dùng hầu hết các chân GPIO còn trống của ESP32 (tránh các chân input-only như GPIO 34–39 vì I2S cần chân có thể xuất tín hiệu).

## Tùy chỉnh tên thiết bị & âm lượng

Trong hàm `setup()`, có thể đổi trực tiếp:

```cpp
a2dp_sink.set_volume(80);      // Mức âm lượng mặc định (0–127)
a2dp_sink.start("ESP32_LOA");  // Tên thiết bị hiện trên danh sách Bluetooth của điện thoại
```

## Cấu trúc thư mục

```
esp32-bluetooth-speaker/
├── ESP32_Bluetooth_Speaker.ino
├── wiring_diagram.png
└── README.md
```

## License

MIT License — tự do sử dụng, chỉnh sửa và phân phối.
