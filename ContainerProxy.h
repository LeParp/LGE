#ifndef CONTAINERPROXY_H
#define CONTAINERPROXY_H

#include <vector>
#include <unordered_map>

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

template<class K, class V>
class UMapProxy
{
    class Iterator
    {
        public:
            Iterator(typename std::unordered_map<K, V>::iterator it) :
                it_(it)
            {

            }

            V& operator*()
            {
                return it_->second;
            }

            Iterator operator++()
            {
                return Iterator(++it_);
            }

            bool operator!=(UMapProxy<K, V>::Iterator const& other)
            {
                return it_ != other.it_;
            }

        private:
            typename std::unordered_map<K, V>::iterator it_;
    };

    public:
        UMapProxy(std::unordered_map<K, V>& from) :
            internal_(from)
        {

        }


        Iterator begin() noexcept
        {
            return Iterator(internal_.begin());
        }

        Iterator end() noexcept
        {
            return Iterator(internal_.end());
        }


        /*typename std::unordered_map<T>::const_iterator begin() const noexcept
        {
            return Iterator(internal_.begin());
        }

        typename std::unordered_map<T>::const_iterator end() const noexcept
        {
            return Iterator(internal_.end());
        }*/

    private:
        std::unordered_map<K, V>& internal_;
};

#endif // CONTAINERPROXY_H
