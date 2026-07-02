#include <algorithm>
#include <array>
#include <cstdint>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <vector>

namespace fs = std::filesystem;

static const std::size_t UINT64_BYTES = 8;
static const std::size_t UINT32_BYTES = 4;
static const std::size_t UINT16_BYTES = 2;

static const uint32_t MAGIC = 0x5241584E;
static const uint64_t ARCHIVE_HEADER_SIZE = 24;
static const std::string ARCHIVE_EXTENSION = ".nxar";

template <std::size_t N, class UInt>
std::array<uint8_t, N> to_le_bytes(const UInt value) {
    std::array<uint8_t, N> bytes;
    for (std::size_t i = 0; i < bytes.size(); ++i) {
        bytes[i] = static_cast<uint8_t>((value >> (i * 8)) & 0xFF);
    }

    return bytes;
}

fs::path normalize_path(const fs::path& raw_path) {
    std::string str = raw_path.string();
    if (str.find_last_of('\\') != std::string::npos) {
        str.pop_back();
    }

    return str;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cout << "[ERROR]: arguments do not match (request:2 now:" << argc << ")" << std::endl;
        return 1;
    }

    fs::path root = fs::absolute(argv[1]);
    std::string target_name = normalize_path(root).filename().string();
    std::vector<uint8_t> file_data;
    std::vector<uint8_t> entry_list;
    uint32_t entry_count = 0;
    for (const auto& entry : fs::recursive_directory_iterator(root)) {
        if (!entry.is_regular_file()) {
            continue;
        }

        fs::path entry_path = entry.path();
        std::ifstream ifs(entry_path.c_str(), std::ios::binary | std::ios::ate);
        if (!ifs.is_open()) {
            std::cout << "[ERROR] file open (path:" << entry_path << ")" << std::endl;
            continue;
        }
        std::streamsize file_size = ifs.tellg();
        ifs.seekg(0, std::ios::beg);

        std::vector<uint8_t> buffer;
        buffer.resize(static_cast<std::size_t>(file_size));
        if (!ifs.read(reinterpret_cast<char*>(buffer.data()), file_size)) {
            std::cout << "[ERROR] read (path:" << entry_path << ")" << std::endl;
            continue;
        }
        file_data.insert(file_data.end(), buffer.begin(), buffer.end());

        std::string access_key = target_name + "/" + fs::relative(entry.path(), root).string();
        std::replace(access_key.begin(), access_key.end(), '\\', '/');

        auto bytes_file_size = to_le_bytes<UINT64_BYTES>(static_cast<uint64_t>(file_size));
        auto bytes_key_size = to_le_bytes<UINT16_BYTES>(static_cast<uint16_t>(access_key.length()));
        entry_list.insert(entry_list.end(), bytes_file_size.begin(), bytes_file_size.end());
        entry_list.insert(entry_list.end(), bytes_key_size.begin(), bytes_key_size.end());
        entry_list.insert(entry_list.end(), access_key.begin(), access_key.end());
        ++entry_count;
        ifs.close();
        std::cout << "[load file] No." << entry_count << " " << access_key << "(size: " << file_size << ")" << std::endl;
    }

    std::vector<uint8_t> archive;
    auto bytes_magic = to_le_bytes<UINT32_BYTES>(MAGIC);
    auto bytes_entry_count = to_le_bytes<UINT32_BYTES>(entry_count);
    auto bytes_data_size = to_le_bytes<UINT64_BYTES>(static_cast<uint64_t>(file_data.size()));
    auto bytes_data_offset = to_le_bytes<UINT64_BYTES>(ARCHIVE_HEADER_SIZE + static_cast<uint64_t>(entry_list.size()));
    archive.insert(archive.end(), bytes_magic.begin(), bytes_magic.end());
    archive.insert(archive.end(), bytes_entry_count.begin(), bytes_entry_count.end());
    archive.insert(archive.end(), bytes_data_size.begin(), bytes_data_size.end());
    archive.insert(archive.end(), bytes_data_offset.begin(), bytes_data_offset.end());
    archive.insert(archive.end(), entry_list.begin(), entry_list.end());
    archive.insert(archive.end(), file_data.begin(), file_data.end());

    fs::path output_path = normalize_path(root).parent_path() / (target_name + ARCHIVE_EXTENSION);
    std::ofstream ofs(output_path.c_str(), std::ios::binary);
    if (!ofs.is_open()) {
        std::cout << "[ERROR] file open (path:" << output_path << ")" << std::endl;
        return 1;
    }

    ofs.write(reinterpret_cast<const char*>(archive.data()), archive.size());
    ofs.close();

    std::cout << "[archive complete] " << output_path.string() << std::endl;

    return 0;
}