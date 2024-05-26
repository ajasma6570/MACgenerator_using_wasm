const express = require("express");
const app = express();
const path = require("path");

app.use(express.json());

app.use(
  express.static("public", {
    setHeaders: (res, path, stat) => {
      if (path.endsWith(".wasm")) {
        res.set("Content-Type", "application/wasm");
      }
    },
  })
);

// Import your WebAssembly module
const Module = require("./public/demo.js"); // Adjust the path accordingly

// Define the onRuntimeInitializedHandler function
function onRuntimeInitializedHandler(cid) {
  // Call the WebAssembly function to generate MAC addresses 
  const result = Module.ccall(
    "generateMACAddresses", // Function name
    "string", // Return type
    ["string"], // Argument types
    [cid] // Arguments
  );

  // Return the result
  return result;
}

// Wait for the Emscripten runtime to be initialized
Module.onRuntimeInitialized = function () {
  // Extract CID from request body and call onRuntimeInitializedHandler
  app.post("/process-cid", (req, res) => {
    const cid = req.body.cid;
    const result = onRuntimeInitializedHandler(cid);
    const extractResult = result.toLowerCase().split("|");
    res.json({
      primary: extractResult[0],
      secondary: extractResult[1],
    });
  });
};

app.listen(2222, () => {
  console.log("Server is running..");
});
