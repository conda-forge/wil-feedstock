#include <windows.h>
#include <wil/resource.h>
#include <iostream>
int main() {
    bool cleaned = false;
    {
        auto cleanup = wil::scope_exit([&] { cleaned = true; });
        wil::unique_handle event(CreateEventW(nullptr, TRUE, FALSE, nullptr));
        if (!event || !SetEvent(event.get())) return 1;
        if (WaitForSingleObject(event.get(), 0) != WAIT_OBJECT_0) return 2;
        if (!ResetEvent(event.get())) return 3;
        if (WaitForSingleObject(event.get(), 0) != WAIT_TIMEOUT) return 4;
    }
    if (!cleaned) return 5;
    std::cout << "Installed WIL Windows event ownership and scope cleanup passed\n";
}
