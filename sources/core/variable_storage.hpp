#ifndef VARIABLE_STORAGE_HPP
#define VARIABLE_STORAGE_HPP

#include <string>
#include <unordered_map>

namespace core
{
class VariableStorage
{
public:
    static VariableStorage& getInstance();

    int getInt(const std::string& name) const noexcept;

    float getFloat(const std::string& name) const noexcept;

    std::string getWord(const std::string& name) const noexcept;

private:
    VariableStorage();

    std::unordered_map<std::string, int> m_ints;

    std::unordered_map<std::string, std::string> m_words;

    std::unordered_map<std::string, float> m_floats;
};
} // namespace core

#endif // VARIABLE_STORAGE_HPP