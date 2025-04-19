# Họ và tên: Nguyễn Minh Quân - MSV: 24022825
# SDL Project - Brick Breaker

## 🎮 Giới thiệu về game
Brick Breaker là một trò chơi được phát triển bằng ngôn ngữ lập trình C++ sử dụng thư viện SDL2, nơi người chơi điều khiển một thanh trượt để phá vỡ các viên gạch bằng một quả bóng. Trò chơi mang lại trải nghiệm thú vị và thử thách với các chế độ khác nhau và cơ chế va chạm vật lý cơ bản. Người chơi có thể dùng game này để giải trí và thư giãn sau một ngày học tập và làm việc mệt mỏi khi game không có quá nhiều sự cạnh tranh và căng thẳng 🤣🤣.	 

---

## 🗂️ Cấu trúc dự án
Dưới đây là cấu trúc thư mục và mô tả các thành phần chính:

```
├── src/                # Mã nguồn chính của game
│   ├── main.cpp        # File chính để khởi chạy game
│   ├── game.cpp        # Xử lý logic game
│   ├── paddle.cpp      # Điều khiển thanh trượt
│   ├── ball.cpp        # Xử lý logic bóng
│   ├── brick.cpp       # Xử lý logic viên gạch
│   ├── menu.cpp        # Xử lý logic menu
│   ├── slider.cpp      # Xử lý logic thanh trượt tăng giảm âm lượng
├── assets/             # Tài nguyên của game
│   ├── image/         # Hình ảnh cho thanh trượt, bóng, và gạch
│   ├── sound/         # Hiệu ứng âm thanh khi bóng chạm gạch và thanh trượt, nhạc background
│   ├── font/          # Phông chữ sử dụng trong giao diện
├── build/              # File thực thi sau khi build (Windows/Linux)
├── README.md           # Hướng dẫn chi tiết
```

---

## **✨ Tính năng chính của game**

- **🕹️ Điều khiển đơn giản:**  
  Chỉ cần dùng phím mũi tên trái/phải là điều khiển paddle được rồi. Dễ chơi, ai cũng làm quen nhanh.

- **⚽ Bóng bật vui tai:**  
  Bóng sẽ nảy qua lại khi va vào paddle hoặc gạch. Cảm giác nghe tiếng “bộp” khi trúng gạch nó đã tai lắm 😆

- **💯 Phá gạch ghi điểm:**  
  Gạch nào bị đập là cộng 10 điểm. Càng phá được nhiều thì điểm càng cao, nhìn cũng sướng mắt nữa. Có 3 màu gạch vàng, cam và đỏ với sức mạnh tăng dần

- **🎶 Âm thanh & giao diện:**  
  Có nhạc nền nghe chill khi chơi, kèm theo hiệu ứng âm thanh mỗi lần bóng va chạm. Game over hay hết giờ cũng có nhạc riêng. Giao diện thì đơn giản, dễ nhìn, tập trung vào gameplay.

- **💿 Chế độ chơi rõ ràng:**  
  + **Survival:** Phá hết gạch thì gạch sẽ xuất hiện lại, và bóng sẽ nhanh hơn chút xíu sau mỗi vòng. Càng chơi càng căng.  
  + **Time Attack:** Có 120 giây để phá sạch gạch. Phá hết là thắng, không thì hết giờ là thua.  
  Dù ở chế độ nào thì bạn cũng có 3 mạng. Để bóng rơi 3 lần là... tạch nha 😬

- **⏸️ Tạm dừng và menu:**  
  Bấm `ESC` để tạm dừng game. Trong lúc tạm dừng có thể:  
  + Bấm `M` để quay lại menu  
  + Bấm `ESC` lần nữa để tiếp tục  
  + Có thanh chỉnh âm lượng rất tiện  

- **🔚 Kết thúc trận:**  
  Khi thua (bị mất hết mạng hoặc hết giờ), bạn có 3 lựa chọn:  
  + Bấm `R` để chơi lại  
  + Bấm `Q` để thoát  
  + Bấm `M` để quay lại chọn chế độ khác  

- **🏆 Điểm cao riêng từng chế độ:**  
  Mỗi chế độ đều có bảng điểm cao riêng, nên yên tâm là kỷ lục của bạn không bị mất đâu 😎
---

## ⚙️ Hướng dẫn cài đặt và chạy game
### 📌 Yêu cầu hệ thống
- Hệ điều hành: Windows/Linux
- Cài đặt SDL2 và các thư viện liên quan:
  - SDL2
  - SDL2_image
  - SDL2_mixer
  - SDL2_ttf

