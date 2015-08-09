#ifndef CONTAINERPROXY_H
#define CONTAINERPROXY_H

#include <vector>

template<class T>
class VectorProxy
{
    public:
        VectorProxy(std::vector<T>& from) :
            internal_(from)
        {

        }


        typename std::vector<T>::iterator begin() noexcept
        {
            return internal_.begin();
        }

        typename std::vector<T>::const_iterator begin() const noexcept
        {
            return internal_.begin();
        }


        typename std::vector<T>::iterator end() noexcept
        {
            return internal_.end();
        }

        typename std::vector<T>::const_iterator end() const noexcept
        {
            return internal_.end();
        }

    private:
        std::vector<T>& internal_;
};

#endif // CONTAINERPROXY_H
