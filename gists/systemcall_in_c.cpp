// WARNING: POTENTIAL SECURITY VULNERABLE CODE
// taking user argument and running then using "system" command is dangerous
// always sanity check the "command" 

#include <fstream>
#include <string>
#include <iostream>

std::string convert_bin_to_int(std::string command) {
  std::string command_wrap = "python -c \"" + command + "\" > output.txt";

  // Execute the command and capture output in "output.txt"
  int result = system(command_wrap.c_str());

  if (result == 0) {
    // Read the captured output from the file
    std::ifstream output_file("output.txt");
    if (output_file.is_open()) {
      std::string output;
      std::getline(output_file, output);
      output_file.close();
      remove("output.txt");
      return output;
    } else {
      std::cerr << "Error: Could not open output.txt" << std::endl;
      exit(1);
    }
  } else {
    std::cerr << "Error: Command execution failed" << std::endl;
    exit(1);
  }
}