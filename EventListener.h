#ifndef EVENTLISTENER_H
#define EVENTLISTENER_H

#include <vector>
#include <functional>
#include <type_traits>
#include <cassert>

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
        // Nettoie la liste des �v�nements � traiter de type U
        template<class U>
        void clear()
        {
            // Le type demand� doit correspondre � celui de ce sous-dispatcher
            // (sinon l'appel de l'utilisateur est sans-effet)
            assert((std::is_same<U, T>::value));
            events_.clear();
        }

        // Nettoie toutes les listes d'�v�nements � traiter
        void clear_all()
        {
            EventListener<T>::template clear<T>();
        }

        // Consulte les �v�nements enregistr�s
        template<class U>
        VectorProxy<U> events()
        {
            // Le type demand� doit correspondre � celui de ce sous-dispatcher
            assert((std::is_same<U, T>::value));
            return VectorProxy<U>((std::vector<U>&)events_);
        }

        // Enregistre une fonction callback pour le type sp�cifi�
        template<class U>
        void log(std::function<void(const U&)>&& func)
        {
            // Le type demand� doit correspondre � celui de ce sous-dispatcher
            assert((std::is_same<U, T>::value));
            callback_ = std::move((std::function<void(const T&)>&&)func);
        }

    private:
        // Appel�e par le dispatcher pour faire passer un �v�nement
        void push(const T& event)
        {
            // Si une fonction callback est sp�cifi�e, on l'appel
            if(callback_)
                callback_((const T&)event);

            // Sinon on ajoute � la liste des �v�nements � traiter
            else
                events_.push_back((const T&)event);
        }

        std::vector<T> events_;
        std::function<void(const T&)> callback_;

    template<class... X>
    friend class EventDispatcher;
};

template<class T, class... Others>
class EventListener<T, Others...> : private EventListener<T>, private EventListener<Others...>
{
    public:
        template<class U>
        void clear()
        {
            if(std::is_same<U, T>::value)
                EventListener<T>::template clear<U>();

            else
                EventListener<Others...>::template clear<U>();
        }

        void clear_all()
        {
            EventListener<T>::template clear<T>();
            EventListener<Others...>::clear_all();
        }

        template<class U>
        VectorProxy<U> events()
        {
            if(std::is_same<U, T>::value)
                return EventListener<T>::template events<U>();

            else
                return EventListener<Others...>::template events<U>();
        }

        template<class U>
        void log(std::function<void(const U&)>&& func)
        {
            if(std::is_same<U, T>::value)
                EventListener<T>::template log<U>(std::move(func));

            else
                EventListener<Others...>::template log<U>(std::move(func));
        }
};

#endif // EVENTLISTENER_H
