#include <windows.h>
#include <iostream>

void GetClipboardText() {
    // Try to open the clipboard
    if (!OpenClipboard(nullptr)) {
        std::cerr << "Failed to open clipboard" << std::endl;
        return;
    }

    // Get the clipboard data in text format
    HANDLE hData = GetClipboardData(CF_TEXT);
    if (hData == nullptr) {
        std::cerr << "Failed to get clipboard data" << std::endl;
        CloseClipboard();
        return;
    }

    // Lock the handle to get the actual text pointer
    char* pszText = static_cast<char*>(GlobalLock(hData));
    if (pszText == nullptr) {
        std::cerr << "Failed to lock clipboard data" << std::endl;
        CloseClipboard();
        return;
    }

    // Output the text
    std::cout << "Clipboard contains: " << pszText << std::endl;

    // Unlock the memory
    GlobalUnlock(hData);

    // Close the clipboard
    CloseClipboard();
}

int main() {
    GetClipboardText();
    return 0;
}
