//
// Created by Leo on 23/12/19.
//

#ifndef CORE_PAYLOADCONFIG_HPP
#define CORE_PAYLOADCONFIG_HPP

#include <iostream>
#include <map>
#include <nlohmann/json.hpp>
#include <vector>

class PayloadConfig {
public:
    explicit PayloadConfig(std::string t_message) {
        nlohmann::json payload = nlohmann::json::parse(t_message);
        m_originator = payload["originator"];
        m_content    = payload["content"];
        setRecipient(payload);
    }

    void setRecipient(nlohmann::json recipient) {
        auto& element = recipient["recipient"];
        std::copy(element.begin(), element.end(), back_inserter(m_recipient));
    }

    const std::vector<std::string> &getRecipient() const {
        return m_recipient;
    }

    const std::string &getOriginator() const {
        return m_originator;
    }

    const std::string &getContent() const {
        return m_content;
    }

private:
    std::vector<std::string> m_recipient;
    std::string m_originator;
    std::string m_content;
};

#endif //CORE_PAYLOADCONFIG_HPP
