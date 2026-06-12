# Console-Based Interactive Math Quiz Game

An interactive, console-based Math Quiz Game developed in C++ using structured programming practices. This application showcases core object-oriented and structural design concepts, utilizing structures, enumerations, memory-efficient operations, and input validation logic to deliver a dynamic user experience.

---

## Technical Features

### 1. Advanced Game Customization and Control Flow
* **Dynamic Settings Selection:** Allows users to choose the number of quiz questions, difficulty levels (Easy, Medium, Hard, or Mixed), and specific arithmetic operation types (Addition, Subtraction, Multiplication, Division, or Mixed).
* **Robust Input Validation:** Implements strict validation loops on user selections (`ReadQuestionsLevel`, `ReadOpType`, and `ReadHowManyQuestions`) to ensure execution stability and prevent out-of-bounds inputs.

### 2. High-Performance Code Architecture
* **Structured Data Components:** Employs nested `struct` definitions (`stQuestion` and `stQuizz`) to cleanly separate question states, answers, and cumulative score metrics.
* **Efficient Memory Allocation:** Functions processing extensive quiz data utilize constant reference parameters (`const stQuizz&`) to optimize performance and prevent unnecessary memory duplication during structural passes.

### 3. Logic Optimization and Safeguards
* **Division by Zero Protection:** Implements critical computational safeguards within the generation logic to prevent run-time application crashes during random number division.
* **Fraction-Free Division Logic:** Automatically adapts generated variables dynamically when division is selected, enforcing exact integer returns to preserve operational integrity for the end user.
* **Environment Synchronization:** Handles color alerts seamlessly across OS terminal modes via dynamic system UI adjustments corresponding directly to factual answer validation states.

---

## Core Technologies and Concepts Demonstrated
* **Control Structures:** Loops (`do-while`, `for`) and selection matrices (`switch-case`).
* **Enumerations (Enums):** Explicit mapping of type states (`enQuestionsLevel` and `enOperationType`).
* **Randomization:** Algorithmic pseudo-random generation tied to system execution time (`srand`, `rand`).
* **Modularity:** Isolation of business logic from console UI rendering and input scanning routines.

---

## How to Run the Application
1. Clone
