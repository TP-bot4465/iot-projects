# ESP32 Bluetooth Speaker (I2S + MAX98357A)

Dự án biến **ESP32** thành một loa Bluetooth sử dụng chế độ **A2DP Sink**. Điện thoại hoặc thiết bị phát kết nối với ESP32 thông qua Bluetooth, sau đó tín hiệu âm thanh được truyền đến module khuếch đại **MAX98357A** bằng giao tiếp số **I2S** và phát ra loa.

Hệ thống không yêu cầu ứng dụng điều khiển riêng, phù hợp để nghiên cứu về Bluetooth Classic, truyền âm thanh không dây, giao tiếp I2S và các ứng dụng âm thanh nhúng trên ESP32.

---

# Demo hoạt động

Quy trình hoạt động của hệ thống:

1. Cấp nguồn cho ESP32.
2. ESP32 khởi tạo Bluetooth và hệ thống âm thanh I2S.
3. Mở Bluetooth trên điện thoại.
4. Tìm và kết nối với thiết bị có tên **`ESP32_LOA`**.
5. Phát nhạc hoặc video trên điện thoại.
6. Âm thanh được truyền qua Bluetooth đến ESP32 và phát ra loa thông qua module MAX98357A.

Thông báo hiển thị trên Serial Monitor:

```text
Khoi dong ESP32 Bluetooth Speaker...
San sang! Hay mo Bluetooth tren dien thoai va ket noi voi 'ESP32_LOA'
```

Video minh họa:

https://github.com/user-attachments/assets/ec027887-4252-4335-9a48-ce9f8d313ffc

---

# Tính năng

* Nhận âm thanh từ điện thoại thông qua Bluetooth A2DP ở chế độ Sink.
* Không yêu cầu cài đặt ứng dụng điều khiển riêng.
* Hỗ trợ phát nhạc, âm thanh video và các nội dung đa phương tiện từ điện thoại.
* Truyền tín hiệu âm thanh số đến module MAX98357A thông qua giao tiếp I2S.
* Hạn chế nhiễu tín hiệu do không sử dụng phương pháp xuất âm thanh PWM hoặc DAC analog trung gian.
* Cho phép thay đổi tên thiết bị Bluetooth trực tiếp trong chương trình.
* Cho phép thiết lập mức âm lượng mặc định.
* Có thể tùy chỉnh các chân I2S gồm BCLK, LRC và DOUT theo sơ đồ kết nối thực tế.
* Hiển thị trạng thái khởi động và kết nối thông qua Serial Monitor.

---

# Phần cứng sử dụng

| Linh kiện                                |             Số lượng |
| ---------------------------------------- | -------------------: |
| ESP32 DevKit có hỗ trợ Bluetooth Classic |                    1 |
| Module khuếch đại âm thanh I2S MAX98357A |                    1 |
| Loa 3 W, trở kháng 4–8 Ω                 |                    1 |
| Dây jumper                               | Theo nhu cầu kết nối |

Dự án sử dụng giao thức **Bluetooth Classic A2DP**, vì vậy cần lựa chọn dòng ESP32 có hỗ trợ Bluetooth Classic, chẳng hạn như:

* ESP32 DevKit V1.
* ESP32-WROOM-32.
* ESP32-WROVER.
* Các bo mạch sử dụng chip ESP32 thế hệ đầu.

Các dòng như **ESP32-S2**, **ESP32-S3** và **ESP32-C3** không hỗ trợ Bluetooth Classic A2DP nên không phù hợp với chương trình này.

---

# Sơ đồ đấu nối (Wiring)

Sơ đồ dưới đây sử dụng cấu hình chân I2S mặc định trong chương trình:

| MAX98357A   | Vai trò                | ESP32         |
| ----------- | ---------------------- | ------------- |
| VIN         | Nguồn cấp cho module   | 5V hoặc VIN   |
| GND         | Nối đất                | GND           |
| DIN         | Dữ liệu âm thanh I2S   | GPIO 33       |
| BCLK        | Xung nhịp dữ liệu I2S  | GPIO 26       |
| LRC hoặc WS | Lựa chọn kênh âm thanh | GPIO 25       |
| SPK+        | Ngõ ra dương của loa   | Cực dương loa |
| SPK−        | Ngõ ra âm của loa      | Cực âm loa    |

