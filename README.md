# Student Management System (C++)

A console-based Student Management System developed in C++ to demonstrate core Object-Oriented Programming (OOP) and file handling concepts. The project simulates a basic academic record system with separate roles for administrators and students, focusing on clean structure, data persistence, and logical flow.

## Features

- Admin and Student login system
- Add, update, search, and delete student records
- View students grouped by department and enrollment year
- Persistent storage using file handling (fstream)
- Simple menu-driven console interface

## Concepts & Technologies Used

**Object-Oriented Programming (OOP)**
- Inheritance (Person → Student → AcademicRecord)
- Polymorphism (virtual functions)
- Encapsulation (private data members with getters/setters)

**STL Containers**
- Vector and algorithm library

**File Handling**
- Read/write student records to text files

**Additional Features**
- Input validation and menu control
- Basic data abstraction and modular design

## Purpose

This project was built for learning and academic practice, focusing on applying theoretical OOP concepts in a practical, real-world–style C++ application.

## Quick Start

### Compile & Run

```bash
g++ -std=c++11 student_management.cpp -o student_mgmt
./student_mgmt
```

### Usage

1. Select user role (Admin/Student)
2. Login with credentials
3. Navigate through menu options
4. Perform CRUD operations on student records

## Future Improvements

- Better input validation and error handling
- Sorting and filtering records
- Improved authentication and security
- GUI-based interface

## License

MIT License - Feel free to use for educational purposes

---

**Clean, structured, and beginner-friendly** — ideal for understanding how larger C++ programs are organized.
