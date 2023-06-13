#pragma once


class event_base {
protected:
    char m_subject_id;
    int m_amount;

public:
    event_base(const char p_subject_id, const int p_amount) :
        m_subject_id(p_subject_id),
        m_amount(p_amount)
    { }

public:
    char get_subject_id() const { return m_subject_id; }

    int get_amount() const { return m_amount; }
};
