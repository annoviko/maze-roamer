#pragma once


template <typename Type>
class singleton {
protected:
    singleton() = default;

public:
    singleton(const singleton& p_other) = delete;
    singleton(singleton&& p_other) = delete;

    singleton& operator=(const singleton& p_other) = delete;
    singleton& operator=(singleton&& p_other) = delete;

public:
    static Type& get() {
        static Type m_instance;
        return m_instance;
    }
};
