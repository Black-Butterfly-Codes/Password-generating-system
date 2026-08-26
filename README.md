# 🔐 Password Generating System

<p align="center">

<img src="https://img.shields.io/badge/Language-C-8A2BE2?style=for-the-badge&logo=c&logoColor=white" alt="C">
<img src="https://img.shields.io/badge/Cybersecurity-Project-00E5FF?style=for-the-badge&logo=hackthebox&logoColor=white" alt="Cybersecurity">
<img src="https://img.shields.io/badge/Platform-Windows-7B2CBF?style=for-the-badge&logo=windows&logoColor=white" alt="Windows">
<img src="https://img.shields.io/badge/Status-In%20Development-D946EF?style=for-the-badge" alt="Status">

</p>

<p align="center">
  <b>⚡ A neon-inspired, menu-driven password generator and local password-management project written entirely in C. ⚡</b>
</p>

<p align="center">
  <a href="https://github.com/Black-Butterfly-Codes">👤 Developer</a>
  •
  <a href="https://github.com/Black-Butterfly-Codes/Password-generating-system">📂 Repository</a>
</p>

<p align="center">
  <img src="https://capsule-render.vercel.app/api?type=waving&color=8A2BE2,00E5FF&height=120&section=header&text=Secure%20Your%20Digital%20World&fontColor=FFFFFF&fontSize=28&animation=fadeIn" alt="Neon header">
</p>

---

## 🧭 About The Project

**Password Generating System** is a cybersecurity-focused command-line application written in **C**.

The project started as a simple random password generator and evolved into a menu-driven password management system that can create, store, search, modify, and delete saved password entries.

Designed with a purple-neon and cyan-inspired visual identity, this project combines practical C programming with introductory cybersecurity concepts.

The project is designed to strengthen practical understanding of:

* 🧠 C programming
* 🔐 Password security concepts
* 🎲 Random password generation
* 📁 File handling
* 🔎 Searching and validation
* 🧮 Password strength analysis
* 🧹 Data management
* 🛡️ Cybersecurity fundamentals

---

# ✨ Features

## 🔑 Password Generation

Generate customizable passwords using:

* 🔢 Numbers
* 🔤 Lowercase letters
* 🔠 Uppercase letters
* 🔣 Special characters

The user can specify the desired password length.

---

## 💾 Password Storage

Password records can be stored locally in a text file.

The project uses local file handling in C to demonstrate persistent data storage.

---

## 👤 Account Management

The system provides a menu-driven interface for managing saved accounts.

### Available Options

1. 🔐 Create New Password
2. 📋 View All Saved Passwords
3. 🔎 Search Account
4. ✏️ Modify Password
5. 🗑️ Delete Password
6. 🚪 Exit

---

## 🔎 Search Accounts

Search saved account entries by account name.

This makes it easier to locate a specific saved credential without manually checking the entire file.

---

## ✏️ Modify Password

Existing password entries can be modified through the account-management workflow.

---

## 🗑️ Delete Password

Individual saved entries can be removed from the local password database.

---

## 🛡️ Password Strength Checker

The project evaluates password characteristics such as:

* Password length
* Uppercase characters
* Lowercase characters
* Numbers
* Special characters

### Example Strength Result

* ✅ Length requirement satisfied
* ✅ Uppercase character included
* ✅ Lowercase character included
* ✅ Number included
* ✅ Special character included
* 🌟 Strength: **STRONG**

---

## 🚫 Duplicate Protection

The system is designed to detect:

* Duplicate account names
* Previously used passwords

This helps prevent accidental duplicate records.

---

# 🧠 How It Works

The overall workflow follows these steps:

1. ▶️ Start the application
2. 📋 Display the main menu
3. 🔐 Create, search, or manage a password
4. 🎲 Generate a password or enter one manually
5. 🛡️ Check password strength
6. 🚫 Check for duplicates
7. 💾 Save the entry
8. 🔁 Return to the main menu

---

# 🔐 Password Generation

The generator combines multiple character categories to create customizable passwords.

## Character Categories

### 🔢 Numbers

```text
0123456789
```

### 🔤 Lowercase Letters

```text
abcdefghijklmnopqrstuvwxyz
```

### 🔠 Uppercase Letters

```text
ABCDEFGHIJKLMNOPQRSTUVWXYZ
```

### 🔣 Special Characters

```text
!@#$%^&*()-_=+[]{};:,.<>?/
```

The user can choose the password length before generation.

---

# 🧪 Example Workflow

```text
✦ PASSWORD GENERATING SYSTEM ✦

1. Create New Password
2. View All Saved Passwords
3. Search Account
4. Modify Password
5. Delete Password
6. Exit

Enter choice: 1

Account Name: Netflix

1. Generate Password
2. Enter Password Manually

Enter choice: 1

Password Length: 16

Generated Password:
X7@kP2!mQ9#vR4$z
```

The application can then evaluate the generated password and save the account information locally.

---

# 🧩 Program Architecture

The project is organized around separate functions for the major operations.

```text
main()
│
├── createPassword()
│   ├── Generate password
│   ├── Manual password
│   ├── Duplicate check
│   └── Strength check
│
├── viewPasswords()
│
├── searchAccount()
│
├── modifyPassword()
│
├── deletePassword()
│
└── checkPasswordStrength()
```

This structure makes the program easier to understand, maintain, and expand.

---

# 🛠️ Technologies Used

<p align="center">

