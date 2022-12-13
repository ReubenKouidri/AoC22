#include <string>
#include <string_view>
#include <utility>
#include <vector>


struct File
{
    explicit File(std::string_view name, size_t size)
        : name_ {name}
        , size_ {size}
    {}
    [[maybe_unused]] [[nodiscard]] size_t size() const{
        return size_;
    }
private:
    std::string name_ {};
    size_t size_ {};
};


struct Directory
{
    explicit Directory(std::vector<Directory>& dirs,
                       std::vector<File>& files)
        : dirs_ {std::move(dirs)}
        , files_ {std::move(files)}
    {}

    [[nodiscard]] size_t totalSize() const{
        size_t total = 0;
        for (const auto& d : dirs_){
            for (const auto& f : d.files_){
                total += f.size();
            }
        }
    }

    [[nodiscard]] size_t totalSize() const{
        size_t total = 0;
        for (const auto f : files_){
            total += f.size();
        }
        for (const auto d : dirs_){

        }
        return total;
    }

    [[nodiscard]] std::vector<std::reference_wrapper<File>> getFiles() const{
        return files_;
    }
private:
    std::vector<Directory> dirs_ {};
    std::vector<File> files_ {};
};