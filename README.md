# 📅 Desktop Timetable Generator

**Desktop Timetable Generator is a tool that facilitates the generation of timetables for teachers.**

## 🚀 Key Features

- 🌟 **Effortless Timetable Generation:** The DesktopTimetable Generator simplifies the creation of schedules for university professors, streamlining the process with intuitive tools and options.

- 🧩 **Flexible and Customizable:** Built with wxWidgets and OpenXLSX, the project boasts a modular architecture, allowing for easy customization and expansion to accommodate various university timetabling needs.

- 📚 **Intuitive User Interface:** User-friendly interface makes it easy to set up templates and schedules.

- 🛠️ **JSON Configuration:** Utilizing JSON for Modern C++, the project ensures code simplicity and readability, facilitating the configuration and management of templates.

- 🐳 **Platform Agnostic Deployment:** Thanks to CMake, the DesktopTimetable Generator supports platform-agnostic deployment, enabling professors to utilize it across different operating systems with ease.

## 🛠️ Technology Stack
- [wxWidgets](https://github.com/wxWidgets/wxWidgets): User-friendly interface.
- [OpenXLSX](https://github.com/troldal/OpenXLSX): Reading schedules.
- [JSON for Modern C++](https://github.com/nlohmann/json): Template serealization.
- [CMake](https://cmake.org): Application building.

## 🏁 Installation and Running

To run the project, follow these steps:
### Building on Windows
1. Clone the repository:
   ```bash
   git clone --recurse-submodules https://github.com/f3n1b00t/desktop-timetable.git
   cd desktop-timetable
   ```
2. Make dir for build:
   ```bash
   mkdir build
   cd build
3. Run cmake:
   ```bash
   cmake ..
   ```
4. Open Visual Studio project
   ```bash
   start devenv DesktopTimetable.sln
   ```
5. Enjoy the project! 🎉

### Building on Linux
1. Clone the repository:
   ```bash
   git clone --recurse-submodules https://github.com/f3n1b00t/desktop-timetable.git
   cd desktop-timetable
   ```
2. Make dir for build:
   ```bash
   mkdir build
   cd build
   ```
3. Run cmake:
   ```bash
   export CC=clang
   export CXX=clang++
   cmake ..
   ```
4. Run make:
   ```bash
   make
   ```
5. Enjoy the project! 🎉
