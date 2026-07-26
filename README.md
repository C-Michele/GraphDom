# GraphDom

**GraphDom** is a modern C++17 library for graph data structures designed around a hierarchy of abstract interfaces and concrete implementations.

The main goal of the project is to separate **graph algorithms** from **graph implementations**. Algorithms can therefore be written against the abstract interfaces, while users are free to choose the concrete graph implementation that best fits their needs.

The library is header-oriented, CMake-friendly, and provides both **static** and **shared** builds.

---

# Features

- Modern C++17 API
- Header-oriented public interface
- Abstract graph hierarchy
- Concrete graph implementations
- Directed and undirected graphs
- Set graphs and multiset graphs
- Vertex labels
- Edge labels
- Generic algorithms can target the abstract interfaces
- CMake package support
- Static and shared library installation

---

# Requirements

- CMake ≥ 3.20
- A C++17 compatible compiler

---

# Building

The project uses CMake.

To build the library **without the unit tests**:

```bash
cmake -S . -B build \
    -DBUILD_TESTING=OFF

cmake --build build
```

---

# Installing

After building:

```bash
cmake --install build
```

The installation exports a CMake package that can later be found with

```cmake
find_package(GraphDom REQUIRED)
```

---

# Using GraphDom from another project

The package exports a single public target:

```cmake
GraphDom::GraphDom
```

A minimal `CMakeLists.txt` looks like:

```cmake
cmake_minimum_required(VERSION 3.20)

project(MyProject)

find_package(GraphDom REQUIRED)

add_executable(MyExecutable
    main.cpp
)

target_link_libraries(
    MyExecutable
    PRIVATE
        GraphDom::GraphDom
)
```

---

# Choosing between the static and shared library

Both the **static** and the **shared** versions are installed.

The package exposes a single imported target whose implementation depends on the variable

```cmake
GraphDom_USE_STATIC_LIBS
```

## Static library

```cmake
set(GraphDom_USE_STATIC_LIBS ON)

find_package(GraphDom REQUIRED)

target_link_libraries(
    MyExecutable
    PRIVATE
        GraphDom::GraphDom
)
```

## Shared library

```cmake
set(GraphDom_USE_STATIC_LIBS OFF)

find_package(GraphDom REQUIRED)

target_link_libraries(
    MyExecutable
    PRIVATE
        GraphDom::GraphDom
)
```

If the variable is not specified, the shared library is selected.

---

# Including the library

The complete public API can be included with

```cpp
#include <graphdom/graphdom.h>
```

Alternatively, the library is organized into two aggregate headers:

```cpp
#include <graphdom/abstract_classes.h>
```

containing the abstract interfaces, and

```cpp
#include <graphdom/concrete_classes.h>
```

containing the concrete implementations.

---

# Library organization

The library is divided into two conceptual layers.

## Abstract interfaces

The abstract interfaces describe graph capabilities independently from any particular implementation.

Examples include:

- graph
- set graph
- multiset graph
- labeled vertex graph
- labeled edge graph
- mixed graph variants

These interfaces are intended to be the primary abstraction layer for writing reusable graph algorithms.

---

## Concrete implementations

Concrete classes provide actual graph containers implementing combinations of the abstract interfaces.

Current implementations include fully labeled

- directed set graphs
- undirected set graphs
- directed multiset graphs
- undirected multiset graphs

Future implementations will extend the available combinations without changing the abstract API.

---

# Reading the documentation

There are two equally valid ways to explore the documentation.

## Top-down approach (recommended)

This approach is ideal for understanding the architecture of the library.

Recommended order:

1. Start from the abstract interfaces.
2. Understand the relationships between the different graph concepts.
3. Explore the concrete implementations.
4. Finally study the algorithms using those abstractions.

This path emphasizes the design philosophy behind GraphDom.

---

## Bottom-up approach

This approach is convenient if you simply want to use the library immediately.

Recommended order:

1. Start from the concrete graph classes.
2. Learn how to create and manipulate graphs.
3. Afterward explore the abstract interfaces to understand how generic algorithms are built.

---

# Design philosophy

GraphDom is designed around the idea that graph algorithms should depend on **capabilities**, not on specific graph containers.

Instead of writing an algorithm for one concrete graph class, algorithms should be written against the smallest abstract interface that provides the required operations.

This promotes:

- code reuse;
- implementation independence;
- easier testing;
- future extensibility.

---

# Roadmap

The project is still under active development.

Planned milestones include:

- Implement the remaining concrete graph classes covering every meaningful combination of the available abstract interfaces.
- Introduce an `unordered_set`-like container specialized for storing `vertex_handle` objects.
- Develop the first collection of graph algorithms written exclusively against the abstract interfaces, maximizing portability across concrete graph implementations.

---

# License

GraphDom is distributed under the Apache-2.0 License.