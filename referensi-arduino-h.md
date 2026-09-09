# Referensi Fungsi & Konstanta `Arduino.h`

Dikategorikan berdasarkan yang kamu pakai (atau akan pakai) di proyek ESP32 + HC-SR04 ini.

---

## 1. Konstanta

Konstanta = nilai tetap yang sudah didefinisikan framework, supaya kode lebih mudah dibaca dibanding pakai angka mentah.

| Konstanta | Nilai asli | Penjelasan |
|---|---|---|
| `HIGH` | `1` | Merepresentasikan tegangan "menyala" (biasanya 3.3V di ESP32). Dipakai untuk mengatur atau membaca kondisi pin. |
| `LOW` | `0` | Merepresentasikan tegangan "mati" (0V). Kebalikan dari `HIGH`. |
| `INPUT` | `0` | Mode pin: pin dipakai untuk **membaca** sinyal dari luar (misal dari sensor). |
| `OUTPUT` | `1` | Mode pin: pin dipakai untuk **mengirim** sinyal keluar (misal menyalakan LED atau trigger sensor). |
| `INPUT_PULLUP` | `2` | Mode pin: sama seperti `INPUT`, tapi mengaktifkan resistor pull-up internal di dalam chip. Berguna untuk tombol/switch supaya nilai default-nya `HIGH` saat tidak ditekan (kita belum pakai ini di proyek sekarang). |

**Kenapa penting?** Alih-alih menulis `pinMode(5, 1)` (angka `1` artinya apa? harus hafal), kita tulis `pinMode(5, OUTPUT)` — jauh lebih jelas dibaca.

---

## 2. Fungsi Pin Digital

Fungsi untuk mengatur atau membaca kondisi pin GPIO (General Purpose Input/Output) satu per satu.

| Fungsi | Contoh pemakaian | Penjelasan |
|---|---|---|
| `pinMode(pin, mode)` | `pinMode(TRIG_PIN, OUTPUT);` | Menentukan apakah sebuah pin dipakai untuk `INPUT` atau `OUTPUT`. **Wajib** dipanggil sekali di `setup()` sebelum pin itu dipakai. |
| `digitalWrite(pin, value)` | `digitalWrite(TRIG_PIN, HIGH);` | Mengatur pin (yang sudah di-set `OUTPUT`) jadi `HIGH` atau `LOW`. Ini yang kita pakai untuk "mengirim" pulsa trigger ke HC-SR04. |
| `digitalRead(pin)` | `int val = digitalRead(2);` | Membaca kondisi pin (yang sudah di-set `INPUT`) — hasilnya `HIGH` atau `LOW`. Belum kita pakai di proyek ini karena Echo kita baca pakai `pulseIn`, bukan `digitalRead` biasa. |

---

## 3. Fungsi Analog

Untuk sinyal yang nilainya bertingkat (bukan cuma on/off). Belum dipakai di proyek HC-SR04 (karena sensor ini sinyalnya digital), tapi berguna untuk sensor lain seperti LM35.

| Fungsi | Contoh pemakaian | Penjelasan |
|---|---|---|
| `analogRead(pin)` | `int nilai = analogRead(34);` | Membaca tegangan analog di suatu pin, hasilnya berupa angka (di ESP32 rentangnya 0-4095, beda dengan Arduino Uno yang 0-1023). |
| `analogWrite(pin, value)` | `analogWrite(9, 128);` | Mengeluarkan sinyal PWM (simulasi sinyal analog) — sering dipakai untuk redupkan LED atau atur kecepatan motor. |

---

## 4. Fungsi Waktu

Fungsi terkait pengaturan dan pengukuran waktu — ini yang paling krusial buat HC-SR04.

| Fungsi | Contoh pemakaian | Penjelasan |
|---|---|---|
| `delay(ms)` | `delay(500);` | Menghentikan (blocking) seluruh program selama sekian **milidetik**. Selama delay, ESP32 tidak melakukan apa-apa lain. |
| `delayMicroseconds(us)` | `delayMicroseconds(10);` | Sama seperti `delay`, tapi satuannya **mikrodetik** (1 detik = 1.000.000 mikrodetik). Dipakai untuk jeda sangat singkat seperti pulsa trigger HC-SR04. |
| `millis()` | `unsigned long t = millis();` | Mengembalikan berapa milidetik sejak ESP32 mulai menyala/reset. Berguna untuk mengatur waktu tanpa "memblokir" program (alternatif dari `delay` untuk kasus lebih lanjut — belum kita pakai). |
| `pulseIn(pin, value, timeout)` | `long d = pulseIn(ECHO_PIN, HIGH, 30000);` | Mengukur berapa lama (dalam mikrodetik) sebuah pin bertahan pada kondisi tertentu (`HIGH`/`LOW`), dengan batas waktu tunggu maksimal (`timeout`). Ini inti dari cara kita membaca jarak HC-SR04. |