Hình ảnh sơ đồ đấu nối:

<img width="632" height="597" alt="Sơ đồ kết nối ESP32 với MAX98357A" src="https://github.com/user-attachments/assets/7fd7898b-0f1d-4bac-ae21-9c4ec8e7b68b" />

Các chân I2S có thể được thay đổi tùy theo bo mạch và cách bố trí phần cứng. Khi thay đổi sơ đồ kết nối, cần cập nhật lại các chân GPIO tương ứng trong chương trình.

---

# Yêu cầu thư viện

Dự án sử dụng hai thư viện:

* `ESP32-A2DP`
* `arduino-audio-tools`

Các thư viện được cài đặt thủ công bằng tệp ZIP.

## Bước 1. Tải thư viện ESP32-A2DP

Truy cập kho mã nguồn:

https://github.com/pschatzmann/ESP32-A2DP

Chọn:

```text
Code → Download ZIP
```

## Bước 2. Tải thư viện arduino-audio-tools

Truy cập kho mã nguồn:

https://github.com/pschatzmann/arduino-audio-tools

Chọn:

```text
Code → Download ZIP
```

## Bước 3. Cài đặt thư viện trong Arduino IDE

Trong Arduino IDE, chọn:

```text
Sketch → Include Library → Add .ZIP Library...
```

Thực hiện lần lượt với hai tệp ZIP vừa tải.

---

# Cài đặt và sử dụng

## Bước 1. Tải mã nguồn

```bash
git clone https://github.com/username/esp32-bluetooth-speaker.git
```

---

## Bước 2. Mở dự án

Mở tệp `ESP32_Bluetooth_Speaker.ino` bằng Arduino IDE.

---

## Bước 3. Chọn bo mạch

Trong Arduino IDE:

* Chọn bo mạch ESP32 có hỗ trợ Bluetooth Classic.
* Ví dụ: **ESP32 Dev Module**.
* Chọn đúng cổng COM của thiết bị.

---

## Bước 4. Cài đặt thư viện

Cài đặt đầy đủ hai thư viện:

* `ESP32-A2DP`
* `arduino-audio-tools`

---

## Bước 5. Kiểm tra chân I2S

Đối chiếu các chân BCLK, LRC và DIN trên module MAX98357A với các chân được khai báo trong chương trình.

Cấu hình mặc định:

```cpp
#define I2S_BCLK_PIN 26
#define I2S_LRC_PIN  25
#define I2S_DOUT_PIN 33
```

---

## Bước 6. Nạp chương trình

1. Kết nối ESP32 với máy tính.
2. Chọn đúng bo mạch và cổng COM.
3. Nhấn **Upload** để nạp chương trình.
4. Mở Serial Monitor với baudrate `115200`.

---

## Bước 7. Kết nối Bluetooth

1. Mở Bluetooth trên điện thoại.
2. Tìm thiết bị có tên **`ESP32_LOA`**.
3. Thực hiện kết nối.
4. Phát nhạc hoặc video trên điện thoại.
5. Âm thanh sẽ được phát qua loa nối với module MAX98357A.

---

# Tùy chỉnh chân I2S

Các chân giao tiếp I2S được khai báo ở đầu chương trình:

```cpp
#define I2S_BCLK_PIN 26
#define I2S_LRC_PIN  25
#define I2S_DOUT_PIN 33
```

Ý nghĩa của từng chân:

| Hằng số        | Chức năng                                                                   |
| -------------- | --------------------------------------------------------------------------- |
| `I2S_BCLK_PIN` | Xuất tín hiệu Bit Clock đến chân BCLK của MAX98357A.                        |
| `I2S_LRC_PIN`  | Xuất tín hiệu Word Select hoặc Left/Right Clock đến chân LRC của MAX98357A. |
| `I2S_DOUT_PIN` | Xuất dữ liệu âm thanh đến chân DIN của MAX98357A.                           |

Các chân được áp dụng khi cấu hình giao tiếp I2S:

