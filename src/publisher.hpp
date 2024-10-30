#pragma once

#include <forward_list>
#include <memory>

// Forward decleration
class IEventObserver;

class IPublisher
{
protected:
    std::forward_list<IEventObserver*> m_observers;

    /// @brief Call all the observers notify function
    virtual void NotifyAll() = 0;
    virtual ~IPublisher() = default;

public:

    /// @brief Subscribe to the publisher
    /// @param observer The subscriber. Will be notified on an event
    void AddObserver(IEventObserver* observer);

    /// @brief Unsubscribe from the publisher. No more notifications.
    /// @param observer The subscriber to remove, will no longer be notified.
    void RemoveObserver(IEventObserver* observer);
};

