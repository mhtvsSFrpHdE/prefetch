## Clang format

When connect Qt Signal and slot, clangd format from `,void*` to `, void *`.  
Qt Creator suggest not using space in connect macro.

Wrap code with clang comment to disable clangd format temporary:

```
// clang-format off
...
// clang-format on
```
