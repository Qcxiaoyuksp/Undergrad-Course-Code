#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>

// ����CTimer
class CTimer {
protected:
    unsigned long m_TimerID; // ʱ�ӱ��
public:
    CTimer(unsigned long id) : m_TimerID(id) {}
    virtual ~CTimer() {}

    // ��ȡʱ�����ŵ��麯������Ҫ��������
    virtual std::string GetTimeZone() const = 0;

    // ��ȡTimerID�Ĵ��麯��
    virtual unsigned long GetTimerID() const = 0;

    // ���ڲ��Դ�ӡ��ǰ�����ʱ��
    void PrintTimeZone() const {
        std::cout << "Timer ID: " << GetTimerID() << ", Time Zone: " << GetTimeZone() << std::endl;
    }
};

// ������CBeijingTimer
class CBeijingTimer : public CTimer {
public:
    CBeijingTimer(unsigned long id) : CTimer(id) {}

    // ����GetTimeZone����
    std::string GetTimeZone() const override {
        return "BJT"; // ����ʱ�����
    }

    // ʵ��GetTimerID
    unsigned long GetTimerID() const override {
        return CTimer::m_TimerID;
    }
};

// ʱ�ӹ�����
class TimerManager {
private:
    std::vector<CTimer*> m_Timers; // ��������Timer��ָ��
public:
    void AddTimer(CTimer* timer) {
        m_Timers.push_back(timer);
    }

    void RemoveTimerByID(unsigned long id) {
        for (auto it = m_Timers.begin(); it != m_Timers.end(); ++it) {
            if ((*it)->GetTimerID() == id) {
                delete *it;
                m_Timers.erase(it);
                return;
            }
        }
        throw std::runtime_error("Timer with specified ID not found.");
    }

    void PrintAllTimeZones() const {
        for (const auto& timer : m_Timers) {
            timer->PrintTimeZone();
        }
    }

    CTimer* FindTimerByID(unsigned long id) const {
        for (const auto& timer : m_Timers) {
            if (timer->GetTimerID() == id) {
                return timer;
            }
        }
        return nullptr;
    }
};

int main() {
    TimerManager manager;

    // ��������ʱ�Ӳ����
    CBeijingTimer* beijingTimer = new CBeijingTimer(1);
    manager.AddTimer(beijingTimer);

    // ��ӡ����ʱ��
    manager.PrintAllTimeZones();

    // ����ɾ�������ڵ�TimerID
    try {
        manager.RemoveTimerByID(999);
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }

    // ɾ���ղ���ӵı���ʱ��
    manager.RemoveTimerByID(1);

    return 0;
}
