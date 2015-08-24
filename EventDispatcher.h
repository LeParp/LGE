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
        template<class U>
        void emit(const U& event)
        {
            assert((std::is_same<T, U>::value));

            // On envoie l'évènement aux listeners attachés au dispatcher
            for(EventListener<T>* listener : attached_)
                listener->push((const T&)event);
        }

        template<class... Listened>
        void attach(EventListener<Listened...>& listener)
        {
            // Si le listener est constitué d'un sous-listener pour le type T, on en prend le pointeur
            if(std::is_base_of<EventListener<T>, EventListener<Listened...>>::value)
                attached_.push_back((EventListener<T>*)(&listener));
        }

    private:
        std::vector<EventListener<T>*> attached_;
};

template<class T, class... Others>
class EventDispatcher<T, Others...> : private EventDispatcher<Others...>
{
    public:
        // Envoie un évènement au dispatcher
        template<class U>
        void emit(const U& event)
        {
            // Si le type de l'évènement correspond à celui du dispatcher
            if(std::is_same<T, U>::value)
            {
                // On envoie l'évènement aux listeners attachés au dispatcher
                for(EventListener<T>* listener : attached_)
                    listener->push((const T&)event);
            }

            // Puis on passe l'évènement au "sous-dispatcher" parent
            else
                EventDispatcher<Others...>::template emit<U>(event);
        }

        template<class... Listened>
        void attach(EventListener<Listened...>& listener)
        {
            // Si le listener est constitué d'un sous-listener pour le type T, on en prend le pointeur
            if(std::is_base_of<EventListener<T>, EventListener<Listened...>>::value)
                attached_.push_back((EventListener<T>*)(&listener));

            // Puis on passe le listener au sous-dispatcher parent
            // (ainsi tous les types de "Listened..." sont attachés aux différents sous-dispatcher du dispatcher)
            EventDispatcher<Others...>::template attach<Listened...>(listener);
        }

    private:
        std::vector<EventListener<T>*> attached_;
};

#endif // EVENTDISPATCHER_H
