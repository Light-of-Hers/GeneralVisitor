//
// Created by herlight on 2020/8/3.
//

#ifndef UNTITLED_GENERAL_VISITOR_H
#define UNTITLED_GENERAL_VISITOR_H

#include <functional>
#include <typeindex>
#include <map>
#include <tuple>
#include <type_traits>

template<typename Base, typename Func>
class default_vtable {
public:
  template<typename T>
  inline void Set(Func f) {
    data_[std::type_index(typeid(T))] = std::move(f);
  }
  inline Func Get(Base *base) {
    return std::move(data_[std::type_index(typeid(*base))]);
  }

private:
  std::map<std::type_index, Func> data_;
};

template<typename, typename, typename, template<typename, typename> typename = default_vtable>
class GeneralVisitor;

template<typename Visitor, typename Base,
        template<typename, typename> typename Vtable, typename R, typename ...Args>
class GeneralVisitor<Visitor, Base, R(Args...), Vtable> {
public:
  R Visit(Base *base, Args ...args) {
    return vtable.Get(base)(static_cast<Visitor *>(this), base, std::forward<Args>(args)...);
  }

protected:
  template<typename Derived, typename ...Rest>
  void Register() {
    vtable.template Set<Derived>(
            [](Visitor *visitor, Base *base, Args ...args) -> R {
              return visitor->ImplVisit(static_cast<Derived *>(base), std::forward<Args>(args)...);
            }
    );
    if constexpr (sizeof...(Rest) > 0) {
      Register<Rest...>();
    }
  }

private:
  Vtable<Base, R(*)(Visitor *, Base *, Args...)> vtable;
};

#endif //UNTITLED_GENERAL_VISITOR_H
