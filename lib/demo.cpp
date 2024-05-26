#include <emscripten.h>
#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <cctype>
#include <cstring> 

// Function to format MAC address with colons inserted between every two pairs of characters
std::string formatMACAddress(uint64_t macInt) {
    std::ostringstream macStream;
    macStream << std::hex << std::uppercase << std::setw(12) << std::setfill('0') << macInt;
    std::string macString = macStream.str();

    // Insert colons between every two pairs of characters
    for (size_t i = 2; i < macString.length(); i += 2) {
        macString.insert(i, ":");
        i++; // Skip the inserted colon
    }

    return macString;
}

extern "C" {
    EMSCRIPTEN_KEEPALIVE
    const char* generateMACAddresses(const std::string& cid) {
        // Take the first 32 characters of the CID string
        std::string truncatedCID = cid.substr(0, 32);

        // Check if truncated CID is valid
        bool validCID = true;
        if (truncatedCID.size() != 32) {
            validCID = false;
        } else {
            for (char c : truncatedCID) {
                if (!std::isxdigit(c)) {
                    validCID = false;
                    break;
                }
            }
        }

        if (!validCID) {
            return strdup("Invalid 128-bit CID format");
        }

        // Extract last 64 bits from the truncated CID
        std::string last64Bits = truncatedCID.substr(16);

        // Convert to 48-bit MAC address
        std::stringstream ss(last64Bits);
        uint64_t macInt;
        ss >> std::hex >> macInt;
        uint64_t primaryMacInt = macInt & 0xFFFFFFFFFFFFULL;

        // Clear the multicast bit (least significant bit of the first byte)
        primaryMacInt &= ~0x010000000000ULL;

        // Increment to get the secondary MAC address
        uint64_t secondaryMacInt = (primaryMacInt + 1) & 0xFFFFFFFFFFFFULL;

        // Format MAC addresses with colons inserted between every two pairs of characters
        std::string primaryMAC = formatMACAddress(primaryMacInt);
        std::string secondaryMAC = formatMACAddress(secondaryMacInt);

        // Return the combined MAC addresses string
        return strdup((primaryMAC + "|" + secondaryMAC).c_str());
    }
}