```cpp
auto cfg = i2s.defaultConfig();

cfg.pin_bck  = I2S_BCLK_PIN;
cfg.pin_ws   = I2S_LRC_PIN;
cfg.pin_data = I2S_DOUT_PIN;

i2s.begin(cfg);
```

Khi sử dụng sơ đồ chân khác, chỉ cần thay đổi ba giá trị trong phần `#define`.

Nên lựa chọn các chân GPIO có khả năng xuất tín hiệu. Không sử dụng các chân chỉ hỗ trợ đầu vào như GPIO 34, 35, 36 và 39 cho tín hiệu I2S.

---

# Tùy chỉnh tên thiết bị và âm lượng

Tên thiết bị Bluetooth và mức âm lượng mặc định được thiết lập trong hàm `setup()`:

```cpp
a2dp_sink.set_volume(80);
a2dp_sink.start("ESP32_LOA");
```

## Thay đổi âm lượng

```cpp
a2dp_sink.set_volume(80);
```

Giá trị âm lượng nằm trong khoảng:

```text
0–127
```

Trong đó:

* `0`: tắt âm thanh.
* `127`: mức âm lượng lớn nhất.

Ví dụ, đặt âm lượng mặc định thành 60:

```cpp
a2dp_sink.set_volume(60);
```

## Thay đổi tên thiết bị Bluetooth

```cpp
a2dp_sink.start("ESP32_LOA");
```

Có thể thay `ESP32_LOA` bằng tên khác:

```cpp
a2dp_sink.start("TEKY_SPEAKER");
```

Sau khi thay đổi tên và nạp lại chương trình, thiết bị sẽ xuất hiện với tên mới trong danh sách Bluetooth của điện thoại.

---

# Nguyên lý hoạt động

ESP32 hoạt động ở chế độ **Bluetooth A2DP Sink**, có nhiệm vụ nhận luồng âm thanh từ điện thoại.

Quy trình truyền âm thanh:

```text
Điện thoại
    ↓ Bluetooth A2DP
ESP32
    ↓ Dữ liệu âm thanh I2S
MAX98357A
    ↓ Tín hiệu khuếch đại
Loa
```

Trong hệ thống:

* Điện thoại đóng vai trò **A2DP Source**.
* ESP32 đóng vai trò **A2DP Sink**.
* MAX98357A nhận dữ liệu âm thanh số I2S.
* MAX98357A chuyển đổi và khuếch đại tín hiệu để điều khiển loa.

---

# Cấu trúc thư mục

```text
esp32-bluetooth-speaker/
├── ESP32_Bluetooth_Speaker.ino
└── README.md
```

Trong đó:

* `ESP32_Bluetooth_Speaker.ino`: chương trình chính của dự án.
* `README.md`: tài liệu mô tả, hướng dẫn kết nối và sử dụng hệ thống.

---

# Giới hạn và lưu ý kỹ thuật

* Chương trình yêu cầu bo mạch hỗ trợ Bluetooth Classic A2DP.
* Chất lượng âm thanh phụ thuộc vào nguồn cấp, loa và cách đấu nối module MAX98357A.
* Nên sử dụng nguồn cấp ổn định khi phát âm thanh ở mức âm lượng lớn.
* Cần nối chung GND giữa ESP32 và MAX98357A.
* Không kết nối trực tiếp loa vào chân GPIO của ESP32.
* Loa phải được kết nối với hai đầu ra `SPK+` và `SPK−` của MAX98357A.
* Không nối một đầu loa xuống GND vì ngõ ra của MAX98357A hoạt động theo kiểu cầu BTL.
* Nên đặt dây tín hiệu I2S ngắn để giảm nhiễu và tăng độ ổn định.
* Nếu thiết bị Bluetooth cũ vẫn còn được lưu trên điện thoại sau khi đổi tên, có thể xóa thiết bị đã ghép đôi và thực hiện kết nối lại.

---

# License

Dự án được phát hành theo **MIT License**.

Người dùng được phép sử dụng, chỉnh sửa, phân phối và phát triển tiếp dự án theo các điều khoản của giấy phép MIT.
