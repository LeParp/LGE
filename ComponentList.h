#ifndef COMPONENTLIST_H
#define COMPONENTLIST_H

#include <cassert>
#include <algorithm>
#include <vector>
#include <forward_list>

#include "Entity.h"

template<class T>
class ComponentList
{
    struct Pair
    {
        Entity entity;
        T component;

        friend bool operator==(const Pair& lhs, const Pair& rhs) {
            return lhs.entity == rhs.entity;
        }

        friend bool operator!=(const Pair& lhs, const Pair& rhs) {
            return !(lhs == rhs);
        }
    };

    class Iterator : public std::iterator<std::forward_iterator_tag, T>
    {
        public:
            Iterator(std::vector<Pair>& vec, unsigned pos) :
                pos_(pos),
                vec_(vec) {

            }

            Iterator(const Iterator& other) = default;
            Iterator& operator=(const Iterator& other) = default;

            Entity key() {
                assert(pos_ < vec_.size());
                return vec_[pos_].entity;
            }

            T& value() {
                assert(pos_ < vec_.size());
                return vec_[pos_].component;
            }

            Iterator& operator++() {
                ++pos_;
                return *this;
            }

            Iterator operator++(int) {
                ++pos_;
                return Iterator(vec_, pos_ - 1);
            }

            T& operator*() {
                return value();
            }

            T* operator->() {
                return &value();
            }

        private:
            unsigned pos_;
            std::vector<Pair>& vec_;

        friend bool operator==(const Iterator& lhs, const Iterator& rhs) {
            return (lhs.vec_ == rhs.vec_ && lhs.pos_ == rhs.pos_);
        }

        friend bool operator!=(const Iterator& lhs, const Iterator& rhs) {
            return !(lhs == rhs);
        }
    };

    public:
        ComponentList() {

        }


        void insert(const Entity& entity, T&& component) {
            array_.emplace_back(Pair{entity, std::move(component)});
        }

        void erase(const Entity& entity) {
            for(auto it = array_.begin(); it != array_.end(); ++it) {
                if(it->entity == entity)
                    array_.erase(it);
            }
        }

        void erase(const Iterator& it) {
            array_.erase(array_.begin() + it.pos_);
        }


        bool has_value(const Entity& entity) {
            return std::any_of(array_.begin(), array_.end(), [&entity](Pair& p) {
                return p.entity == entity;
            });
        }

        size_t size() const {
            return array_.size();
        }


        T& front() {
            return *begin();
        }

        T& back() {
            return *Iterator(array_, array_.size() - 1);
        }

        Iterator begin() {
            return Iterator(array_, 0);
        }

        Iterator end() {
            return Iterator(array_, array_.size());
        }

        T& operator[](const Entity& entity) {
            assert(has_value(entity));

            for(auto it = array_.begin(); it != array_.end(); ++it) {
                if(it->entity == entity)
                    return it->component;
            }

            return array_[0].component;
        }

        const T& operator[](const Entity& entity) const {
            assert(has_value(entity));

            for(auto it = array_.begin(); it != array_.end(); ++it) {
                if(it->entity == entity)
                    return it->component;
            }

            return array_[0].component;
        }

    private:
        std::vector<Pair> array_;
};

#endif // COMPONENTLIST_H
