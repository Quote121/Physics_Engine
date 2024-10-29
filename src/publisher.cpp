#include "publisher.hpp"
#include "objects/components.hpp"

void IPublisher::AddObserver(IEventObserver* observer)
{
    m_observers.push_front(observer);
}

void IPublisher::RemoveObserver(IEventObserver* observer)
{
    m_observers.remove(observer);
}
