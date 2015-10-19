#ifndef EVENTDISPATCHER_H
#define EVENTDISPATCHER_H

#include <vector>
#include <type_traits>

#include "EventListener.h"

template<class... T>
class EventDispatcher
{
    public:
        EventDispatcher() = default;
        virtual ~EventDispatcher() = default;
};

template<class T>
class EventDispatcher<T>
{
    public:
        // Envoie un évènement au dispatcher
        template<class U = T>
        std::enable_if_t<std::is_same<T, U>::value, void>
            emit(const T& event)
        {
            // On envoie l'évènement aux listeners attachés au dispatcher
            for(EventListener<T>* listener : attached_) {
                listener->push(event);
            }
        }

        template<class... Listened>
        std::enable_if_t<std::is_base_of<EventListener<T>, EventListener<Listened...>>::value, void>
            attach(EventListener<Listened...>& listener)
        {
            attached_.push_back(static_cast<EventListener<T>*>(&listener));
        }

        template<class... Listened>
        std::enable_if_t<!std::is_base_of<EventListener<T>, EventListener<Listened...>>::value, void>
            attach(EventListener<Listened...>& listener)
        {
        }

    private:
        std::vector<EventListener<T>*> attached_;
};

template<class T, class... Others>
class EventDispatcher<T, Others...> : private EventDispatcher<Others...>
{
    public:
        // Envoie un évènement au dispatcher
        template<class U = T>
        std::enable_if_t<std::is_same<T, U>::value, void>
            emit(const T& event)
        {
            for(EventListener<T>* listener : attached_) {
                listener->push(event);
            }
        }

        template<class U>
        std::enable_if_t<!std::is_same<T, U>::value, void>
            emit(const U& event)
        {
            EventDispatcher<Others...>::template emit(event);
        }

        template<class... Listened>
        std::enable_if_t<std::is_base_of<EventListener<T>, EventListener<Listened...>>::value, void>
            attach(EventListener<Listened...>& listener)
        {
            // Si le Listener est constitué d'un sous-listener pour le type T, on en prend le pointeur
            attached_.push_back(static_cast<EventListener<T>*>(&listener));

            // Puis on passe le listener au sous-dispatcher parent
            // (ainsi tous les types de "Listened..." sont attachés aux différents sous-dispatchers du Dispatcher)
            EventDispatcher<Others...>::template attach(listener);
        }

        template<class... Listened>
        std::enable_if_t<!std::is_base_of<EventListener<T>, EventListener<Listened...>>::value, void>
            attach(EventListener<Listened...>& listener)
        {
            EventDispatcher<Others...>::template attach(listener);
        }

    private:
        std::vector<EventListener<T>*> attached_;
};

#endif // EVENTDISPATCHER_H
