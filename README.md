# ♟️ C++ Chess Game (Remake)

A remake of the classic chess game built using C++. This project focuses on implementing core chess mechanics while applying object-oriented programming principles and clean code structure.

---

## 📌 Overview
This project recreates the traditional two-player chess experience in a console-based environment. It handles piece movement, turn-based gameplay, and essential game rules, making it a solid demonstration of logic building and structured programming in C++.

---

## 🚀 Features
- ♟️ Full chessboard representation  
- 🔁 Turn-based gameplay (Player vs Player)  
- ✅ Valid move checking for all pieces  
- ⚔️ Capture mechanics  
- 👑 Check and checkmate detection (if implemented)  
- 🧠 Object-oriented design (classes for pieces, board, game logic)  
- 🖥️ Console-based interface (simple and lightweight)  

---

## 🎮 Controls

Example input format:

- First coordinate → piece to move  
- Second coordinate → destination  

### Notes:
- Coordinates follow standard chess notation (a–h, 1–8)  
- Invalid moves will be rejected  
- Players take turns entering moves  

---

## 🛠️ Technologies Used
- C++  
- Standard Library (STL)  
- Object-Oriented Programming (OOP)  

---

## 📷 Screenshots

*(Add your screenshots here after uploading them to GitHub)*

### Game Board
![Game Board](screenshots/board.png)

### Example Move
![Move Example](screenshots/move.png)

> Tip: Create a `screenshots` folder in your repo and place images there.

---

## 📂 Project Structure├── main.cpp
├── Game.cpp / Game.h
├── Board.cpp / Board.h
├── Piece.cpp / Piece.h
├── Player.cpp / Player.h
└── screenshots/


---

## ⚙️ How to Run

### 1. Clone the repository

bash
  git clone https://github.com/your-username/chess-game-cpp.git
  cd chess-game-cpp
  
### 2. Compile the code
g++ *.cpp -o chess

### 3. Run the game
./chess
