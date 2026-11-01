# Public-Safe C++ Subset

This directory contains compile-ready analytical code derived from the engineering concerns explored during ECHOSEEK. It is not the private stager and cannot retrieve, stage, inject, or execute a payload.

The subset is intentionally limited to defensive and non-operational functions:

- bounds-checked recognition of the DOS and PE signatures;
- extraction of selected COFF header fields;
- Shannon entropy calculation over a byte range;
- typed representation of the seven endpoint-visibility layers;
- a self-test built around a synthetic in-memory PE header.

## Build and test

```bash
cmake -S . -B build
cmake --build build
ctest --test-dir build --output-on-failure
```

The code is platform-independent and uses only the C++20 standard library.

## Deliberate exclusions

This directory contains no Windows execution APIs, network retrieval, native-call resolution, telemetry modification, memory mapping, thread dispatch, cryptographic material, or infrastructure configuration.
