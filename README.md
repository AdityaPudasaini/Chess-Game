# ♟️ C++ Chess Game

A graphical chess game built in C++ using the SFML library. This project implements standard chess rules with a clean object-oriented design and a fully interactive GUI.

---

## 📷 Screenshots

> **Add your screenshots here!** Take a screenshot of your game running and upload them to a `screenshots/` folder in your repo, then replace the placeholder links below.

### Game Board
<img width="799" height="792" alt="image" src="https://github.com/user-attachments/assets/fc94f750-b8fe-461e-89ef-d0c3e79ac7da" />


### Valid Move showcase
<img width="795" height="800" alt="image" src="https://github.com/user-attachments/assets/3d465a37-14e9-4e2e-a5a3-7f958fd4cd34" />


### Checkmate
<img width="800" height="793" alt="image" src="https://github.com/user-attachments/assets/45feb379-a58d-442c-9e02-e964d6cd5693" />


### Pawn Promotion
<img width="798" height="798" alt="image" src="https://github.com/user-attachments/assets/73e070fc-7296-4af5-8912-bd4da17f4dc6" />


---

## 🚀 Features

- 🎨 Fully graphical board rendered with SFML
- 🔁 Turn-based two-player gameplay (Player vs Player)
- ✅ Valid move highlighting for selected pieces
- ♟️ All standard piece movements (King, Queen, Rook, Bishop, Knight, Pawn)
- ⚔️ Capture mechanics
- 👑 Check and checkmate detection
- ♙ Pawn promotion with piece selection UI
- 🚫 Prevents moves that leave your own king in check

---

## 🛠️ Technologies Used

- C++ (C++20)
- [SFML 3.1.0](https://www.sfml-dev.org/) — Graphics, Window, System modules
- MinGW / GCC

---

## 📂 Project Structure

```
Chess-Game/
├── main.cpp        # Entry point, window and event loop
├── Game.cpp        # Core game logic, move validation, check/checkmate
├── Game.hpp
├── board.cpp       # Board rendering
├── board.hpp
├── piece.cpp       # Piece struct, texture loading, drawing
├── piece.hpp
├── assets/         # Piece PNG images and 
└── .vscode/        # Build configuration
```

---

## ⚙️ How to Build and Run

### Prerequisites

- [SFML 3.1.0](https://www.sfml-dev.org/download.php) installed
- GCC / MinGW with C++20 support

### Compile

```bash
g++ -std=c++20 main.cpp board.cpp piece.cpp Game.cpp \
    -IC:/SFML-3.1.0/include \
    -LC:/SFML-3.1.0/lib \
    -lsfml-graphics -lsfml-window -lsfml-system -lopengl32 \
    -o chess
```

### Run

```bash
./chess
```

> Make sure the SFML `.dll` files and the `assets/` folder are in the same directory as the executable.

---

## 🎮 How to Play

1. **Select a piece** — Click on one of your pieces. Valid moves will be highlighted in green.
2. **Move** — Click a highlighted square to move there.
3. **Captures** — Move onto an opponent's piece to capture it.
4. **Pawn Promotion** — When a pawn reaches the last rank, a promotion menu appears. Click your desired piece.
5. **Checkmate** — The game ends when a player has no legal moves left.

---

## 📌 Known Limitations

- No castling or en passant yet
- No AI — two human players only
- No game timer

---

## 👤 Author

**Aditya Pudasaini**
[GitHub](https://github.com/AdityaPudasaini)