#include <windows.h>

// Authentic excerpt from the private implant.cpp source.
// The function signature and body below are unchanged.
// Adjacent loader and execution code is intentionally not published.

void XorMemory(PVOID base, SIZE_T size, BYTE* key, DWORD keyLen) {
    BYTE* p = (BYTE*)base;
    for (SIZE_T i = 0; i < size; i++) {
        p[i] ^= key[i % keyLen];
    }
}
