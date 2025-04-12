# Hiragana Quiz Game

## Description
The **Hiragana Quiz Game** is a terminal-based program designed to help users practice and improve their knowledge of **Japanese Hiragana characters**. It presents a randomized series of questions where the user must match Hiragana characters to their correct English transliterations.

---

## Instructions

1. **Compile** the program using a C compiler (e.g., `gcc main.c -o hiragana_quiz`).
2. **Run** the compiled executable.
3. **Enter** the number of questions you wish to attempt.
4. For each question:
   - A Hiragana character will be displayed.
   - Four English translation options will be shown.
   - Select your answer by entering the number corresponding to your choice.
5. After completing the quiz:
   - Your total score and accuracy will be displayed.
   - Your name and score will be added to the leaderboard.

---

## Features

- **Randomized Questions:** Each quiz session is unique with shuffled options.
- **No Repeats:** Ensures no repetition of characters within a single session.
- **Performance Metrics:** Displays total time taken, average time per question, score, and accuracy.
- **Leaderboard:** Stores and displays top performers based on accuracy.

---

## How to Use

1. **Compile:**
   ```bash
   gcc main.c -o hiragana_quiz
   ```
2. **Run:**
   ```bash
   ./hiragana_quiz
   ```
3. Follow the on-screen prompts to take the quiz and enter your name at the end to record your score.

---

## Files Included

- `main.c` – Source code for the Hiragana Quiz Game.
- `leaderfile.txt` – Stores leaderboard data.
- `README.md` – Documentation and usage guide.

---

## Requirements

- A working C compiler (e.g., GCC).
- Standard C libraries:
  - `stdio.h`
  - `stdlib.h`
  - `time.h`
  - `string.h`
  - `stdbool.h`

---

## About

- **Author:** Raj Khedkar (B23CH1038)  
- **Version:** 1.0  
- **Date:** 18/03/2024

---

## Note

This project is a basic implementation and may contain limitations. Feedback, suggestions, and contributions are welcome to improve functionality and expand its scope.
