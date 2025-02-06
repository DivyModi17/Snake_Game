# Snake Game in C++

This is a simple Snake game implemented in C++. The game is played in a terminal window and features a snake that grows in length as it eats fruits. The game ends if the snake collides with the walls, its own tail, or an obstacle. The game keeps track of the player's score and the highest score achieved.

---

## Table of Contents
1. [Features](#features)
2. [How to Play](#how-to-play)
3. [Installation](#installation)
4. [Code Explanation](#code-explanation)
   - [Setup Function](#setup-function)
   - [Draw Function](#draw-function)
   - [Input Function](#input-function)
   - [Logic Function](#logic-function)
   - [Main Function](#main-function)
5. [Usage](#usage)
6. [Contributing](#contributing)
7. [License](#license)

---

## Features
- **Snake Movement**: The snake can move in four directions (Up, Down, Left, Right).
- **Fruit Consumption**: The snake grows in length when it eats a fruit.
- **Obstacles**: The game includes obstacles that end the game if the snake collides with them.
- **Score Tracking**: The game keeps track of the current score and the highest score achieved.
- **Game Over**: The game ends if the snake collides with the walls, its own tail, or an obstacle.

---

## How to Play
- Use the following keys to control the snake:
  - **W**: Move Up
  - **A**: Move Left
  - **S**: Move Down
  - **D**: Move Right
  - **X**: Quit the game
- The game ends if the snake collides with the walls, its own tail, or an obstacle.
- The goal is to eat as many fruits as possible to increase your score.

---

## Installation
1. Clone the repository:
   ```bash
   git clone https://github.com/your-username/snake-game-cpp.git
   ```
2. Navigate to the project directory:
   ```bash
   cd snake-game-cpp
   ```
3. Compile the code using a C++ compiler (e.g., g++):
   ```bash
   g++ -o snake_game main.cpp
   ```

---

## Code Explanation

### Setup Function
The `Setup()` function initializes the game variables and sets up the initial state of the game. It sets the snake's starting position, places the fruit and obstacle randomly, and initializes the tail length and score.

```cpp
void Setup() {
    GameOver = false;
    dir = 'L';
    x = width / 2;
    y = height / 2;
    fruitX = rand() % (width - 2) + 1;
    fruitY = rand() % (height - 2) + 1;
    obstacleX = rand() % (width - 2) + 1;
    obstacleY = rand() % (height - 2) + 1;
    score = 0;

    nTail = 2;
    tailX[0] = x + 1;
    tailY[0] = y;
    tailX[1] = x + 2;
    tailY[1] = y;
}
```

---

### Draw Function
The `Draw()` function renders the game board, snake, fruits, and obstacles. It clears the screen, draws the borders, and updates the positions of the snake, fruit, and obstacle.

```cpp
void Draw() {
    system("cls");

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (i == 0 || i == height - 1 || j == 0 || j == width - 1) {
                cout << "#";
            }
            else if (i == y && j == x) {
                cout << "O";
            }
            else if (i == fruitY && j == fruitX) {
                cout << "F";
            }
            else if (i == obstacleY && j == obstacleX) {
                cout << "X";
            }
            else {
                bool print = false;
                for (int k = 0; k < nTail; k++) {
                    if (tailX[k] == j && tailY[k] == i) {
                        cout << "o";
                        print = true;
                    }
                }
                if (!print) {
                    cout << " ";
                }
            }
        }
        cout << endl;
    }

    cout << "Score: " << score << endl;
    cout << "Highest Score: " << highestScore << endl;
}
```

---

### Input Function
The `Input()` function handles user input to control the snake's movement. It uses `_kbhit()` and `_getch()` to detect key presses and updates the direction of the snake accordingly.

```cpp
void Input() {
    if (_kbhit()) {
        switch (_getch()) {
        case 'a':
            if (dir != 'R') dir = 'L';
            break;
        case 'd':
            if (dir != 'L') dir = 'R';
            break;
        case 'w':
            if (dir != 'D') dir = 'U';
            break;
        case 's':
            if (dir != 'U') dir = 'D';
            break;
        case 'x':
            GameOver = true;
            break;
        }
    }
}
```

---

### Logic Function
The `Logic()` function implements the game logic, including snake movement, collision detection, and score updating. It updates the snake's position, checks for collisions, and handles fruit consumption.

```cpp
void Logic() {
    int prevX = tailX[0];
    int prevY = tailY[0];
    int prev2X, prev2Y;
    tailX[0] = x;
    tailY[0] = y;

    for (int i = 1; i < nTail; i++) {
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }

    switch (dir) {
    case 'L':
        x--;
        break;
    case 'R':
        x++;
        break;
    case 'U':
        y--;
        break;
    case 'D':
        y++;
        break;
    }

    if (x > width - 1 || x < 0 || y > height - 1 || y < 0) {
        GameOver = true;
    }

    for (int i = 0; i < nTail; i++) {
        if (tailX[i] == x && tailY[i] == y) {
            GameOver = true;
        }
    }

    if (x == obstacleX && y == obstacleY) {
        GameOver = true;
    }

    if (x == fruitX && y == fruitY) {
        score += 10;
        fruitX = rand() % (width - 2) + 1;
        fruitY = rand() % (height - 2) + 1;
        obstacleX = rand() % (width - 2) + 1;
        obstacleY = rand() % (height - 2) + 1;
        nTail++;
    }
}
```

---

### Main Function
The `main()` function runs the game loop and handles game over logic. It initializes the game, updates the game state, and allows the player to play again.

```cpp
int main() {
    srand(static_cast<unsigned int>(time(0)));
    char playAgain;

    do {
        Setup();
        while (!GameOver) {
            Draw();
            Input();
            Logic();
            Sleep(70);
        }

        if (score > highestScore) {
            highestScore = score;
        }

        cout << "Game Over!" << endl;
        cout << "Your Score: " << score << endl;
        cout << "Highest Score: " << highestScore << endl;
        cout << "Do you want to play again? (y/n)";
        playAgain = '+';
        while (playAgain != 'Y' && playAgain != 'y' && playAgain != 'n' && playAgain != 'N') {
            playAgain = _getch();
            if (playAgain == 'n' || playAgain == 'N') {
                return 0;
            }
        }

    } while (playAgain == 'y' || playAgain == 'Y');

    return 0;
}
```

---

## Usage
1. Run the compiled executable:
   ```bash
   ./snake_game
   ```
2. Follow the on-screen instructions to play the game.

---

## Contributing
Contributions are welcome! If you have any suggestions, bug reports, or feature requests, please open an issue or submit a pull request.

1. Fork the repository.
2. Create a new branch (`git checkout -b feature/YourFeatureName`).
3. Commit your changes (`git commit -m 'Add some feature'`).
4. Push to the branch (`git push origin feature/YourFeatureName`).
5. Open a pull request.
