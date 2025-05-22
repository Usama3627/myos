# MyOS - A Simple Operating System

A minimal operating system written from scratch, currently featuring a basic terminal with keyboard input and screen output capabilities. This project is a learning exercise in operating system development and will be expanded with more features over time.

## 🚀 Current Features

- **Basic Terminal**
  - Text input/output support
  - Keyboard input handling (US QWERTY layout)
  - Screen clearing functionality
  - Basic text display with white-on-black color scheme
  - Support for special characters and basic keyboard input

## 🎯 Planned Features

### Short Term
- [ ] Color support for terminal
- [ ] Cursor movement (arrow keys)
- [ ] Command history
- [ ] Basic command parser
- [ ] Text editing capabilities

### Medium Term
- [ ] Basic file system
- [ ] Process management
- [ ] Simple shell with basic commands
- [ ] Memory management
- [ ] Device drivers

## 🛠️ Technical Details

### Boot Process
- Uses GRUB as the bootloader
- Implements Multiboot specification
- Written in C and x86 Assembly
- 32-bit protected mode

### Memory Layout
- VGA text mode at 0xB8000
- 80x25 character display
- 16KB kernel stack
- Basic memory management

### Building and Running

#### Prerequisites
- GCC (with 32-bit support)
- NASM (Netwide Assembler)
- GRUB
- QEMU (for testing)

#### Build Instructions
This is tested on Ubuntu 24.04 LTS

Make sure you install necessary libraries

`sudo apt update`

`sudo apt-get install build-essential nasm qemu-system-i386 grub-pc-bin mtools`

```bash
# Clone the repository
git clone https://github.com/usama3627/myos.git
cd myos

make run
```

## 📁 Project Structure
myos/<br>
├── loader.s &nbsp;&nbsp;&nbsp;&nbsp;# Assembly bootstrap code<br>
├── kmain.c &nbsp;&nbsp;&nbsp;&nbsp;# Main kernel code<br>
├── grub.cfg &nbsp;&nbsp;&nbsp;&nbsp;# GRUB configuration<br>
├── Makefile &nbsp;&nbsp;&nbsp;&nbsp;# Build configuration<br>
└── README.md &nbsp;&nbsp;&nbsp;&nbsp;# This file<br>


## 🤝 Contributing

Contributions are welcome! If you'd like to contribute:

1. Fork the repository
2. Create your feature branch (`git checkout -b feature/AmazingFeature`)
3. Commit your changes (`git commit -m 'Add some AmazingFeature'`)
4. Push to the branch (`git push origin feature/AmazingFeature`)
5. Open a Pull Request

## 📄 License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## 👤 Author

**Usama3627**
- GitHub: [@Usama3627](https://github.com/Usama3627)

## 🙏 Acknowledgments

- GRUB for the bootloader
- OSDev community for their excellent documentation
- All contributors who help improve this project

---

⭐ Star this repository if you find it helpful!