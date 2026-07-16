# C Lexical Analyzer

A comprehensive lexical analyzer implementation in C that tokenizes C source code into meaningful tokens, identifying keywords, identifiers, operators, delimiters, literals, and preprocessor directives. This project demonstrates the first phase of compiler design.

## 📋 Project Description

The **Lexical Analyzer** is a C-based tool that breaks down C source code into its fundamental components (tokens). It scans the input character by character, recognizes patterns, and classifies them into appropriate token categories. The analyzer also performs error detection for common lexical errors like unterminated strings, invalid characters, and malformed tokens.

### Author
- **Name:** Jupalli Karthik  
- **Date:** 16-07-2026

## ✨ Features

- **Token Recognition:** Identifies and classifies multiple token types
  - Keywords (if, else, while, for, int, float, void, etc.)
  - Identifiers (variable and function names)
  - Operators (+, -, *, /, %, ==, !=, etc.)
  - Delimiters ({, }, (, ), [, ], ;, :, ,, ., etc.)
  - String literals ("...")
  - Character literals ('...')
  - Integer and floating-point literals
  - Preprocessor directives (#include, #define, etc.)

- **Error Detection:** Identifies and reports lexical errors
  - Unterminated strings
  - Unterminated character literals
  - Unterminated comments
  - Unknown/invalid symbols
  - Invalid tokens

- **Detailed Reporting:**
  - Line number tracking for each token
  - Position tracking within lines
  - Comprehensive token summary statistics
  - Error reports with exact locations

- **Color-Coded Console Output:** User-friendly colored terminal messages for easy monitoring

## 📁 Project Structure

```
LexicalAnalyzerProject/
├── main.c              # Entry point of the lexical analyzer
├── lexer.c             # Core lexical analysis logic
├── lexer.h             # Lexer function declarations
├── tokens.c            # Token printing/formatting functions
├── tokens.h            # Token function declarations
├── checks.c            # Token type checking functions
├── checks.h            # Check function declarations
├── colors.h            # ANSI color codes for terminal output
├── input.c             # Sample C source code to analyze
├── output.txt          # Generated token report (created at runtime)
└── README.md           # This file
```

## 🛠️ Compilation

### Requirements
- GCC compiler (or any C compiler that supports standard C)
- Linux/Unix/Windows environment with a C development toolchain

### Build Instructions

**Option 1: Using GCC directly**
```bash
gcc -o lexer main.c lexer.c tokens.c checks.c input.c
```

**Option 2: Using a Makefile** (if available)
```bash
make
```

### Compilation Output
- Executable file: `lexer` (or `lexer.exe` on Windows)

## 🚀 Usage

### Running the Analyzer

**On Linux/Unix/macOS:**
```bash
./lexer
```

**On Windows:**
```bash
lexer.exe
```

### Workflow

1. **Prepare Input File:** Create a C source file named `input.c` in the same directory as the lexer executable
2. **Run the Analyzer:** Execute the lexer program
3. **View Results:** The program generates `output.txt` with the complete token report

### Example Input

Create an `input.c` file with sample C code:
```c
#include <stdio.h>

int main() {
    int x = 10;
    float y = 3.14;
    if (x > 5) {
        printf("x is greater than 5\n");
    }
    return 0;
}
```

## 📊 Output Format

The `output.txt` file contains:

1. **Header:** Analyzer information and timestamp
2. **Token Table:** Each token with:
   - Lexeme (actual text)
   - Token Type (keyword, identifier, operator, etc.)
   - Line Number
   - Position in Line
3. **Error Report:** Any lexical errors found with details
4. **Summary Statistics:**
   - Total tokens count
   - Token distribution by type
   - Total errors count
   - Error breakdown

### Example Output
```
=========================================================
        LEXICAL ANALYSIS TOKEN REPORT
=========================================================

LEXEME          TOKEN TYPE          LINE    POSITION
#include        PREPROCESSOR        1       1
<stdio.h>       HEADER_FILE         1       10
int             KEYWORD             3       1
main            IDENTIFIER          3       5
(               DELIMITER           3       9
)               DELIMITER           3       10
{               DELIMITER           3       12
int             KEYWORD             4       5
x               IDENTIFIER          4       9
=               OPERATOR            4       11
10              INTEGER_LITERAL     4       13
;               DELIMITER           4       15
...
```

## 📝 Token Types

### Keywords
Recognized C keywords: `auto`, `break`, `case`, `char`, `const`, `continue`, `default`, `do`, `double`, `else`, `enum`, `extern`, `float`, `for`, `goto`, `if`, `inline`, `int`, `long`, `register`, `restrict`, `return`, `short`, `signed`, `sizeof`, `static`, `struct`, `switch`, `typedef`, `union`, `unsigned`, `void`, `volatile`, `while`, `_Alignas`, `_Alignof`, `_Atomic`, `_Bool`, `_Complex`, `_Generic`, `_Imaginary`, `_Noreturn`, `_Static_assert`, `_Thread_local`

### Operators
Single and multi-character operators: `+`, `-`, `*`, `/`, `%`, `++`, `--`, `==`, `!=`, `<`, `>`, `<=`, `>=`, `&&`, `||`, `!`, `&`, `|`, `^`, `~`, `<<`, `>>`, `=`, `+=`, `-=`, `*=`, `/=`, `%=`, `&=`, `|=`, `^=`, `<<=`, `>>=`, `->`

### Delimiters
`{`, `}`, `(`, `)`, `[`, `]`, `;`, `:`, `,`, `.`, `?`, `...`

## ⚠️ Error Handling

The analyzer detects and reports the following lexical errors:

| Error Type | Description |
|-----------|-------------|
| Unterminated String | String literal not closed with `"` |
| Unterminated Character | Character literal not closed with `'` |
| Unterminated Comment | Block comment `/* */` not properly closed |
| Unknown Symbol | Unrecognized character or symbol |
| Invalid Token | Malformed token that doesn't fit any category |

Each error includes line number and position for easy debugging.

## 🔧 Technical Details

### Algorithm Overview
1. **Initialization:** Open input and output files
2. **Character-by-Character Scanning:** Read the input file character by character
3. **Pattern Recognition:** Group characters into meaningful units (tokens)
4. **Classification:** Determine token type based on recognized patterns
5. **Error Detection:** Identify and log any lexical errors
6. **Reporting:** Write tokens and errors to output file with metadata
7. **Cleanup:** Close files and display completion message

### Key Functions

- **`lexicalAnalyzer()`** - Main analysis function
- **`isKeyword()`** - Checks if word is a C keyword
- **`isIdentifier()`** - Validates identifier naming rules
- **`isOperator()`** - Checks for operators
- **`isDelimiter()`** - Checks for delimiters
- **`isInteger()`** - Validates integer literals
- **`isFloat()`** - Validates floating-point literals
- **`isString()`** - Checks for string literals
- **`isCharacter()`** - Checks for character literals
- **`printToken()`** - Formats and outputs token information

## 📈 Sample Output to Console

```
=========================================================
               C LEXICAL ANALYZER
=========================================================

[INFO] Lexical Analysis Process Started...
[INFO] Source file opened successfully.
[INFO] Output file created successfully.
[INFO] Performing Lexical Analysis...

[INFO] Lexical Analysis Completed Successfully.
[INFO] Token information stored in output.txt
=========================================================
                 THANK YOU
=========================================================
```

## 🐛 Troubleshooting

| Issue | Solution |
|-------|----------|
| "Unable to open source file (input.c)" | Ensure `input.c` exists in the same directory as the executable |
| "Unable to create output file (output.txt)" | Check directory permissions and disk space |
| Unexpected token classifications | Review the token type checking functions in `checks.c` |
| Missing tokens in output | Verify the input file contains valid C code |

## 📚 Learning Outcomes

This project demonstrates:
- **Compiler Design:** Understanding the lexical analysis phase
- **String Processing:** Pattern matching and token recognition
- **File I/O:** Reading and writing files in C
- **Data Structures:** Using arrays and structures for token storage
- **Error Handling:** Detecting and reporting lexical errors
- **C Programming:** Comprehensive use of C language features

## 🎓 Educational Use

This analyzer serves as an excellent educational tool for:
- Computer Science students learning compiler design
- Understanding how compilers process source code
- Learning lexical analysis techniques
- Implementing state machines for token recognition

## 📝 License

This project is provided as-is for educational purposes.

## 🔗 Related Topics

- Compiler Design and Theory
- Lexical Analysis (Scanner)
- Token Recognition
- Syntax Analysis (Parser) - Next Phase
- Semantic Analysis - Further Phase

---

**For questions or improvements, feel free to modify and enhance this analyzer!**
