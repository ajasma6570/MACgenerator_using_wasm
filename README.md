This project is a MAC address generator implemented in C++ with a WebAssembly (WASM) module and integrated with Node.js for server-side functionality. It generates primary and secondary MAC addresses based on a given 128-bit CID (Client Identifier).

Features
Generates primary and secondary MAC addresses from a 128-bit CID.
Frontend interface for user input.
Server-side logic implemented in Node.js.
WebAssembly (WASM) module written in C++ for MAC address generation.
Prerequisites
Node.js installed on your system.
C++ compiler for building the WASM module.

Installation
Clone the repository:

Copy code 
git clone https://github.com/ajasma6570/MACgenerator_using_wasm.git

Navigate to the project directory:

Copy code 
cd MACgenerator_using_wasm


Install Node.js dependencies:
Copy code
npm install


Build the WASM module:

Copy code
cd wasm
emcc mac_generator.cpp -o mac_generator.js -s WASM=1
Usage


Start the Node.js server:

Copy code
npm start
Open your web browser and navigate to http://localhost:2222.

Input the 128-bit CID into the provided field and click the "Generate MAC" button.

The generated MAC addresses will be displayed on the webpage.
