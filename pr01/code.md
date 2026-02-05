# Lexical Analyzer in C

## **Overview**

A **Lexical Analyzer (Lexer)** is the **first phase of a compiler**. Its main responsibilities are:

1. Read the source code **character by character**.
2. Group characters into **tokens**:

   * Keywords (`if`, `int`, `return`)
   * Identifiers (`x`, `count`, `myVar`)
   * Numbers (`123`, `456`)
   * Operators (`+`, `-`, `*`, `/`, `=`)
   * Separators (`;`, `()`, `{}`, `,`)
3. Ignore **whitespace**, **tabs**, and **newlines**.
4. Report **errors** for invalid tokens.

Think of it like **scanning a sentence in English**:

```
“The cat sat on the mat.”
```

The lexer separates it into words (tokens): `"The"`, `"cat"`, `"sat"`, `"on"`, `"the"`, `"mat"`.

Similarly, in C, the input:

```c
int x = 10;
```

becomes:

```
int, x, =, 10, ;
```

---

## **How the Code Works**

### **Step 1: Input the code**

```c
char code[MAX];
fgets(code, MAX, stdin);
```

* Reads a line of code including spaces and newlines.
* Example: `int x = 10;`

---

### **Step 2: Loop through each character**

```c
while (code[i] != '\0') { ... }
```

* Loops through each character until the **end of string (`\0`)**.
* `i` keeps track of the **current position**.

---

### **Step 3: Skip redundant spaces, tabs, and newlines**

```c
if (code[i] == ' ' || code[i] == '\t' || code[i] == '\n') {
    i++;
    continue;
}
```

* These characters are **ignored** because they do not affect the meaning of the program.

---

### **Step 4: Detect operators**

```c
if (isOperator(code[i])) {
    printf("Operator: %c\n", code[i]);
    i++;
}
```

* Checks if the character is one of `+ - * / =`.
* Prints it as an **Operator token**.

---

### **Step 5: Detect separators**

```c
else if (isSeparator(code[i])) {
    printf("Separator: %c\n", code[i]);
    i++;
}
```

* Checks for characters like `(){};,`.
* Prints it as a **Separator token**.

---

### **Step 6: Detect keywords or identifiers**

```c
else if (isalpha(code[i])) {
    while (isalnum(code[i])) { buffer[j++] = code[i++]; }
    buffer[j] = '\0';
    if (isKeyword(buffer)) printf("Keyword: %s\n", buffer);
    else printf("Identifier: %s\n", buffer);
}
```

* If a character is **alphabetic**, it could be a keyword or identifier.
* Collects letters and digits into `buffer`.
* Checks if `buffer` matches a keyword list.

**Theory:**

* Keywords: reserved words with **special meaning** (`int`, `if`, `return`).
* Identifiers: names for **variables, functions**, etc.

---

### **Step 7: Detect numbers**

```c
else if (isdigit(code[i])) {
    while (isdigit(code[i])) { buffer[j++] = code[i++]; }
    buffer[j] = '\0';
    printf("Number: %s\n", buffer);
}
```

* If the character is a **digit**, collect all consecutive digits.
* Prints as a **Number token**.

**Theory:** Numbers are constants used in computations.

---

### **Step 8: Handle unknown tokens**

```c
else {
    printf("Unknown token: %c\n", code[i]);
    i++;
}
```

* Any character not matching previous categories is flagged as **unknown**.
* Useful for **error detection**.

---

### **Step 9: Repeat until end**

* Loop continues until all characters are processed.
* At the end, you have a **list of tokens** ready for the parser.

---

## **How Lexer Ignores Spaces, Tabs, and Newlines**

* The lexer **skips these characters** using:

```c
if (code[i] == ' ' || code[i] == '\t' || code[i] == '\n') { ... }
```

* This process is called **lexical cleansing**.

---

## **Lexical Analyzer Flowchart (Theory)**

1. **Start**
2. **Read next character**
3. **Is it whitespace/tab/newline?** → Ignore
4. **Is it an operator?** → Token: Operator
5. **Is it a separator?** → Token: Separator
6. **Is it alphabetic?** → Collect word → Keyword or Identifier
7. **Is it a digit?** → Collect number → Token: Number
8. **Else** → Unknown token → Error
9. **Repeat** until end of input
10. **Stop**

---

## **Key Points**

* A **lexer** does **not check grammar** — the parser does that.
* It identifies **meaningful units (tokens)**.
* Keywords, identifiers, numbers, operators, and separators are the **basic token categories**.

## Sample Input
```c
int x=10; x=x+1; return x;
```
## Sample output
```txt
Keyword: int
Identifier: x
Operator: =
Number: 10
Separator: ;
Identifier: x
Operator: =
Identifier: x
Operator: +
Number: 1
Separator: ;
Keyword: return
Identifier: x
Separator: ;
```