---

## 5. Fungsi Matematika Bawaan

Fungsi pembantu perhitungan sederhana.

| Fungsi | Contoh pemakaian | Penjelasan |
|---|---|---|
| `min(a, b)` | `min(5, 10)` → `5` | Mengembalikan nilai yang lebih kecil di antara dua angka. |
| `max(a, b)` | `max(5, 10)` → `10` | Mengembalikan nilai yang lebih besar di antara dua angka. |
| `map(val, fromLow, fromHigh, toLow, toHigh)` | `map(512, 0, 1023, 0, 255)` | Mengubah skala suatu angka dari satu rentang ke rentang lain. |
| `constrain(val, min, max)` | `constrain(150, 0, 100)` → `100` | Membatasi nilai supaya tidak melebihi batas atas/bawah tertentu. |
| `fabs(x)` | `fabs(-2.5)` → `2.5` | Mengembalikan nilai absolut (selalu positif) dari angka desimal (`float`). Ini yang kita pakai untuk hitung `delta` (selisih jarak) di logika filtering. |

---

## 6. Objek `Serial` (Komunikasi)

`Serial` bukan fungsi biasa, tapi sebuah **objek** (kumpulan fungsi/method yang berhubungan dengan komunikasi serial ke komputer, biasanya lewat USB atau ditampilkan di Serial Monitor/Wokwi).

| Method | Contoh pemakaian | Penjelasan |
|---|---|---|
| `Serial.begin(baudrate)` | `Serial.begin(115200);` | Mengaktifkan komunikasi serial dengan kecepatan tertentu (baud rate). Wajib dipanggil sekali di `setup()` sebelum pakai method `Serial` lainnya. |
| `Serial.print(data)` | `Serial.print("Jarak: ");` | Menampilkan teks/angka ke Serial Monitor, **tanpa** pindah baris di akhir. |
| `Serial.println(data)` | `Serial.println(distance);` | Sama seperti `print`, tapi otomatis pindah baris di akhir. |
| `Serial.printf(format, ...)` | `Serial.printf("Jarak: %.2f cm\n", distance);` | Versi lebih fleksibel — bisa gabung teks dan angka dalam satu baris pakai format string (gaya bahasa C), mirip seperti `printf` di C. |

---

## 7. Tipe Data yang Sering Dipakai

Bukan fungsi, tapi "jenis kotak penyimpanan" data yang disediakan/dipakai bareng framework ini.

| Tipe | Contoh | Penjelasan |
|---|---|---|
| `int` | `int jumlah = 5;` | Bilangan bulat (tanpa desimal). |
| `long` | `long durasi = 30000;` | Bilangan bulat, tapi kapasitasnya lebih besar dari `int` — dipakai untuk hasil `pulseIn` yang bisa berupa angka besar. |
| `float` | `float jarak = 24.18;` | Bilangan desimal (pecahan). Dipakai untuk jarak dalam cm karena butuh presisi angka di belakang koma. |
| `const` | `const int TRIG_PIN = 5;` | Bukan tipe data, tapi "penanda" bahwa nilai variabel ini **tidak boleh diubah** setelah didefinisikan. Dipakai untuk pin & konfigurasi yang memang seharusnya tetap. |
| `String` | `String pesan = "Halo";` | Tipe data teks bawaan Arduino framework (beda dengan `std::string` C++ biasa). Kita belum pakai ini karena lebih boros memori dibanding `char array`, tapi sering muncul di contoh-contoh lain. |

---

## Catatan

Semua fungsi & konstanta di atas datang dari **framework Arduino (core)**, bukan dari library tambahan apapun — makanya semuanya sudah tersedia otomatis begitu kamu `#include <Arduino.h>` dan set `framework = arduino` di `platformio.ini`. Kalau nanti kamu pakai sensor lain yang butuh library tambahan (misal `DHT.h`), fungsi-fungsi barunya (`dht.readTemperature()`, dst) baru akan tersedia setelah kamu install & include library itu secara terpisah.
