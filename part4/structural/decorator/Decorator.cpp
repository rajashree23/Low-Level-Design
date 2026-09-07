#include <string>
#include <iostream>
#include <memory>

class DataSource
{
public:
    virtual ~DataSource() = default;
    virtual std::string readData() = 0;
    virtual void writeData(const std::string &data) = 0;
};

class FileSource : public DataSource
{
private:
    std::string filename;

public:
    FileSource(const std::string &file) : filename(file) {}

    void writeData(const std::string &data) override
    {
        std::cout << "Writing to file " << filename << "\n";
    }

    std::string readData() override
    {
        return "Reading from file " + filename;
    }
};

class EncryptionDecorator : public DataSource
{
private:
    std::unique_ptr<DataSource> ds;

public:
    EncryptionDecorator(std::unique_ptr<DataSource> source)
        : ds(std::move(source)) {}

    void writeData(const std::string& data) override
    {
        std::string encrypted = "encrypted:" + data;
        ds->writeData(encrypted);
    }

    std::string readData() override
    {
        std::string data = ds->readData();
        return "decrypted:" + data;
    }
};

int main()
{
    auto file = std::make_unique<FileSource>("file.txt");

    auto encrypt =
        std::make_unique<EncryptionDecorator>(std::move(file));

    encrypt->writeData("hello");
    std::cout << encrypt->readData() << "\n";
}