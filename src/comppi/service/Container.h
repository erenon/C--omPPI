#ifndef COMPPI_SERVICE_CONTAINER_H_
#define COMPPI_SERVICE_CONTAINER_H_

#include <memory>
#include <type_traits>

namespace comppi {
namespace service {

class Container {
private:
    template <typename S>
    struct has_factory {
    private:
        template <typename S1>
        static typename S1::ServiceFactory test(int);

        template <typename S2>
        static void test(...);
    public:
        enum { value = std::is_class<decltype(test<S>(0))>::value };
    };

public:
    template<
        typename Service,
        typename std::enable_if<
            has_factory<Service>::value,
            int
        >::type = 0
    >
    typename Service::SelfPtr get() {
        static auto servicePtr = Service::ServiceFactory::create(*this);
        return servicePtr;
    }

    template<
        typename Service,
        typename std::enable_if<
            !has_factory<Service>::value,
            int
        >::type = 0
    >
    typename std::shared_ptr<Service> get() {
        static auto servicePtr = std::make_shared<Service>();
        return servicePtr;
    }
};

} // namespace service
} // namespace comppi

#endif  // COMPPI_SERVICE_CONTAINER_H_
