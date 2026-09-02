# ComputorV2 — Mathematical Interpreter & Computer Algebra Engine

[![C++20](https://img.shields.io/badge/Language-C%2B%2B20-00599C?logo=c%2B%2B&logoColor=white)](https://en.cppreference.com/w/cpp/20)
[![Build](https://img.shields.io/badge/Build-GNU%20Make-informational?logo=gnu)](Makefile)
[![Compiler Flags](https://img.shields.io/badge/Compiler_Flags---Wall_--Wextra_--Werror-blueviolet)](#)
[![Zero Libmath](https://img.shields.io/badge/Dependencies-Zero_External_Math_Libs-success)](#)
[![Architecture](https://img.shields.io/badge/Design-Recursive_Descent_%7C_AST_%7C_Visitor-orange)](#)

A high-performance interactive Computer Algebra System (CAS) and REPL written in modern **C++20**. It executes symbolic and numerical computations across scalar, complex, matrix, and polynomial domains using a recursive-descent parser, an abstract syntax tree (AST) evaluated via the Visitor pattern, and a custom first-principles numerical mathematics engine with zero external dependencies.

---

## 📌 Academic / Project Context

This project is part of the **42 School Post-Common Core curriculum** (Advanced Mathematics / Software Architecture track). It serves as the comprehensive continuation of *ComputorV1*, expanding from single-equation solving to an extensible, context-aware command-line interpreter.

### Core Engineering Constraints
- **Zero External Mathematical Libraries**: Standard math library headers (`<cmath>`, `<math.h>`) and external CAS engines are forbidden. All elementary, trigonometric, exponential, linear algebraic, and polynomial algorithms are designed and implemented from first principles.
- **Strict Modern C++ Idioms**: Compiled under `-Wall -Wextra -Werror -std=c++20`. Employs C++20 concepts, `std::variant`-based algebraic data types, `std::unique_ptr` polymorphic hierarchies, type-safe double-dispatch visitors, and RAII memory lifecycle management.
- **Multi-Paradigm Domain Algebra**: Simultaneous support for Real numbers (`ℝ`), Complex numbers (`ℂ`), Matrices (`M_{m,n}(ℝ)` / `M_{m,n}(ℂ)`), and Polynomials (`ℝ[X]`) with complete cross-domain operator interop.

---

## 🏗️ Architecture & Modules

The pipeline follows a decoupled compiler architecture: raw user input is lexed with regular expressions, preprocessed to resolve grammar ambiguities, converted into an Abstract Syntax Tree (AST) via recursive-descent parsing, and evaluated dynamically against an in-memory execution context through double-dispatch visitors.

```
                    +------------------------------------------+
                    |                User Input                |
                    |        (CLI via GNU Readline REPL)       |
                    +--------------------+---------------------+
                                         |
                                         v
                    +--------------------+---------------------+
                    |               Lexer                      |
                    | (Regex Tokenization & Op Classification) |
                    +--------------------+---------------------+
                                         |
                                         v
                    +--------------------+---------------------+
                    |         Token Preprocessor               |
                    |  - Contextual Arity Resolution (+ / -)   |
                    |  - Implicit Multiplication Injection     |
                    +--------------------+---------------------+
                                         |
                                         v
                    +--------------------+---------------------+
                    |       Recursive Descent Parser           |
                    |    (Operator Precedence & Grammar)       |
                    +--------------------+---------------------+
                                         |
                                         v
                    +--------------------+---------------------+
                    |        AST Node Representation           |
                    |   (BaseNode -> Binary, Unary, Matrix,    |
                    |     Builtin, Variable, FunctionCall)     |
                    +--------------------+---------------------+
                                         |
                                         v
                    +--------------------+---------------------+
                    |         Interpreter Engine               |
                    |  - Evaluation Context (std::map)         |
                    |  - Double-Dispatch Visitor Pattern       |
                    |  - VarType (std::variant Heterogeneous)  |
                    +--------------------+---------------------+
                                         |
                                         v
                    +--------------------+---------------------+
                    |          Output Formatter                |
                    |  - Continued Fraction Rational Approxim. |
                    |  - Exact Radical & Pi Multiplier Scaling |
                    |  - Unicode Braille (2x4 Subpixel Raster) |
                    +------------------------------------------+
```

### Module Breakdown

| Module | Location | Primary Responsibilities |
| :--- | :--- | :--- |
| **Lexer & Preprocessor** | [`Lexer.cpp`](srcs/Lexer.cpp), [`TokenPreprocessor.cpp`](srcs/Interpreter/TokenPreprocessor.cpp) | Regex-based token extraction; arity disambiguation (unary vs binary `+`/`-`); implicit multiplication insertion (`2x` → `2 * x`). |
| **Parser & AST Nodes** | [`Parser.cpp`](srcs/Parser.cpp), [`srcs/Nodes/`](srcs/Nodes/) | Recursive-descent grammar parsing with standard operator precedence; builds AST using `std::unique_ptr<BaseNode>` hierarchy. |
| **Visitor Evaluator** | [`srcs/Visitors/`](srcs/Visitors/), [`InterpreterEvaluator.cpp`](srcs/Interpreter/InterpreterEvaluator.cpp) | Double-dispatch evaluation via `std::visit` and operator overloads for cross-type operations. |
| **Numerical Kernel** | [`srcs/Maths/`](srcs/Maths/) | Custom transcendental engine: Taylor series (`sin`, `cos`, `tan`, `exp`), Newton-Raphson square roots, modular range reduction. |
| **Linear Algebra** | [`Matrix.hpp`](includes/Types/Matrix.hpp), [`Matrix.tpp`](includes/Types/Matrix.tpp) | Templated matrix algebra constrained with C++20 concepts; Gauss-Jordan elimination with partial pivoting; matrix powers (O(log k)). |
| **Polynomial Engine** | [`srcs/Types/Polynomial/`](srcs/Types/Polynomial/) | Polynomial algebra, Horner evaluation, Euclidean division (quotient & remainder), and analytic root solver (≤ 2nd degree). |
| **Exact Output & Formatting** | [`Real.cpp`](srcs/Types/Real.cpp), [`Fraction.cpp`](srcs/Fraction.cpp) | Continued fraction approximation (convergents $h_n/k_n$); exact radical/π representation detection. |
| **Subpixel Terminal Plotter** | [`Plotter.cpp`](srcs/Plotter.cpp) | High-resolution terminal canvas rendering equations onto UTF-8 Braille matrix blocks (2 × 4 subpixels per glyph). |

---

## 🧠 Engineering Highlights & Technical Learnings

### 1. Heterogeneous Type System & Multi-Dispatch via `std::variant`
Instead of runtime pointer downcasting (`dynamic_cast`) or unsafe type tagging, the interpreter models runtime data types as a closed algebraic sum type:
```cpp
using VarType = std::variant<Real, Complex, Polynomial, Matrix<Real>, Matrix<Complex>>;
```
Binary and unary operations are evaluated via `std::visit` with specialized visitor structs (`BinaryOpVisitor`, `UnaryOpVisitor`). Overloaded call operators define valid algebraic cross-interactions (e.g., `Matrix<Real> * Real`, `Polynomial + Real`, `Complex / Real`, `Matrix<K> ** Matrix<K>`) at compile time, rejecting illegal combinations with explicit runtime diagnostics while retaining zero heap allocation overhead for scalar evaluation.

### 2. Zero-`<cmath>` Numerical Kernel & Series Expansions
Because external math functions were strictly prohibited, all mathematical primitives were engineered from first principles:
- **Newton-Raphson Root Finding**: Square root extraction for real numbers and complex polar decomposition using iterative quadratic convergence:
  $$x_{n+1} = \frac{1}{2}\left(x_n + \frac{S}{x_n}\right)$$
- **Taylor/Maclaurin Series & Range Reduction**: Trigonometric and exponential evaluations use Taylor polynomial expansions. Argument reduction modulo $2\pi$ keeps terms bounded within convergence intervals:
  $$\sin(x) = \sum_{k=0}^{N} \frac{(-1)^k x^{2k+1}}{(2k+1)!}, \quad \exp(z) = \sum_{k=0}^{N} \frac{z^k}{k!}$$
- **Complex Analytical Continuation**: Euler's formulas compute complex trigonometric functions without divergence:
  $$\cos(z) = \frac{e^{iz} + e^{-iz}}{2}, \quad \sin(z) = \frac{e^{iz} - e^{-iz}}{2i}$$

### 3. Linear Algebra & Gauss-Jordan Matrix Inversion
Matrix computations are parameterized using modern C++20 concepts:
```cpp
template<typename K>
concept real_complex = std::same_as<K, Real> || std::same_as<K, Complex>;

template<real_complex K>
class Matrix { ... };
```
Matrix inversion is solved in O(N³) via **Gauss-Jordan elimination with partial column pivoting** (`findIndexMaxAbsColumn`), guaranteeing numerical stability when handling small pivot values. Fast binary exponentiation computes matrix powers $M^k$ in O(log k) matrix multiplications.

### 4. Continued Fraction Rational Approximation & Exact Formatting
Floating-point outputs are evaluated through a continued fraction expansion algorithm generating best rational convergents:
$$x = a_0 + \frac{1}{a_1 + \frac{1}{a_2 + \dots}}, \quad h_n = a_n h_{n-1} + h_{n-2}, \quad k_n = a_n k_{n-1} + k_{n-2}$$
This allows the engine to automatically simplify decimal results (such as `0.333333` → `1/3`, `3.5 + 2.5i` → `7/2 + 5/2i`, and detect integral multiples of π or integer square roots like `sqrt(30)`).

### 5. High-Density Subpixel Graphics via Unicode Braille Encoding
The built-in `plot` command renders arbitrary polynomial curves directly in standard CLI terminals by mapping a continuous 2D coordinate grid to Unicode Braille patterns (`U+2800` through `U+28FF`). Each printed character contains a 2 × 4 binary dot matrix (8 subpixels per character block), yielding 4× higher vertical resolution and 2× higher horizontal resolution compared to standard ASCII character plotting.

---

## 🚀 Quick Start

### Prerequisites
- C++20 compatible compiler (`clang++` >= 12 or `g++` >= 10)
- GNU Make
- `libreadline` development headers

### Build & Run
```bash
# Clone the repository
git clone https://github.com/r-richardcanavaggio/computorv2.git
cd computorv2

# Compile the binary
make -j

# Launch the interactive REPL
./computorv2
```

### Cleanup
```bash
# Remove object files
make clean

# Remove object files and binary
make fclean

# Rebuild from scratch
make re
```

---

## 💻 Showcase

### 1. Polynomial Calculus, Euclidean Division & Complex Root Resolution
```text
> f(x) = 2x^2 - 4x + 10
2x^2 - 4x + 10
> f(x) = 0?
Polynomial degree: 2
Discriminant is -64
Strictly negative, the two solutions are:
1 - 2i
1 + 2i
> g(x) = x^3 - 2x^2 + x - 5
x^3 - 2x^2 + x - 5
> h(x) = x - 1
x - 1
> g(x) / h(x)
x^2 - x
> g(x) % h(x)
-5
```

### 2. Linear Algebra, Matrix Inversion & Transcendental Functions
```text
> m = [[1, 2]; [3, 4]]
[1, 2]
[3, 4]

> inv(m)
[-2, 1]
[3/2, -1/2]

> m ** inv(m)
[1, 0]
[0, 1]

> norm(m)
sqrt(30)
> exp(i * pi)
-1
> cos(pi / 3)
1/2
```

### 3. High-Resolution Terminal Plotting (Braille Subpixel Engine)
```text
> f(x) = 0.1 * x^2 - 5
1/10x^2 - 5
> plot f
 ⠹⡄                 ⡇                ⢠⠎ 
  ⠙⣄                ⡇               ⢠⠏  
   ⠘⢦               ⡇              ⡰⠃   
    ⠈⢳⡀             ⡇            ⢀⡜⠁    
      ⠙⣄            ⡇           ⣠⠎      
       ⠈⠳⣄          ⡇         ⢀⠜⠁       
         ⠈⠲⣄        ⡇       ⣀⠔⠁         
⠒⠒⠒⠒⠒⠒⠒⠒⠒⠒⠒⠚⠓⢶⣒⠒⠒⠒⠒⠒⡗⠒⠒⠒⠒⢒⡶⠞⠓⠒⠒⠒⠒⠒⠒⠒⠒⠒⠒⠒
              ⠈⠙⠲⠤⠤⠤⡧⠤⠤⠖⠊⠁              
                    ⡇                   
                    ⡇                   
                    ⡇                   
                    ⡇                   
                    ⡇                   
                    ⡇                   
```
