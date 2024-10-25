#include "publisher.hpp"
#include "objects/components.hpp"

void IPublisher::AddObserver(std::shared_ptr<IEventObserver> observer)
{
    m_observers.push_front(observer);
}

void IPublisher::RemoveObserver(std::shared_ptr<IEventObserver> observer)
{
    m_observers.remove(observer);
}
