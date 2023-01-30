#include <cstdio>
#include <string>
#include <iostream>
#include <memory>
#include <utility>
#include <variant>
#include <stack>
#include <vector>
#include <functional>
#include <optional>
#include <map>
#include <climits>

class FileSystem {
public:
    struct File {
        std::string name;
        size_t size;
    };

    struct Directory {
        std::string name;
        Directory* parent;
        std::vector<File> files;
        std::vector<std::unique_ptr<Directory>> dirs;
    };

    FileSystem(){
        root = std::make_unique<Directory>(Directory{"/", nullptr, {}, {}});
        cwd = root.get();
    }

    void cd(const std::string &name){

        if (name == ".."){
            if (cwd->parent == nullptr){
                throw std::runtime_error("cd: Cannot cd .. from root directory");
            }
            cwd = cwd->parent;
            return;
        }

        std::optional<Directory*> dir = findDir(name);
        if (!dir.has_value()){
            throw std::runtime_error("cd: Directory " + name + " does not exist");
        }

        cwd = dir.value();
    }

    void createDirectory(const std::string &name) {
        if (findDir(name)){
            return;
        }

        auto newDir = std::make_unique<Directory>(Directory{name, cwd, {}, {}});
        cwd->dirs.push_back(std::move(newDir));
    }

    void createFile(const std::string &name, size_t size) {
        if (findFile(name)){
            return;
        }

        cwd->files.push_back({name, size});
    }

    std::optional<Directory*> findDir(const std::string &name) const {
        for (const auto& dirPtr : cwd->dirs){
            if (dirPtr->name == name){
                return dirPtr.get();
            }
        }
        return std::nullopt;
    }

    std::optional<File> findFile(const std::string &name) const {
        if (!cwd){
            return std::nullopt;
        }

        for (const auto& file : cwd->files){
            if (file.name == name){
                return file;
            }
        }
        return std::nullopt;
    }

    std::map<Directory*, size_t> directorySizes(){
        std::map<Directory*, size_t> sizes;
        directorySizesRecursive(root.get(), sizes);
        return sizes;
    }

    Directory* getCwd() const {
        return cwd;
    }

    Directory* getRoot() const {
        return root.get();
    }

private:
    std::unique_ptr<Directory> root;
    Directory* cwd;

    size_t directorySizesRecursive(Directory* dir, std::map<Directory*, size_t>& sizes){
        size_t fileSizes = 0;
        for (const File& file : dir->files){
            fileSizes += file.size;
        }

        size_t dirSizes = 0;
        for (const auto& childDirs : dir->dirs){
            dirSizes += directorySizesRecursive(childDirs.get(), sizes);
        }

        sizes[dir] = fileSizes + dirSizes;
        return sizes[dir];
    }
};

bool isLsFile(const std::string &line){
    return !line.empty() && isdigit(line[0]);
}

bool isLsDirectory(const std::string &line){
    return line.size() >= 3 && line.substr(0, 3) == "dir";
}


void handleCd(const std::string &dirName, FileSystem& fileSystem){
    if (dirName == "/"){
        return;
    }

    if (dirName != ".." && !fileSystem.findDir(dirName).has_value()){
        fileSystem.createDirectory(dirName);
    }

    fileSystem.cd(dirName);
}

std::pair<std::string, std::string> splitOnSpace(const std::string& str){
    size_t spacePos = str.find(' ');
    return std::make_pair(str.substr(0, spacePos), str.substr(spacePos+1));
}

int handleLs(std::vector<std::string> lines, int lineNum, FileSystem& fileSystem){
    lineNum++;
    while (lineNum < lines.size() && (isLsFile(lines[lineNum]) || isLsDirectory(lines[lineNum]))){
        std::string line = lines[lineNum];
        if (isLsFile(line)){
            auto [sizeStr, name] = splitOnSpace(lines[lineNum]);
            if (!fileSystem.findFile(name)){
                fileSystem.createFile(name, std::stoul(sizeStr));
            }
        } else {
            std::string dir = lines[lineNum].substr(4);
            if (!fileSystem.findDir(dir)){
                fileSystem.createDirectory(dir);
            }
        }
        lineNum++;
    }

    return lineNum;
}

std::vector<std::string> readLines(){
    std::string line;
    std::vector<std::string> lines;
    while (std::getline(std::cin, line)){
        lines.push_back(line);
    }
    return lines;
}

void part1And2(){
    std::vector<std::string> lines = readLines();
    FileSystem fileSystem;
    int lineNum = 0;
    while (lineNum < lines.size()){
        std::string cmd = lines[lineNum];
        if (cmd.at(0) == '$' && cmd.substr(2, 2) == "cd"){
            std::string dir = cmd.substr(5);
            handleCd(dir, fileSystem);
            lineNum++;
        } else if (cmd == "$ ls"){
            lineNum = handleLs(lines, lineNum, fileSystem);
        }
    }

    std::map<FileSystem::Directory*, size_t> sizes = fileSystem.directorySizes();
    size_t under100kSum = 0;
    for (const auto& [directory, size] : sizes){
        if (size <= 100000){
            under100kSum += size;
        }
    }

    std::cout << "Part 1: " << under100kSum << "\n";

    size_t totalSize = 70000000;
    size_t requiredSpace = 30000000;
    size_t availableSpace = totalSize - sizes[fileSystem.getRoot()];
    size_t minDirectoryToDelete = ULONG_MAX;

    for (const auto& [directory, size] : sizes){
        if (availableSpace + size >= requiredSpace){
            minDirectoryToDelete = std::min(minDirectoryToDelete, size);
        }
    }

    std::cout << "Part 2: " << minDirectoryToDelete << "\n";
}


int main(int argc, char* argv[]){
    freopen("input.txt", "r", stdin);
    part1And2();
    return 0;
}