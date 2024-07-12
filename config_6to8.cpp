#include <iostream>
#include <fstream>
#include <vector>
#include <string>

void modifyLine(
    std::vector<std::string>& lines, 
    int lineNumber, 
    const std::string& oldContent, 
    const std::string& newContent
) {
    if (lineNumber >= 0 && lineNumber < lines.size()) {
        size_t pos = lines[lineNumber].find(oldContent);
        if (pos != std::string::npos) {
            lines[lineNumber].replace(pos, oldContent.length(), newContent);
        }
    }
}

int main() {
    std::string filename = "config.plist";
    std::ifstream fileIn(filename);
    if (!fileIn) {
        std::cerr << "Unable to open file " << filename << std::endl;
        return 1;
    }

    std::vector<std::string> lines;
    std::string line;
    while (std::getline(fileIn, line)) {
        lines.push_back(line);
    }
    fileIn.close();

    modifyLine(
        lines, 
        935, 
        "<data>uAYAAAAA</data>", 
        "<data>uAgAAAAA</data>"
    );
    modifyLine(
        lines, 
        965, 
        "<data>ugYAAAAA</data>", 
        "<data>uggAAAAA</data>"
    );
    modifyLine(
        lines, 
        995, 
        "<data>ugYAAACQ</data>", 
        "<data>uggAAACQ</data>"
    );
    modifyLine(
        lines, 
        1025, 
        "<data>ugYAAAA=</data>", 
        "<data>uggAAAA=</data>"
    );

    std::ofstream fileOut(filename);
    if (!fileOut) {
        std::cerr << "Unable to open file " << filename << std::endl;
        return 1;
    }

    for (const auto& modifiedLine : lines) {
        fileOut << modifiedLine << std::endl;
    }
    fileOut.close();

    std::cout << "File modified successfully." << std::endl;
    return 0;
}
