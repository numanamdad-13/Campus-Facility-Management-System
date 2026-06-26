
# Campus Facility Management System

A **console-based Campus Facility Management System** developed in **C++** using **Object-Oriented Programming (OOP)** principles. The system allows students and faculty to book campus facilities while administrators manage facilities and approve or reject booking requests. Data is stored using text files to ensure persistence between program executions.

---

## 📌 Project Overview

The Campus Facility Management System is designed to automate the process of managing campus facilities such as seminar halls, auditoriums, computer labs, and extra rooms. The application provides different functionalities based on user roles (Student, Faculty, and Admin) while demonstrating core OOP concepts and file handling in C++.

---

## ✨ Features

### 👨‍🎓 Student
- Register and Login
- View available facilities
- Request facility booking
- View booking history
- Cancel bookings

### 👨‍🏫 Faculty
- Register and Login
- View available facilities
- Request bookings
- View booking history

### 👨‍💼 Administrator
- Register and Login
- Add new facilities
- Remove facilities
- View pending booking requests
- Approve or reject bookings
- Manage the overall system

---

## 🏢 Facilities Included

- Extra Room
- Seminar Hall
- Computer Lab
- Auditorium

---

## 💻 Object-Oriented Programming Concepts

### ✔ Classes and Objects
The project is built using multiple classes:
- User
- Student
- Faculty
- Admin
- Facility
- Booking
- SystemManager
- FinalManager

### ✔ Inheritance
Inheritance is used to reduce code duplication.

```
User
│
├── Student
│      │
│      └── Faculty
│
└── Admin

SystemManager
      │
      └── FinalManager
```

### ✔ Encapsulation
- Private data members
- Protected members
- Public getter and setter functions

### ✔ Abstraction
The `SystemManager` class acts as an abstract class by using pure virtual functions.

```cpp
virtual void loaddata() = 0;
virtual void registeruser() = 0;
virtual user* login() = 0;
virtual void savedata() = 0;
```

### ✔ Polymorphism
Runtime polymorphism is implemented through:
- Virtual Functions
- Function Overriding

Example:
- `showmenu()`
- `savedata()`
- `loaddata()`
- `login()`
- `registeruser()`

### ✔ Dynamic Memory Allocation
Objects are created dynamically using:

```cpp
new
```

Memory is released using destructors to avoid memory leaks.

---

## 📂 File Handling

The project stores all information using text files.

| File | Purpose |
|------|----------|
| users.txt | Stores user information |
| facilities.txt | Stores facility details |
| bookings.txt | Stores booking records |

---

## 📁 Project Structure

```
Campus-Facility-Management-System/
│
├── main.cpp
├── users.txt
├── facilities.txt
├── bookings.txt
├── README.md
└── LICENSE
```

---

## 🛠 Technologies Used

- C++
- Object-Oriented Programming (OOP)
- File Handling
- Standard Template Library (STL)
- Visual Studio / Code::Blocks / Dev-C++

---

## ⚙ System Workflow

1. User registers.
2. User logs into the system.
3. Student/Faculty views facilities.
4. Booking request is submitted.
5. Administrator reviews booking.
6. Admin approves or rejects the request.
7. Booking data is saved to files.

---

## 🎯 Learning Outcomes

This project demonstrates:

- Object-Oriented Programming
- Inheritance
- Encapsulation
- Abstraction
- Polymorphism
- File Handling
- Dynamic Memory Allocation
- STL Vectors
- User Authentication
- Menu-Driven Programming

---

## 🚀 Future Improvements

- Password encryption
- Date and time validation
- Search and filter facilities
- Booking conflict detection
- Graphical User Interface (GUI)
- Database integration (MySQL)
- Email notifications
- Online booking support

---

## 👨‍💻 Author

**Numan**

Computer Science Student

---

## 📜 License

This project is created for educational and learning purposes.
