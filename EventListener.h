#ifndef EVENTLISTENER_H
#define EVENTLISTENER_H

#include <vector>
#include <functional>
#include <type_traits>

#include "ContainerProxy.h"

template<class... T>
class EventListener
{
    public:
        EventListener() = default;
        virtual ~EventListener() = default;
};

template<class T>
class EventListener<T>
{
    public:
        // Nettoie la liste des évènements à traiter
        template<class U>
        std::enable_if_t<std::is_same<T, U>::value, void>
            clear()
        {
            events_.clear();
        }

        void clear_all() {
            events_.clear();
        }

        // Consulte les évènements enregistrés
        template<class U>
        std::enable_if_t<std::is_same<T, U>::value, VectorProxy<T>>
            events()
        {
            return VectorProxy<T>(events_);
        }

        // Enregistre une fonction callback pour le type spécifié
        template<class U = T>
        std::enable_if_t<std::is_same<T, U>::value, void>
            log(std::function<void(const T&)>&& func)
        {
            callback_ = std::move(func);
        }

    private:
        // Appelée par le dispatcher pour faire passer un évènement
        void push(const T& event) {
            // Si une fonction callback est spécifiée, on l'appel
            if(callback_)
                callback_(event);

            // Sinon on ajoute à la liste des évènements à traiter
            else
                events_.push_back(event);
        }

        std::vector<T> events_;
        std::function<void(const T&)> callback_;

    template<class...>
    friend class EventDispatcher;
};

template<class T, class... Others>
class EventListener<T, Others...> : private EventListener<T>, private EventListener<Others...>
{
    public:
        template<class U>
        std::enable_if_t<std::is_same<T, U>::value, void>
            clear()
        {
            EventListener<T>::template clear<T>();
        }

        template<class U>
        std::enable_if_t<!std::is_same<T, U>::value, void>
            clear()
        {
            EventListener<Others...>::template clear<U>();
        }

        void clear_all() {
            EventListener<T>::template clear<T>();
            EventListener<Others...>::clear_all();
        }

        template<class U>
        std::enable_if_t<std::is_same<T, U>::value, VectorProxy<U>>
            events()
        {
            return EventListener<T>::template events<T>();
        }

        template<class U>
        std::enable_if_t<!std::is_same<T, U>::value, VectorProxy<U>>
            events()
        {
            return EventListener<Others...>::template events<U>();
        }

        template<class U = T>
        std::enable_if_t<std::is_same<T, U>::value, void>
            log(std::function<void(const T&)>&& func)
        {
            EventListener<T>::template log(std::move(func));
        }

        template<class U>
        std::enable_if_t<!std::is_same<T, U>::value, void>
            log(std::function<void(const U&)>&& func)
        {
            EventListener<Others...>::template log<U>(std::move(func));
        }

    template<class...>
    friend class EventDispatcher;
};

#endif // EVENTLISTENER_H
