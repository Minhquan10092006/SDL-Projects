#include "Game.h"
#include <iostream>

int main(int argc, char* argv[]) {
    Game game;

    // Khởi tạo trò chơi
    if (!game.init()) {
        std::cerr << "Failed to initialize the game.\n";
        return -1;
    }

    while (game.isRunningGame()) { // Kiểm tra trạng thái chạy của game
        if (game.runMenu()) { // Hiển thị menu và kiểm tra lựa chọn
            game.run(); // Bắt đầu trò chơi
        }
    }

    // Kết thúc trò chơi
    game.close();
    return 0;
}