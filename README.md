# EnderGFX

## About

_EnderGFX_ grew out of increasing frustration with rewriting the same
SDL3/bgfx boilerplate — window management, GPU initialization, buffers,
cameras — every time I started a new 3D project. Once I had a decent grasp
of those basics, it became clear that repeating all of that for every
future project was pointless. Thus grew the need for a proper library that
abstracts SDL3 and bgfx behind a simple API, while still letting me drop
down to the native handles whenever I need more control than the
abstraction provides.

> **Fun fact:** the name almost ended up as _Zender_ (a.k.a. _Ezrender_)
> before settling on _Ender_, and finally _EnderGFX_ — a nod to _bgfx_.

## Installation

Installing _EnderGFX_ is straightforward via CMake. The public headers live
in `include/endergfx`, and the library can either use SDL3/bgfx already
installed on your system, or fetch and build them automatically.

If you already have SDL3 and bgfx installed:

```bash
cmake -B build -S .
cmake --build build
```

Without them installed:

```bash
cmake -B build -S . -DENDERGFX_FETCH_SDL3=ON -DENDERGFX_FETCH_BGFX=ON
cmake --build build
```

The only requirement for building _EnderGFX_ is a C++20-compatible
compiler. It has been developed and tested on Linux (Arch + Hyprland/Wayland);
Windows and macOS support the same native window-handle detection but have
not been thoroughly tested yet.

There are a few dependencies for this library. They are as follows:

- SDL3 (windowing, input, and platform abstraction)
- bgfx (cross-platform rendering backend)
- bx, bimg (bgfx support libraries)

## More Info

See [`examples/basic_window`](examples/basic_window) for a minimal usage
example.