<img src="https://img.shields.io/badge/C-Programming-8A2BE2?style=flat-square&logo=c&logoColor=white" alt="C">
<img src="https://img.shields.io/badge/GCC-Compiler-00E5FF?style=flat-square&logo=gnu&logoColor=black" alt="GCC">
<img src="https://img.shields.io/badge/Git-Version%20Control-D946EF?style=flat-square&logo=git&logoColor=white" alt="Git">
<img src="https://img.shields.io/badge/GitHub-Repository-7B2CBF?style=flat-square&logo=github&logoColor=white" alt="GitHub">

</p>

### Language

**C**

### Compiler

**GCC / MinGW**

### Development Environment

**VS Code + Git Bash**

### Storage

**Local text file**

---

# 📁 Project Structure

```text
Password-generating-system/
│
├── 📄 passwordgeneration.c
├── 📄 passwords.txt
├── 📄 README.md
└── 📄 .gitignore
```

---

# ▶️ How To Run

## 1. Clone the repository

```bash
git clone https://github.com/Black-Butterfly-Codes/Password-generating-system.git
```

## 2. Enter the project directory

```bash
cd Password-generating-system
```

## 3. Compile

```bash
gcc passwordgeneration.c -o passwordgeneration
```

## 4. Run

### Windows / Git Bash

```bash
./passwordgeneration
```

---

# 🧪 Testing Checklist

| Test                 | Expected Result       | Status |
| -------------------- | --------------------- | ------ |
| Generate password    | Password generated    | ⬜      |
| Custom length        | Requested length used | ⬜      |
| Uppercase characters | Supported             | ⬜      |
| Lowercase characters | Supported             | ⬜      |
| Numbers              | Supported             | ⬜      |
| Special characters   | Supported             | ⬜      |
| Save account         | Entry stored          | ⬜      |
| View accounts        | Entries displayed     | ⬜      |
| Search account       | Correct entry found   | ⬜      |
| Modify password      | Entry updated         | ⬜      |
| Delete password      | Entry removed         | ⬜      |
| Duplicate account    | Prevented             | ⬜      |
| Duplicate password   | Detected              | ⬜      |
| Strength checker     | Correct analysis      | ⬜      |

---

# 📊 Security Concepts

This project explores several introductory password-security concepts.

## Password Length

Longer passwords generally provide a larger search space.

## Character Diversity

Using multiple character classes increases the possible combinations.

## Password Reuse

The project includes duplicate-password checking to demonstrate why reusing passwords can be problematic.

## Password Strength

The strength checker demonstrates how different password characteristics contribute to password quality.

> **Important:** This project is primarily an educational demonstration. It should not be treated as a production-grade password manager or secure credential vault.

---

# ⚠️ Security Notice

The current project stores password information in a local text file.

**Do not use this implementation to store real passwords or sensitive credentials.**

A production password manager should use appropriate security mechanisms such as:

* Strong password hashing where applicable
* Authenticated encryption for recoverable secrets
* Secure key derivation
* Secure random number generation
* Access controls
* Memory protection
* Secure secret storage

This project is intended for learning C programming and cybersecurity concepts.

---

# 🚀 Future Improvements

## Completed Features

* [x] Random password generation
* [x] Custom password length
* [x] Uppercase and lowercase support
* [x] Numbers
* [x] Special characters
* [x] Account management
* [x] Search functionality
* [x] Modify functionality
* [x] Delete functionality
* [x] Password strength checking
* [x] Duplicate detection

## Planned Improvements

* [ ] Improve secure random generation
* [ ] Encrypt stored credentials
* [ ] Add master-password authentication
* [ ] Improve data validation
* [ ] Add better error handling
* [ ] Add password entropy estimation
* [ ] Improve terminal UI
* [ ] Add automated tests
* [ ] Add project documentation

---

# 🎓 What I Learned

Building this project helped me practice:

* C functions
* Arrays and strings
* Pointers
* Structures
* File handling
* Input validation
* Random number generation
* Conditional logic
* Loops
* Modular programming
* Debugging
* Git
* GitHub
* Basic cybersecurity concepts

---

# 📈 Project Evolution

The project developed through the following stages:

1. **Simple Password Generator**
2. **Custom Password Length**
3. **Character Diversity**
4. **Password Strength Checking**
5. **Account Management**
6. **Search, Modify, and Delete Features**
7. **Duplicate Detection**
8. **Local Password Manager**

---

# 👤 Developer

<p align="center">

## 🦋 Black-Butterfly-Codes

<b>Cybersecurity • C Programming • Security Projects</b>

<br><br>

<a href="https://github.com/Black-Butterfly-Codes">
<img src="https://img.shields.io/badge/GitHub-Black--Butterfly--Codes-8A2BE2?style=for-the-badge&logo=github&logoColor=white" alt="GitHub Profile">
</a>

</p>

---

# 🔗 Project Links

## 👤 GitHub Profile

[Black-Butterfly-Codes](https://github.com/Black-Butterfly-Codes)

## 🔐 Password Generating System

[Password-generating-system](https://github.com/Black-Butterfly-Codes/Password-generating-system)

---

# ⭐ Support The Project

If you find this project useful or interesting:

* ⭐ Star the repository
* 🐛 Report bugs
* 💡 Suggest improvements
* 📚 Learn from the source code
* 🔐 Explore cybersecurity responsibly

---

<p align="center">

<img src="https://capsule-render.vercel.app/api?type=waving&color=00E5FF,8A2BE2&height=100&section=footer" alt="Neon footer">

<b>Built with C • Built for learning • Built for cybersecurity</b>

<br><br>

🦋 <b>Black-Butterfly-Codes</b>

</p>