### 🚀 Cài đặt
1. **Clone dự án từ GitHub:**
   ```bash
   git clone https://github.com/Minhquan10092006/SDL-Projects.git
   cd SDL-Projects/BrickBreaker
   ```

2. Cài đặt thư viện SDL2:
   - **Windows:** Sử dụng vcpkg hoặc tải từ [SDL Official](https://libsdl.org/).
   - **Linux:** Chạy lệnh:
     ```bash
     sudo apt-get install libsdl2-dev libsdl2-image-dev libsdl2-mixer-dev libsdl2-ttf-dev
     ```

3. Build dự án:
   ```bash
   g++ src/*.cpp -o build/brickbreaker -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf
   ```

4. Chạy trò chơi:
   ```bash
   ./build/brickbreaker
   ```

---

## 📚 Nguồn tham khảo

- **🔁 Logic va chạm:**  
  Một vài đoạn logic tham khảo từ [Lazy Foo' SDL Tutorials](https://lazyfoo.net/tutorials/SDL/)

- **🎨 Tài nguyên đồ họa:**  
  - Paddle, bóng và gạch từ [OpenGameArt - Breakout Brick Breaker Tileset](https://opengameart.org/content/breakout-brick-breaker-tile-set-free)
  - Background từ [Ocean and Clouds Free Pixel Art Backgrounds](https://craftpix.net/freebies/ocean-and-clouds-free-pixel-art-backgrounds/)
  - Font chữ từ [Font Space- Feulisma font](https://www.fontspace.com/feulismia-font-f139028) và [Font space - Meloncamp](https://www.fontspace.com/melon-camp-font-f139888)

- **🔊 Âm thanh:**  
  - Hiệu ứng âm thanh từ [Mixkit Game Sound Effects](https://mixkit.co/free-sound-effects/game/)
  - Hiệu ứng âm thanh game over từ [Super Mario gameover](https://www.youtube.com/shorts/3kvVMn28Ogg?feature=share)
  - Hiệu ứng âm thanh background từ [𝐁𝐮𝐧𝐧𝐲 𝐆𝐢𝐫𝐥 𝐒𝐞𝐧𝐩𝐚𝐢 ~ lofi hiphop and lofi remix](https://youtu.be/g7Luv9ibHWg)
---

## 🎥 Video giới thiệu
Video giới thiệu game và chạy thử: [Demo game Brick Breaker - First big project](https://youtu.be/ik9KapIMlsE)

---

## 🤝 Đóng góp
Nếu bạn có ý tưởng hoặc phát hiện lỗi, vui lòng tạo issue hoặc pull request trên repository này.

---

## 🧠 Mức độ sử dụng AI
AI được sử dụng chủ yếu để tra cứu và học về các hàm của SDL2, vẽ background của GameOver và được sử dụng để hỗ trợ Debug khi không còn cách nào khác.

---

## 🧑🏻‍💻 Tác giả
- **Email**: [minhquan20061009@gmail.com]

---

## 🧪 Game cho ai muốn tải về chơi thử
- **Link tải**: [Game Brick Breaker](https://drive.google.com/file/d/1vRcqJf2kZb3YrDVEnuL_ruGM8mefM6G5/view?usp=sharing)
- **Cách cài đặt**: Khi mọi người tải về xong, giải nén ra và chạy file .exe, thế là xong rồi 👌👌👌

---
## 🎯 Ngưỡng điểm mong muốn 8 - 8.5
- Lý do em muốn được ngưỡng điểm này là vì:
1. **Gameplay hấp dẫn và quen thuộc (8/10)**:  
   Game arcade dễ tiếp cận, các chế độ **Survival** và **Time Attack** tạo thử thách mới mẻ, không nhàm chán.

2. **Đồ họa và âm thanh ổn (8/10)**:  
   Đồ họa đơn giản, dễ nhìn, âm thanh sinh động giúp tăng trải nghiệm, nhạc nền tạo không khí arcade vui nhộn.

3. **Các tính năng và sự sáng tạo (8.5/10)**:  
   Các tính năng như **pause game**, **thanh trượt âm lượng**, **high score** riêng cho mỗi chế độ giúp người chơi dễ quản lý game.

4. **Cải tiến có thể thêm một cách dễ dàng với code chia file logic (8/10)**:  
   Game có thể thêm hiệu ứng hình ảnh đặc biệt, mở rộng chế độ chơi hoặc tăng độ khó để thử thách lâu dài hơn.

5. **Tính đa dạng và sự thử thách (8/10)**:  
   Các chế độ chơi giữ thử thách, nhưng có thể dễ dàng chiến thắng hơn với game thủ lâu dài nếu không có sự thay đổi gameplay.

---

## Giấy phép
Dự án này được phát hành dưới giấy phép [MIT License](LICENSE).
