//
// Created by herlight on 2020/8/3.
//

#ifndef UNTITLED_GENERAL_VISITOR_H
#define UNTITLED_GENERAL_VISITOR_H

#include <functional>
#include <map>
#include <tuple>
#include <type_traits>
#include <typeindex>

template<typename Base, typename Func>
class default_vtable {
public:
  template<typename T>
  inline void Set(Func f) {
    data_[std::type_index(typeid(T))] = f;
  }
  inline Func Get(Base *base) { return data_[std::type_index(typeid(*base))]; }

private:
  std::map<std::type_index, Func> data_;
};

template<typename, typename, typename, typename,
         template<typename, typename> typename = default_vtable>
class GeneralVisitor;

template<typename Visitor, typename Base, typename... Deriveds,
         template<typename, typename> typename Vtable, typename R, typename... Args>
class GeneralVisitor<Visitor, Base, std::tuple<Deriveds...>, R(Args...), Vtable> {
  using VtableType = Vtable<Base, R (*)(Visitor *, Base *, Args...)>;

public:
  R Visit(Base *base, Args... args) {
    static VtableType vtable = BuildVtable();
    return vtable.Get(base)(static_cast<Visitor *>(this), base, std::forward<Args>(args)...);
  }

private:
  template<typename Derived, typename... Rest>
  static void Register(VtableType &vtable) {
    vtable.template Set<Derived>([](Visitor *visitor, Base *base, Args... args) -> R {
      return visitor->ImplVisit(static_cast<Derived *>(base), std::forward<Args>(args)...);
    });
    if constexpr (sizeof...(Rest) > 0) { Register<Rest...>(vtable); }
  }

  static VtableType BuildVtable() {
    VtableType vtable;
    Register<Deriveds...>(vtable);
    return vtable;
  }
};

template<typename... Visitors>
class MultiVisitors : public Visitors... {
public:
  using Visitors::Visit...;
};

#endif//UNTITLED_GENERAL_VISITOR_H
