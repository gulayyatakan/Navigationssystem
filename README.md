# Navigationssystem

A simple Qt-based navigation system for managing and visualizing geographic locations on a map of Germany. This application allows users to create and interact with locations (addresses, POIs, and their own position), calculate distances, and display information using a graphical interface.

---

## Features

- 🗺️ Interactive map of Germany with labeled cities and positions  
- ➕ Add new locations (Address or POI) with custom parameters  
- 📍 Move and set your personal location (`MeinOrt`)  
- 📏 Calculate distance between two selected cities  
- 🔎 Display information about any selected location  
- 💾 Save/load map data to/from file  
- 🧪 Unit tests included (via QTest)

---

## Screenshots

> _Screenshots coming soon..._

---

## Build Instructions

### Prerequisites

- Qt 6 (tested with **Qt 6.7.3**)
- C++17 compatible compiler
- `qmake` and `make` installed (included in Qt Creator or `qt6-tools` package)

### Automatic Qt Detection (Unix/macOS)

> If `qmake` is not found, ensure Qt is installed and added to your `PATH`:

```bash
# Check if qmake is available
which qmake

# Or, for Qt6-specific:
which qmake6
```

If not found, install via:

```bash
# Ubuntu/Debian
sudo apt install qt6-base-dev qt6-tools-dev-tools

# macOS (Homebrew)
brew install qt@6
brew link --force qt@6
```

---

### 🐧 Build on Linux/macOS

```bash
git clone https://github.com/gulayyatakan/Navigationssystem.git
cd Navigationssystem
qmake
make
./Navigationssystem
```

---

### 🪟 Build on Windows

You can use **Qt Creator** for an easier experience:

1. Download & install [Qt + Qt Creator](https://www.qt.io/download)
2. Open `Navigationssystem.pro` in Qt Creator
3. Configure a `Desktop` kit (MSVC or MinGW)
4. Click ▶️ **Run**

Alternatively (via terminal if `qmake` is available):

```cmd
qmake Navigationssystem.pro
mingw32-make   # or just 'nmake' if using MSVC
Navigationssystem.exe
```

---

## Run Tests

Tests will automatically run on application startup via `QTest`.

---

## Project Structure

- `mainwindow.*`: GUI logic and UI layout  
- `navigationsverwaltung.*`: Core logic for managing locations  
- `ort.*`: Abstract base class  
- `adresse.*`, `poi.*`, `meinort.*`: Derived location types  
- `main.cpp`: Starts GUI and runs tests  
- `navigationssystem_test.*`: Unit test implementation

---

## License

This project is for educational and learning purposes. No license yet specified.

---

## Author

Created by **Atakan Gülay** – [GitHub Profile](https://github.com/gulayyatakan)
