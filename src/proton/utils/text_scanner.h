#pragma once
#include <algorithm>
#include <string>
#include <vector>
#include <fmt/format.h>
#include <proton/utils/common.h>
#include <utils/text.h>

namespace GrowtopiaServer
{
    class TextScanner { //thanks to ztz who helped me on this
    public:
        TextScanner() : m_data() {}
        explicit TextScanner(const std::string& string) { 
            this->Parse(string); 
        }
        explicit TextScanner(const std::vector<std::pair<std::string, std::string>>& data) {
            for (const auto& it : data)
                this->add(it.first, it.second);
        }
        ~TextScanner() = default;

        void Parse(const std::string& string) {
            m_data = this->StringTokenize(string, "\n");
            for (auto &data : m_data) {
                std::replace(data.begin(), data.end(), '\r', '\0');
            }
        }
        static std::vector<std::string> StringTokenize(const std::string &string, const std::string &delimiter = "|") {
            std::vector<std::string> tokens{};
            for (const auto& word : utils::split(string, delimiter))
                tokens.emplace_back(word.begin(), word.end());
            return tokens;
        }

        std::string Get(const std::string &key, int index = 1, const std::string &token = "|", int key_index = 0) {
            if (m_data.empty())
                return "";

            for (auto &data : m_data) {
                if (data.empty())
                    continue;
                std::vector<std::string> tokenize = this->StringTokenize(data, token);
                if (tokenize[key_index] == key) {
                    if (index < 0 || index >= tokenize.size())
                        return "";
                    return tokenize[key_index + index];
                }
            }
            return "";
        }
        template<typename T, typename std::enable_if_t<std::is_integral_v<T>, bool> = true>
        T Get(const std::string &key, int index = 1, const std::string &token = "|") {
            return std::stoi(this->Get(key, index, token));
        }
        template<typename T, typename std::enable_if_t<std::is_floating_point_v<T>, bool> = true>
        T Get(const std::string &key, int index = 1, const std::string &token = "|") {
            if (std::is_same_v<T, double>)
                return std::stod(this->Get(key, index, token));
            else if (std::is_same_v<T, long double>)
                return std::stold(this->Get(key, index, token));
            return std::stof(this->Get(key, index, token));
        }

		bool TryGet(const std::string& key, std::string& value) noexcept {
			if (!this->contain(key))
				return false;
			value = this->Get(key);
			return true;
		}
        template<typename T, typename std::enable_if_t<std::is_integral_v<T>, bool> = true>
        bool TryGet(const std::string& key, T &value) noexcept {
			if (!this->contain(key))
				return false;
			value = std::atoi(this->Get(key).c_str());
			return true;
		}
        bool TryGet(const std::string& key, bool &value) noexcept {
			if (!this->contain(key))
				return false;
			value = this->Get(key) == "1" ? true : false;
			return true;
		}

        TextScanner* add(const std::string& key, const std::string& value, const std::string& token = "|") {
            m_data.push_back(key + token + value);
            return this;
        }
        template<typename T, typename std::enable_if_t<std::is_integral_v<T> || std::is_floating_point_v<T>, bool> = true>
        TextScanner* add(const std::string& key, const T& value, const std::string& token = "|") {
            this->add(key, std::to_string(value), token);
            return this;
        }
        TextScanner* add(const std::string& key, const CL_Vec2i& value, const std::string& token = "|") {
            std::string data{
                std::to_string(value.m_x) + '|' +
                std::to_string(value.m_y)
            };
            this->add(key, data, token);
            return this;
        }
        TextScanner* add(const std::string& key, const CL_Recti& value, const std::string& token = "|") {
            std::string data{
                std::to_string(value.x) + '|' +
                std::to_string(value.y) + '|' +
                std::to_string(value.width) + '|' +
                std::to_string(value.height)
            };
            this->add(key, data, token);
            return this;
        }

        void set(const std::string &key, const std::string &value, const std::string &token = "|") {
            if (m_data.empty())
                return;

            for (auto &data : m_data) {
                std::vector<std::string> tokenize = this->StringTokenize(data, token);
                if (tokenize[0] == key) {
                    data = std::string{ tokenize[0] };
                    data += token;
                    data += value;
                    break;
                }
            }
        }
        template<typename T, typename std::enable_if_t<std::is_integral_v<T> || std::is_floating_point_v<T>, bool> = true>
        void set(const std::string &key, const T &value, const std::string &token = "|") {
            this->set(key, std::to_string(value), token);
        }

		bool contain(const std::string& key) {
			return this->Get(key) != "" ? true : false;
		}

        std::vector<std::string> get_all_array() {
            std::vector<std::string> ret{};
            for(int i = 0; i < m_data.size(); i++)
                ret.push_back(fmt::format("[{}]: {}", i, m_data[i]));

            return ret;
        }
        std::string get_all_raw() const {
            std::string string{};
            for (int i = 0; i < m_data.size(); i++) {
                string += m_data.at(i);
                if (i + 1 >= m_data.size())
                    continue;

                if (!m_data.at(i + 1).empty())
                    string += '\n';
            }

            return string;
        }

        std::vector<std::string> get_data() const { return m_data; }
        std::string& get_data(const std::size_t& pos) { return m_data[pos]; }
        bool empty() { return m_data.empty(); }
        std::size_t size() { return m_data.size(); }

    private:
        std::vector<std::string> m_data;
    };
}