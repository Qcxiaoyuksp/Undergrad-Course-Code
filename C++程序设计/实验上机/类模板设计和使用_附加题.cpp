#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>

// 基类CTimer
class CTimer {
protected:
    unsigned long m_TimerID; // 时钟编号
public:
    CTimer(unsigned long id) : m_TimerID(id) {}
    virtual ~CTimer() {}

    // 获取时区代号的虚函数，需要子类重载
    virtual std::string GetTimeZone() const = 0;

    // 获取TimerID的纯虚函数
    virtual unsigned long GetTimerID() const = 0;

    // 用于测试打印当前对象的时区
    void PrintTimeZone() const {
        std::cout << "Timer ID: " << GetTimerID() << ", Time Zone: " << GetTimeZone() << std::endl;
    }
};

// 派生类CBeijingTimer
class CBeijingTimer : public CTimer {
public:
    CBeijingTimer(unsigned long id) : CTimer(id) {}

    // 重载GetTimeZone函数
    std::string GetTimeZone() const override {
        return "BJT"; // 北京时间代号
    }

    // 实现GetTimerID
    unsigned long GetTimerID() const override {
        return CTimer::m_TimerID;
    }
};

// 时钟管理类
class TimerManager {
private:
    std::vector<CTimer*> m_Timers; // 保存所有Timer的指针
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

    // 创建北京时钟并添加
    CBeijingTimer* beijingTimer = new CBeijingTimer(1);
    manager.AddTimer(beijingTimer);

    // 打印所有时区
    manager.PrintAllTimeZones();

    // 尝试删除不存在的TimerID
    try {
        manager.RemoveTimerByID(999);
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }

    // 删除刚才添加的北京时钟
    manager.RemoveTimerByID(1);

    return 0;
}
